#include <LiquidCrystal_I2C.h>
#include <Adafruit_Thermal.h>
#include <SoftwareSerial.h>
#include <avr/pgmspace.h>

volatile unsigned int sinyal = 0;
volatile unsigned long sonSinyalZamani = 0;
volatile unsigned int lira = 0;
volatile bool paraGeldimi = false;

const char metin1[] PROGMEM = "Antarktika'daki kara buzullari\nnin hacmi yaklasik 30 milyon km\nustu 3.Yani dunyadaki buzun %90'\ni,tatli suyun ise %70-85'i An\ntarktika'da bulunuyor.\n";
const char metin2[] PROGMEM = "Insanli uzay araclarina ait hiz\nrekoru Apollo 10'un.Apollo 10 u\nzay araci,26 Mayis 1969'da dunya\nya donusu sirasinda atmosfere gi\nrerken saatte 39.897 km hiza u\nlasti(Apollo 10'un kendi ucus ka\nyitlerindeki hizi 39.937 km/sa i\ndi.)\n";
const char metin3[] PROGMEM = "Antarktika'da hem kara hem de de\nniz buzullari var.Kara buzullari\nnin kalinligi ortalama 1,8 kilo\nmetreyken,bazi bolgelerde buz ka\nlinligi 4,8 kilometreye ulasabi\nliyor.\n";
const char metin4[] PROGMEM = "Kopekbaliklarinda yuzme kesesi\nbulunmaz.Bundan dolayi bircok ko\npekbaligi surekli yuzmek zorunda\ndir,aksi takdirde batarlar.\n";
const char metin5[] PROGMEM = "Google ceviri,internet sitelerin\nde karsilastigimiz 'Bunu da bege\nnebilirsiniz' onerilerinin ya da\nFacebook taki yuz tanima ozelli\ngi bugun gunluk hayatimizda bol\nca yararlandigimiz uygulamala\nrin arkasinda yapay zeka tekno\nlojisi var.\n";
const char metin6[] PROGMEM = "Gokadalari bir arada tutan kutle\ncekim kuvveti dogadaki dort te\nmel kuvvet arasinda en zayif ola\nnidir. Ancak etki mesafesi son\nsuzdur.Atom cekirdigini bir ara\nda tutan kuvvet olan guclu nukle\ner kuvvet ise kutlecekim kuvve\ntinden 10 ustu 37 kat daha guclu\nolmasina ragmen,sadece atom ce\nkirdegi olceginde etkilidir.\n";

const char metin7[] PROGMEM = "Kuzey Kutup Dairesi'nde yasayan\n"
"ren geyiklerinin gozleri bircok\n"
"memeli hayvandan farkli olarak\n"
"morotesi dalga boyundaki isinla\n"
"ri algilayabilir.Yani ren geyik\n"
"leri UV goruse sahiptir.\n";

const char metin8[] PROGMEM = "Dunya uzerinde her gun 2,5 ken\n"
"tilyon yani 2.500.000.000.000\n"
".000.000 bayt veri uretiliyor.\n"
"Dunyadaki verilerin %90'indan \n"
"fazlasi ise son iki yilda ure\n"
"tildi.\n";

const char metin9[] PROGMEM = "Insan vucudundaki damarlarin top\n"
"lam uzunlugu yaklasik 100.000 km\n"
"'dir.Diger bir ifadeyle damarla\n"
"rimiz Dunya'nin etrafini 2,5 ke\n"
"re dolasabilecek kadar uzundur.\n";

const char metin10[] PROGMEM = "Ayni anda hem nefes alip hem de\n"
"yutkunamayiz.Yutkunma ve nefes\n"
"alma surecleri arasinda koordi\n"
"nasyonu saglayan bu sistem ozel\n"
"likle uyku esnasinda hayatta kal\n"
"mamiz icin gereklidir.\n";

const char metin11[] PROGMEM = "Christiaan Huygens 1656 yilinda\n"
"sarkacli saatleri kesfetmeden\n"
"once kullanilan saatler zamani\n"
"bir gunde yaklasik 15 dakika ha\n"
"tali olcuyordu.Huygens'in sarkac\n"
"li saatlerinde bu hata 15 saniye\n"
"kadar dustu.\n";

const char metin12[] PROGMEM = "Antarktika'da deniz buzullarinin\n"
"kisin kapladigi toplam alan 18\n"
"milyon km2'ye kadar dusuyor.\n"
"Kuresel isinma onlenmezse hem\n"
"kara hem de deniz buzullari\n"
"erimeye devam edebilir.\n";

const char metin13[] PROGMEM = "Kutlesi 1.989.100.000.000.000.\n"
"000.000.000.t000.000.kg olan\n"
"Gunes,Gunes sistemi'nin toplam\n"
"kutlesinin neredeyse tamamini\n"
"-%99,86'sini- olusturur.\n";

const char metin14[] PROGMEM = "Uzayda kokulari dogrudan algila\n"
"mak mumkun olmasa da,astronotlar\n"
"uzay yuruyusu sirasinda kiyafet\n"
"lerine sinen kokularin metal ko\n"
"kusuna-ornegin kaynak sirasinda\n"
"aciga cikan dumaninkine-benzedi\n"
"gini soyluyor.\n";

const char metin15[] PROGMEM = "Kanser kaynakli olumlerin yakla\n"
"sik ucte biri hayatta tarzimiz\n"
"daki bes etkenle iliskili:vucut\n"
"-kutle indeksinin yuksek olusu,\n"
"dusuk sebze ve meyve tuketimi,\n"
"sigara kullanimi,alkol kullani\n"
"mi ve yetersiz fiziksel etkin\n"
"lik.\n";

