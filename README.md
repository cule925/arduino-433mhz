# ARDUINO BEŽIČNA KOMUNIKACIJA 433 MHZ

[Arduino](https://www.arduino.cc/) je talijanska tvrtka koja se bavi dizajniranjem mikroupravljačkih pločica za razvoj i edukaciju te softvera kojim se programiraju te pločice. Sav hardver i softver koji proizvode su otvorenog koda te svatko može proizvoditi Arduino pločice (*eng. Creative Commons license*) ili distribuirati kod (*eng GPL - General Public License*). Za razvoj softvera Arduino pruža svoje razvojno okruženje. Programiranje pločice se radi u varijanti C i C++ programskih jezika: *Embedded C*.

## Instalacija Arduino razvojnog okruženja

Arduino razvojno okruženje se na Arch Linux operacijskom sustavu može instalirati naredbom:
```
sudo pacman -S arduino-ide
```

Pokretanje razvojnog okruženja moguće je naredbom (ili preko grafičkog sučelja):
```
arduino-ide
```

Minimalni program za Arduino ima sljedeću strukturu:

- *setup()* - izvodi se jednom u početku paljenja ili resetiranja Arduina
- *loop()* - beskonačna petlja koja se izvodi nakon *setup()* funkcije

### Korištenje Arduino alata za naredbeni redak

Umjesto grafičkog alata *arduino-ide* može se koristiti alat naredbenog retka [*arduino-cli*](https://arduino.github.io/arduino-cli/1.0/). Stvaranje inicijalne konfiguracijske datoteke:

```
arduino-cli config init
```

Stvaranje novog projekta (*Arduino Sketch*):

```
arduino-cli sketch new [ime projekta]
```

Projekt sadrži izvorne datoteke i biblioteke potrebne za prevođenje. Datoteka koja se u projektu nalazi je ```[Ime projekta].ino``` koja sadržava početnu šablonu koda. Datoteku se može uređivati bilo kojim uređivačem teksta (```nano```, ```gedit```, ```code```, ...).

Ažuriranje lokalnog *cachea* za nove platforme i biblioteke može se napraviti naredbom:

```
arduino-cli core update-index
```

Ako se spoji Arduino pločica, Linux bi je trebao prepoznati. Spojene pločice se mogu izlistati s naredbom:
```
arduino-cli board list
```

FQBN (*eng. Fully Qualified Board Name*) se koristi za identificiranje pločice (oblik ```platform:core:specific_board```). U slučaju da za ploču piše *Unknown* dovoljno je samo znati njezin FQBN da bi se mogao prevesti izvorni kod. FQBN označava sljedeće:

- platformu (*eng. platform*)
- jezgru, odnosno softverske pakete potrebno za prevođenje koda za pločicu (*eng. core*)
- pločica (*specific_board*)

Saznavanje FQBN za specifičnu pločicu se može napraviti naredbom:

```
arduino-cli board search [ime pločice]
```

Za Arduino Nano je FQBN ```arduino:avr:nano```.

Pretraga biblioteka s Arduino repozitorija moguće je naredbom:

```
arduino-cli lib search [ime biblioteke]
```

Instalacija biblioteke s Arduino repozitorija moguće je naredbom:

```
arduino-cli lib install [ime biblioteke]
```

Primjerice, biblioteku RadioHead moguće je instalirati naredbom ```arduino-cli install search RadioHead```.

Prevođenje datoteke ```[ime projekta].ino``` moguće je naredbom:

```
arduino-cli compile --fqbn [FQBN] [.ino datoteka]
```

Za starije Arduino Nano pločice potrebno FQBN treba biti ```arduino:avr:nano:cpu=atmega328old``` što označava da se koristi stariji *bootloader*.

Prijenos prevedene binarne datoteke:

```
arduino-cli upload -p [datoteka uređaja koja predstavlja pločicu] --fqbn [FQBN] [.ino datoteka]
```

Otvaranje serijske veze između računala i pločice može se napraviti naredbom:

```
arduino-cli monitor -p [datoteka uređaja koja predstavlja pločicu] --config [baud]
```

Kombinacija tipki *Ctrl + C* prekida serijsku vezu.

## Arduino Nano

[Arduino Nano](https://docs.arduino.cc/hardware/nano/#features) je mala i kompaktna verzija programabilne razvojne pločice. Ima sljedeće [karakteristike](https://docs.arduino.cc/resources/pinouts/A000005-full-pinout.pdf):

- koristi 8 bitni mikroupravljač ATmega328 koji sadrži:
	- takt od 16 MHz
	- 2 KiB RAM
	- 32 KiB Flash memorije
	- 1 KiB EEPROM
	- UART, I2C, SPI
- koristi USB za programiranje (USB na UART most), USB B mini priključak
- 14 digitalnih ulazno-izlaznih pinova (Dn oznaka) + 8 pinova koji imaju ulaze spojenih na analogno digitalni pretvarač (*eng. ADC - Analog to Digital Converter*), posebne funkcionalnosti određenih pinova
	- za I2C: pin A4 SDA, pin A5 SCL
	- za SPI: pin D11 COPI, pin D12 CIPO, pin D13 SCK, bilo koji pin za CS
	- za UART: pin D0 TX, pin D1 RX
	- pinovi s mogućnosti pulsno-širinske modulacije: D3, D5, D6, D9, D10, D11
- svi pinovi osim pinova A6 i A7 imaju mogućnost prosljeđivanje prekida
- napajanje 5 V, struja po pinu 20 mA:
	- pin Vin za vanjsko napajanje od 7 V do 12 V
	- dva pina za resetiranje
	- jedan 5 V izlaz
	- jedan 3.3 V izlaz

## Arduino Nano i RF 433 MHz modul

[RF 433 MHz odašiljač i prijemnik modul](https://www.alldatasheet.com/datasheet-pdf/view/1452032/ETC/433MHZ.html) je jeftin par modula koji se koristi u jednostavnim Arduino projektima gdje je potrebna bežična komunikacija. Moduli koriste amplitudnu modulaciju kako bi odašiljali i primali informacije. Kako bi olakšali slanje i primanje paketa podataka, preporučuje se koristiti *RadioHead.h* biblioteku koja će podatke enkapsulirati i dekapsulirati u pakete i upravljati RF modulima. Funkcije koje se mogu koristiti se nalaze [ovdje](https://www.airspayce.com/mikem/arduino/RadioHead/classRH__ASK.html).

Gotovi programi se nalaze u direktoriju [*transmitter*](transmitter) za odašiljač i [*receiver*](receiver) za prijemnik. Odašiljač šalje dvije poruke naizmjenično u intervalu od 1 sekunde dok prijemnik prima poruke i ispisuje ih na serijsku vezu. Datoteku odašiljača je potrebno prevesti i prebaciti na Arduino NANO pločicu na kojoj je spojen odašiljač, a datoteku prijemnika potrebno je prevesti i prebaciti na Arduinu NANO pločicu na kojoj je spojen prijemnik.

**Preporuka je koristiti zalemljene antene (obična žica) duljine 34.6 cm za veći raspon komunikacije.**

### Shema spojeva za RF module

```
        +--------------+          +--------------+                +--------------+          +--------------+
        | ARDUINO   5V +----------+ 5V    TX     |                | ARDUINO   5V +----------+ 5V    RX     |
        | NANO         |          |       MODUL  |                | NANO         |          |       MODUL  |
        |          D12 +----------+              |                |          D11 +----------+              |
        |              |          |              |                |              |          |              |
        |          GND +----------+ GND          |                |          GND +----------+ GND          |
        +--------------+          +--------------+                +--------------+          +--------------+
```
