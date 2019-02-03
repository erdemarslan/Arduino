/*
 * Biga İmam Hatip Ortaokulu
 * 2017-2018 TÜBİTAK 4006 Sergisi
 * Hava Nasıl Oralarda?
 * 
 * 
 * 
 */
#include <Wire.h>
#include <SPI.h>
#include <MQ135.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>
#include <SD.h>
#include <DHT.h>


// DHT
const byte DHTTURU = DHT22;
const byte DHTPIN = 6;


// MQ-135
const byte MQPIN = A0;
#define RZERO = 822.60;


// SD Kart
const byte SDPIN = 53;


// Toz Sensörü
const byte TOZLEDPIN = 7;
const byte TOZOLCUMPIN = A1;
unsigned int orneklemeZamani = 280;
unsigned int degisimZamani = 40;
unsigned int uykuZamani = 9680;
float voOlculen = 0.00;
float hesaplananVoltaj = 0.00;
float tozOrani = 0.00;


// Buton, Buzzer ve Ledler
const byte butonPin = 2;
const byte ledPinK = 3;
const byte ledPinY = 4;
const byte ledPinM = 5;
const byte buzzerPin = A6;


// Diğer değişkenler
volatile bool kayitBaslasinmi = false;
float sicaklik = 0.00;
float nem = 0.00;
float sicaklikEndeksi = 0.00;
float co2 = 0.00;
String tarihDegeri, saatDegeri;
String gun, ay, yil, sa, da, sn;

// Ekran işe ilgili değişkenler
byte ekranModu = 2;
byte oncekiEkranModu = 0;
unsigned long sonIslemZamani = 0;
unsigned long sonKayitZamani = 0;
const unsigned long beklemeSuresi = 60000;
const int ekranSuresi = 5000;
const unsigned long isinmaSuresi = 120000;
unsigned long sonEkranZamani = 0;
int maxKayitSayisi = 100;
int kayitSayisi = 1;


// Ekranı Tanımla
LiquidCrystal_I2C lcd(0x27, 16,2);

// DHT Sıcaklık ve Nem Sensörünü Tanımla!
DHT dht(DHTPIN, DHTTURU);

// Saati Tanımla
DS1307 saat;

// MQ-135 Hava Kalitesi Sensörünü Tanımla
MQ135 havaSensoru = MQ135(MQPIN);