const char metin16[] PROGMEM = "Sinir hucresinin turune gore de\n"
"gismekle birlikte sinir iletile\n"
"rinin hizi saatte yaklasik 430\n"
"kilometreye ulasabilir.Bu,bilgi\n"
"nin beynimizde bir Formula 1 a\n"
"racindan daha hizli aktarildigi\n"
"anlamina geliyor.\n";

const char metin17[] PROGMEM = "Antarktika 14 milyon km ustu 2'\n"
"lik yuzolcumuyle Turkiye'nin yak\n"
"lasik 17, Avrupa'nin ise yakla\n"
"sik 1,5 kati buyuklukte.\n";

const char metin18[] PROGMEM = "Antartika'da bilinen altmis ka\n"
"dar yanardag var. bunlarin en ak\n"
"tif olani 3794 metre yukseklige\n"
"sahip Erebus Yanardagi'dir.\n";

const char metin19[] PROGMEM = "Antartika dunyanin en ruzgarli\n"
"bolgesidir. Dunyadaki en yuksek\n"
"ruzgar hizi 320 km/sa ile Antar\n"
"tika'da kaydedildi.\n";

const char metin20[] PROGMEM = "Bugun ameliyat masasinda kulla\n"
"nilan aletlerin %70'ini Ibn-i\n"
"Sina bulmus ve kullanmistir.\n";

const char * const metinler[] PROGMEM = {
  metin1,
  metin2,
  metin3,
  metin4,
  metin5,
  metin6,
  metin7,
  metin8,
  metin9,
  metin10,
  metin11,
  metin12,
  metin13,
  metin14,
  metin15,
  metin16,
  metin17,
  metin18,
  metin19,
  metin20
};

char buffer[1024];


// Ekran
LiquidCrystal_I2C lcd(0x27, 16,2);

SoftwareSerial mySerial(11, 12); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(F("Serial Acildi!"));

  randomSeed(analogRead(A2));

  mySerial.begin(9600);
  printer.begin();

  Serial.println(F("Printer baslatildi!"));
  
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(10, OUTPUT); // 10-relayPin
  pinMode(13, OUTPUT); // 13 - buzzerPin

  Serial.println(F("G/C Tamamlandi!"));

  paraMakinesiniKapat();

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.home();
  lcd.print(F("SISTEM BASLIYOR"));
  lcd.setCursor(0,1);
  lcd.print(F("LUTFEN BEKLEYIN"));
  delay(2000);

  // Para Makinesini Aç!
  paraMakinesiniAc();
  delay(500);
  attachInterrupt(digitalPinToInterrupt(2), paraAttilar, RISING);
  
  lcd.clear();
  lcd.home();
  lcd.print(F("LUTFEN PARA ATIN"));
  lcd.setCursor(0,1);
  lcd.print(F("Tutar 0 Lira"));

  Serial.println(F("Sistem basladi!"));

  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW);
  delay(200);
  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW);
  delay(200);
  
}

void paraAttilar() {
  sinyal++;
  sonSinyalZamani = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long sonSinyaldenGecenZaman = millis() - sonSinyalZamani;
  
  if(sinyal > 0 && sonSinyaldenGecenZaman > 200) {
    if(sinyal > 2) {
      paraGeldimi = true;
      lira = lira + 1; 
    }
    sinyal = 0;
  }
  
  if(paraGeldimi) {
    lcd.setCursor(0,1);
    lcd.print("                ");
    lcd.setCursor(0,1);
    String veri = "Tutar " + String(lira) + " Lira";
    lcd.print(veri);
    paraGeldimi = false;
  }

  // Para varken, butona basılırsa
  if(lira > 0 && digitalRead(3) == HIGH) {
    bagisYap();
  }

  delay(50);
}

void paraMakinesiniKapat() {
  digitalWrite(10, HIGH);
}

void paraMakinesiniAc() {
  digitalWrite(10, LOW);
}

void bagisYap() {
  paraMakinesiniKapat();

  lcd.clear();
  lcd.home();
  lcd.print(F("TESEKKUR  EDERIZ"));
  lcd.setCursor(1,1);
  lcd.print(F("FIS  BASILIYOR"));
  delay(500);

  // Başlık kısmı
  printer.justify('C');
  printer.boldOn();
  printer.println(F("Biga Imam Hatip Ortaokulu\n"));

  // Bunları biliyor musunuz kısmı
  printer.boldOff();
  printer.println(F("################################\n"));
  printer.boldOn();
  printer.println(F("BUNU BILIYOR MUYDUNUZ?"));
  printer.boldOff();
  printer.justify('L');
  long rasgele = random(0,19);
  strcpy_P(buffer, (char*)pgm_read_word(&(metinler[rasgele]))); // Necessary casts and dereferencing, just copy. 
  printer.println(buffer);
  // Bitiş ve lira kısmı!
  printer.justify('C');
  printer.println(F("################################\n"));
  printer.println("Pin Pon oyunu icin " + String(lira) + " oyun hakki verir.\n");
  printer.println(String(lira) + F(" TL") + "- #" + String(rasgele) + "#");

  printer.feed(2);

  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW);
  delay(200);
  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW);
  delay(200);

  
  printer.sleep();
  delay(1500L);
  printer.wake();
  printer.setDefault();
  lira = 0;
  paraMakinesiniAc();
  sinyal = 0;
  lcd.clear();
  lcd.home();
  lcd.print(F("LUTFEN PARA ATIN"));
  lcd.setCursor(0,1);
  lcd.print(F("Tutar 0 Lira"));
}
