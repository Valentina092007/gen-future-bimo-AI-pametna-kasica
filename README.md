# gen-future-bimo-AI-pametna-kasica
1. Opis i cilj projekta:
•	Bimo je interaktivni personalni financijski asistent; predstavlja robotsku „kasicu prasicu“. Cilj projekta je modernizirati proces štednje korištenjem umjetne inteligencije (AI) i robotike kako bi se korisnicima, posebice mladima, olakšalo upravljanje novcem i planiranje financijskih ciljeva.
2. Povezanost s financijskom pismenošću:
•	Središnji dio projekta je edukacija o financijskoj pismenosti. Bimo ne služi samo za fizičko prikupljanje novca, već putem integriranog AI chatbota pruža:
•	analizu ciljeva – pomaže korisniku izračunati koliko mu je još potrebno za određenu kupnju (npr. novi bicikl)
•	savjetovanje – pruža konkretne, personalizirane savjete o štednji, smanjenju nepotrebnih troškova i malim poslovima za povećanje budžeta
•	praćenje napretka – vizualizira štednju kao dinamičan proces, a ne samo kao statičan iznos.
3. Razvoj mobilne aplikacije (MIT App Inventor):
•	Aplikacija je razvijena na platformi MIT App Inventor i služi za interakciju između korisnika i robotske kasice.
•	Dizajn sučelja (UI) - intuitivno sučelje koje sadržava sljedeće elemente:
-	prikaz ukupnog (total) iznosa novca u kasici
-	gumbove za biranje količine novca koju želimo podići (Withdraw)
-	AI chatbot „Bimo“ kojemu možemo postavljati pitanja ili ciljeve vezane za štednju ili financije općenito, i dodatni gumb za mogućnost dijeljenja njegovog odgovora putem drugih aplikacija.

•	AI integracija - povezana je s Google Gemini 2.5 Flash modelom putem Google Apps Scripta

•	Upozorenje za zaštitu privatnosti: Nikada ne biste trebali upisivati osjetljive osobne podatke (poput kućne adrese, stvarnih bankovnih lozinki ili privatnih tajni) u AI chatbota!

4. Hardverski sustav i Arduino programiranje:
•	U srcu (središtu) fizičkog uređaja je Arduino Uno mikrokontroler koji upravlja mehaničkim dijelovima kasice:
•	senzorom težine (HX711 Load Cell) - koristi se za precizno mjerenje težine ubačenih kovanica
•	sustavom servo motora - ukupno 4 servo motora upravlja kretanjem novca:
o	prva 2 serva - zadržavaju kovanicu na senzoru težine dok aplikacija ne obradi podatke
o	druga 2 serva - upravljaju spremnikom kovanica i omogućuju opciju "Withdraw" (podizanje novca) na zahtjev korisnika putem aplikacije.

•	Napajanje i optimizacija – za napajanje svih četiri servo motora koristi se eksterni izvor od 6V (četiri AA baterije od 1,5V spojene u seriju) kako bi se osigurala stabilna snaga i spriječilo preopterećenje Arduino ploče.

•	Ostale elektroničke komponente – u projektu su, uz senzore i aktuatore, korištene ključne komponente za komunikaciju i interakciju s korisnikom:
o	Bluetooth modul HC-05 – modul omogućuje dvosmjerni prijenos podataka – slanje informacija o detektiranim kovanicama s Arduina na mobitel te primanje naredbi iz aplikacije (npr. otvaranje spremnika za isplatu ili ažuriranje ukupnog iznosa)

o	LCD 16x2 zaslon (s I2C adapterom) – zaslon u stvarnom vremenu prikazuje trenutačno stanje novca u Bimu ("Total"); posebnost ovog rješenja su vlastiti grafički znakovi (custom characters) koji animiraju Bimovo lice (oči i usta), čime uređaj dobiva na osobnosti

•	Donji red zaslona rezerviran je za skrolajući tekst koji prikazuje odgovore dobivene od chatbota iz mobilne aplikacije, omogućujući Bimu da "razgovara" s korisnikom

5. Povezivanje komponenti i komunikacija:
•	Projekt se oslanja na sinkronizaciju triju razina:
1.	Aplikacija ↔ Cloud – slanje upita Gemini AI-ju i primanje financijskih savjeta
2.	Aplikacija ↔ Arduino – slanje naredbi za otvaranje spremnika (Withdraw)
3.	Arduino ↔ mehanika – koordinacija rada senzora i motora kako bi se fizički novac sigurno pohranio i izvagao.
Zaključak:
Projekt Bimo uspješno demonstrira kako se moderni alati poput umjetne inteligencije i mikrokontrolera mogu koristiti u službi financijske edukacije. Kroz praktičan rad na dizajnu aplikacije i sastavljanju hardvera, projekt nudi cjelovito rješenje za razvoj financijskih navika u digitalnom dobu.
