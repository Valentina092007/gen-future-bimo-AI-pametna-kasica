#include <HX711_ADC.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// HX711 pinovi
const int DT_PIN = 4;
const int SCK_PIN = 5;
HX711_ADC LoadCell(DT_PIN, SCK_PIN);

// Bluetooth na pinovima 10 (RX) i 11 (TX)
SoftwareSerial Bluetooth(10, 11);

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Servo objekti - vage i spremnici
Servo v2;
Servo s2;

byte okoOtvoreno[8] = {0, 14, 21, 21, 21, 14, 0, 0};
byte okoZatvoreno[8] = {0, 0, 0, 31, 0, 0, 0, 0};
byte usta[8] = {0, 0, 10, 10, 0, 17, 14, 0}; // Smiješak :3

String trenutniTotal = "0.00"; // Varijabla za spremanje iznosa s aplikacije

void setup() {
  Serial.begin(57600); 
  Bluetooth.begin(9600); 
  
  LoadCell.begin();
  LoadCell.start(2000, true); 

  lcd.init();
  lcd.backlight();
  
  // Registracija lica
  lcd.createChar(0, okoOtvoreno);
  lcd.createChar(1, okoZatvoreno);
  lcd.createChar(2, usta);

  lcd.setCursor(0, 0);
  lcd.print("Dobar dan! -w-");
  delay(2000); 
  lcd.clear();
  
  prikaziLice(); // Lice se pojavljuje od početka
  
  v2.attach(7);
  s2.attach(8);
  
  zatvoriSve(); 
}

void loop() {
  // Slušanje naredbi iz aplikacije preko BLUETOOTHA
  if (Bluetooth.available() > 0) {
    String dolaznaLinija = Bluetooth.readStringUntil('\n'); // Čitamo cijelu poruku
    
    if (dolaznaLinija.length() > 0) {
      char tip = dolaznaLinija.charAt(0); // Gledamo prvi znak (* ili # ili W)
      String podatak = dolaznaLinija.substring(1); // Ostatak poruke
      
      if (tip == 'W') { 
        otvoriSpremnik(); 
        delay(3000); 
        zatvoriSve();
      }
      else if (tip == '#') { // Ako je stigao NOVI TOTAL
        trenutniTotal = podatak;
        osvjeziTotal();
      }
      else if (tip == '*') { // Ako je stigao CHATBOT ODGOVOR
        skrolajPoruku(podatak);
      }
    }
  }

  // Update LoadCell i detekcija težine
  if (LoadCell.update()) {
    float weight = abs(LoadCell.getData());
    if (weight > 7.0) { 
      delay(500);
      
      if (weight < 12.0) { 
        Bluetooth.print("1"); 
      } else { 
        Bluetooth.print("2"); 
      }

      otvoriVagu(); 
      delay(2000); 
      zatvoriSve();
      Bluetooth.flush();
      prikaziLice(); // Vraća lice ako ga je skrolanje maknulo
      osvjeziTotal(); // Vraća total
    }
  }
}

// POMOĆNE FUNKCIJE ZA LCD
void prikaziLice() {
  lcd.setCursor(13, 0);
  lcd.write(byte(0)); // Lijevo oko
  lcd.write(byte(2)); // Usta
  lcd.write(byte(0)); // Desno oko
}

void osvjeziTotal() {
  lcd.setCursor(0, 0);
  lcd.print("T:"); 
  lcd.print(trenutniTotal);
  lcd.print("e   "); // Razmaci brišu stare brojke
}

void skrolajPoruku(String tekst) {
  lcd.setCursor(0, 1);
  lcd.print("                "); // Čisti donji red
  String prikaz = "                " + tekst + "                "; 
  for (int i = 0; i < prikaz.length() - 16; i++) {
    lcd.setCursor(0, 1);
    lcd.print(prikaz.substring(i, i + 16));
    delay(250); // Brzina skrolanja
    if (Bluetooth.available() > 0) break; // Prekid ako stigne nova poruka
  }
}

// Zasebne funkcije za servo
void otvoriVagu() {  
  v2.write(180); 
}
  
void otvoriSpremnik() {  
  s2.write(90); 
}

void zatvoriSve() { 
  v2.write(90); 
  s2.write(0); 
}
