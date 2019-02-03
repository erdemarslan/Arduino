/*
 * Sıvı Seviyesi Ölçümü
 * Litre olarak hesaplama dahil.
 * 
 * Biga İmam Hatip Ortaokulu
 * Robocanlar v.1.0
 * 
 * Erdem ARSLAN
 * Fen Bilimleri Öğretmeni
 */

#include <NewPing.h>
#include <LiquidCrystal_I2C.h>

// Mesafe Sensörü Tanımlamaları
#define TRIGPIN 7
#define ECHOPIN 6
#define MAX_MESAFE 250

#define LCD_ADRES 0x3F
#define LCD_SATIR 16
#define LCD_SUTUN 2

#define BUTONPIN 2

const int BEKLEME = 5000;

volatile bool kalibrasyon, olcumOldumu = false;
volatile int bos, olcum = 0;

NewPing sensor(TRIGPIN, ECHOPIN, MAX_MESAFE);
LiquidCrystal_I2C lcd(LCD_ADRES, LCD_SATIR, LCD_SUTUN);

void butonaBastim() {
  olcum = sensor.ping_cm();

  int sonuc = bos - olcum;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("BOYUNUZ OLCULDU:");
  lcd.setCursor(0,1);
  String metin = String(sonuc) + " cm";
  lcd.print(metin);

  olcumOldumu = true;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(BUTONPIN, INPUT);
  // LCD Ekranı başlat
  lcd.init();
  lcd.backlight();
  kalibreEt();
}

void loop() {
  // put your main code here, to run repeatedly:
  // Devamlı kodlar!
  /*
  if(!kalibrasyon) {
    kalibreEt();
  }
  */
  if(olcumOldumu) {
    delay(BEKLEME);
    lcd.clear();
    olcum = 0;
    olcumOldumu = false;
    lcd.setCursor(0,0);
    lcd.print("BOYUNUZU OLCMEK");
    lcd.setCursor(0,1);
    lcd.print("ICIN TUSA BASIN");
  }
}

void kalibreEt() {

  detachInterrupt(digitalPinToInterrupt(BUTONPIN));
  
  lcd.setCursor(0,0);
  lcd.print("BOS KAP KOY VE");
  lcd.setCursor(0,1);
  lcd.print("BUTONA BAS");

  while(bos == 0) {
    int buton = digitalRead(BUTONPIN);
    if(buton == HIGH) {
      delay(100);
      bos = sensor.ping_cm();
      delay(500);
    }
  }
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("KALIBRASYON");
  lcd.setCursor(0,1);
  lcd.print("YAPILIYOR...");
  delay(1000);
  lcd.clear();

  attachInterrupt(digitalPinToInterrupt(BUTONPIN), butonaBastim, RISING);

  lcd.setCursor(0,0);
  lcd.print("BOYUNUZU OLCMEK");
  lcd.setCursor(0,1);
  lcd.print("ICIN TUSA BASIN");
}