void butonaBasildi() {
  if(!kayitBaslasinmi) {
    kayitBaslasinmi = true;
    sonKayitZamani = millis();
  } else {
    kayitBaslasinmi = false;
    sonKayitZamani = millis();
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(butonPin, INPUT);
  pinMode(ledPinK, OUTPUT);
  pinMode(ledPinY, OUTPUT);
  pinMode(ledPinM, OUTPUT);
  pinMode(TOZLEDPIN, OUTPUT);
  pinMode(buzzerPin, OUTPUT);


  
  
  // Ekranı Başlat
  lcd.init();
  lcd.backlight();
  lcd.clear();

  digitalWrite(ledPinK, HIGH);

  // Ekrana uyarı ver!
  lcd.setCursor(4,0);
  lcd.print(F("BIGA IHO"));
  lcd.setCursor(2, 1);
  lcd.print(F("TUBITAK 4006"));
  delay(3000);
  lcd.clear();

  lcd.setCursor(3, 0);
  lcd.print(F("HAVA NASIL"));
  lcd.setCursor(3,1);
  lcd.print(F("ORALARDA ?"));
  delay(3000);

  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print(F("BASLATILIYOR"));
  

  lcd.setCursor(6,1);
  lcd.print(F("SAAT"));
  delay(1500);
  
  // Wire kütüphanesini başlar
  Wire.begin();
  // Saati başlat
  saat.begin();
  
  // saat başlatılmamışsa başlat!
  if(!saat.isrunning()) {
    saat.adjust(DateTime(__DATE__, __TIME__));
  }

  //saat.adjust(DateTime(__DATE__, __TIME__));

  
  lcd.setCursor(0,1);
  lcd.print("                ");
  lcd.setCursor(1,1);
  lcd.print(F("SICAKLIK - NEM"));
  delay(1500);
  
  // Sıcaklık ve Nem Sensörünü Başlat!
  dht.begin();

  lcd.setCursor(0,1);
  lcd.print("                ");
  lcd.setCursor(4,1);
  lcd.print(F("SD  KART"));
  delay(1500);
  
  // SD Kartı Başlat
  if(!SD.begin(SDPIN)) {
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print(F("OLUMCUL HATA"));
    lcd.setCursor(2,1);
    lcd.print(F("SD  KART YOK"));
    while (1);
  }


  lcd.setCursor(0,1);
  lcd.print("                ");
  lcd.setCursor(2,1);
  lcd.print(F("TOZ  SENSORU"));
  delay(1500);

  lcd.setCursor(0,1);
  lcd.print("                ");
  lcd.setCursor(2,1);
  lcd.print(F("HAVA SENSORU"));
  delay(1500);

  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print(F("HAVA SENSORU"));
  lcd.setCursor(4,1);
  lcd.print("ISINIYOR");
  delay(isinmaSuresi);
  //delay(1500);

  digitalWrite(ledPinK, LOW);
  delay(200);

  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("SISTEM");
  lcd.setCursor(3,1);
  lcd.print("HAZIRLANDI");
  
  for(int i = 0; i < 3; i++) {
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(ledPinK, HIGH);
    delay(300);
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPinK, LOW);
    delay(200);
  }
  delay(1500);
  lcd.clear();

  attachInterrupt(digitalPinToInterrupt(butonPin), butonaBasildi, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(ledPinY) == LOW && kayitBaslasinmi == true) {
    digitalWrite(ledPinY, HIGH);
  }

  if(digitalRead(ledPinY) == HIGH && kayitBaslasinmi == false) {
    digitalWrite(ledPinY, LOW);
  }

  if(millis() - sonIslemZamani > ekranSuresi) {
    ekranModu++;
    if(ekranModu > 2) {
      ekranModu = 0;
    }
    sonIslemZamani = millis();
  }

  


  if(ekranModu == 0) {
    // Saati göster!
    if(oncekiEkranModu != ekranModu) {
      lcd.clear();
      saatiAl();
      lcd.setCursor(3,0);
      lcd.print(tarihDegeri);
      lcd.setCursor(4,1);
      lcd.print(saatDegeri);

      oncekiEkranModu = ekranModu;
      sonEkranZamani = millis();
    }
    if(millis() - sonEkranZamani > 1000) {
      saatiAl();
      lcd.setCursor(3,0);
      lcd.print(tarihDegeri);
      lcd.setCursor(4,1);
      lcd.print(saatDegeri);
      sonEkranZamani = millis();
    }
  }

  if(ekranModu == 1) {
    if(oncekiEkranModu != ekranModu) {
      sicaklikOlc();
      lcd.clear();
      lcd.setCursor(0,0);
      String sv = "SICAKLIK: " + String(sicaklik) + "C";
      String sn = "NEM: %" + String(nem);
      lcd.print(sv);
      lcd.setCursor(0,1);
      lcd.print(sn);
      oncekiEkranModu = ekranModu;
    }
  }

  if(ekranModu == 2) {
    if(oncekiEkranModu != ekranModu) {
      tozOlc();
      delay(50);
      co2Olc();
      delay(50);
      String tz = "TOZ: " + String(tozOrani) + " ppm";
      String co = "CO2: " + String(co2) + " ppm";

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(tz);
      lcd.setCursor(0,1);
      lcd.print(co);
      oncekiEkranModu = ekranModu;
    }
  }

  if(kayitBaslasinmi) {
    // her 1 dakikada bir kaydet!
    if(millis() - sonKayitZamani > beklemeSuresi) {
      // artık kaydedebiliriz!
      // Önce yeşil ledi söndürelim!
      digitalWrite(ledPinY, LOW);
      delay(250);
      // mavi ledi yakalaım!
      digitalWrite(ledPinM, HIGH);

      // ölçümleri ve saati tekrar alalım ki yanlışlık olmasın
      co2Olc();
      delay(50);
      tozOlc();
      delay(50);
      saatiAl();
      delay(50);

      String dosyaAdi = yil + ay + gun + ".CSV";
    
      // Tarih, Saat, Sıcaklık, Nem, Sıcaklık Endeksi, Toz Oranı, CO2 oranı
      String veri = String(kayitSayisi) + "," + tarihDegeri + "," + sa + ":" + da + "," + String(sicaklik) + "," + String(nem) + "," + String(sicaklikEndeksi) + "," + String(tozOrani) + "," + String(co2);

      File dosya = SD.open(dosyaAdi, FILE_WRITE);

      if(dosya) {
        dosya.println(veri);
        dosya.close();
      }
      delay(50);
      

      sonKayitZamani = millis();
      sonEkranZamani = millis();

      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("KAYDEDILDI");
      String sn = "";
      if(kayitSayisi < 10) {
        sn = "#00" + String(kayitSayisi);
      } else if(kayitSayisi > 9 && kayitSayisi < 100) {
        sn = "#0" + String(kayitSayisi);
      }
      else {
        sn = "#" + String(kayitSayisi);
      }
      
      lcd.setCursor(6,1);
      lcd.print(sn);

      digitalWrite(buzzerPin, HIGH);
      delay(500);
      digitalWrite(buzzerPin, LOW);
      delay(500);
      
      digitalWrite(ledPinM, LOW);
      delay(250);
      
      kayitSayisi++;
      if(kayitSayisi > maxKayitSayisi) {
        kayitSayisi = 1;
        kayitBaslasinmi = false;
        for(int i = 0; i < 5; i++) {
          digitalWrite(buzzerPin, HIGH);
          delay(500);
          digitalWrite(buzzerPin, LOW);
          delay(200);
        }
      }
    }
  }
}


