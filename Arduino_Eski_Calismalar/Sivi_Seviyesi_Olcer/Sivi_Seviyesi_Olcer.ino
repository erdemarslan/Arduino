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
#define TRIGPIN 8
#define ECHOPIN 9
#define MAX_MESAFE 100

#define LCD_ADRES 0x3F
#define LCD_SATIR 16
#define LCD_SUTUN 2

#define BUTONPIN 2


volatile bool kalibrasyon = false;
volatile int bos, dolu, olcum = 0;

NewPing sensor(TRIGPIN, ECHOPIN, MAX_MESAFE);
LiquidCrystal_I2C lcd(LCD_ADRES, LCD_SATIR, LCD_SUTUN);

void butonaBastim() {
  kalibrasyon = false;
  bos = 0;
  dolu = 0;
  olcum = 0;

  //kalibreEt();
}

void setup() {
  Serial.begin(9600);
  
  pinMode(BUTONPIN, INPUT);
  
  // LCD Ekranı başlat
  lcd.init();

  lcd.backlight();

  kalibreEt();
}

void loop() {
  // Devamlı kodlar!
  /*
  if(!kalibrasyon) {
    kalibreEt();
  }
  */
  
  olcum = sensor.ping_cm();
  Serial.println(olcum);

  int mililitre = map(olcum, bos, dolu, 0, 1000);
  int yuzde = map(olcum, bos, dolu, 0, 100);

  lcd.setCursor(8,0);
  lcd.print("       ");
  lcd.setCursor(8,0);
  //String ilksatir = String(mililitre) + " ml";
  //lcd.print(ilksatir);
  lcd.print(mililitre);

  lcd.setCursor(9,1);
  lcd.print("      ");
  lcd.setCursor(9,1);
  String ikincisatir = "%" + String(yuzde);
  lcd.print(ikincisatir);

  delay(1000);
}

void kalibreEt() {

  //detachInterrupt(digitalPinToInterrupt(BUTONPIN));
  
  lcd.setCursor(0,0);
  lcd.print("BOS KAP KOY VE");
  lcd.setCursor(0,1);
  lcd.print("BUTONA BAS");

  while(bos == 0) {
    int buton = digitalRead(BUTONPIN);
    if(buton == HIGH) {
      delay(100);
      bos = sensor.ping_cm();
      Serial.println(bos);
      delay(500);
    }
  }

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("DOLU KAP KOY VE");
  lcd.setCursor(0,1);
  lcd.print("BUTONA BAS");

  while(dolu == 0) {
    int buton = digitalRead(BUTONPIN);
    if(buton == HIGH) {
      delay(100);
      dolu = sensor.ping_cm();
      Serial.println(dolu);
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

  kalibrasyon = true;

  //attachInterrupt(digitalPinToInterrupt(BUTONPIN), butonaBastim, RISING);

  lcd.setCursor(0,0);
  lcd.print("MIKTAR: ");
  lcd.setCursor(0,1);
  lcd.print("DOLULUK: ");
}