void saatiAl() {
  tarihDegeri = "q";
  saatDegeri = "w";

  DateTime simdi = saat.now();

  
  gun = simdi.day() > 9 ? String(simdi.day(), DEC) : "0" + String(simdi.day(), DEC);
  ay = simdi.month() > 9 ? String(simdi.month(), DEC) : "0" + String(simdi.month(), DEC);
  yil = String(simdi.year(), DEC);
  sa = simdi.hour() > 9 ? String(simdi.hour(), DEC) : "0" + String(simdi.hour(), DEC);
  da = simdi.minute() > 9 ? String(simdi.minute(), DEC) : "0" + String(simdi.minute(), DEC);
  sn = simdi.second() > 9 ? String(simdi.second(), DEC) : "0" + String(simdi.second(), DEC);
  
  
  tarihDegeri = gun + "." + ay + "." + String(simdi.year(), DEC);
  saatDegeri = sa + ":" + da + ":" + sn;
}

void co2Olc() {
  co2 = havaSensoru.getPPM();
}

void sicaklikOlc() {
  sicaklik = dht.readTemperature();
  nem = dht.readHumidity();
  sicaklikEndeksi = dht.computeHeatIndex(sicaklik, nem);
}

void tozOlc() {
  digitalWrite(TOZLEDPIN, LOW);
  delayMicroseconds(orneklemeZamani);

  voOlculen = analogRead(TOZOLCUMPIN);

  delayMicroseconds(degisimZamani);
  digitalWrite(TOZLEDPIN, HIGH);

  hesaplananVoltaj = voOlculen*(5.0/1024);
  tozOrani = 0.17*hesaplananVoltaj-0.1;

  /*
  Serial.println(voOlculen);
  Serial.println(hesaplananVoltaj);
  Serial.println(tozOrani);
  */
  
  if(tozOrani < 0) {
    tozOrani = 0.00;
  }
}

