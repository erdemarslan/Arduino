#include <SPI.h>
#include <SD.h>


/*
 * Kapı Otomati
 * v.0.1-beta
 * Erdem ARSLAN
 * 19.07.2017 Başlangıç
 * 
 * Modüller
 * RFID-RC522 (SPI)
 * 5110 Ekranı (SPI)
 * SD Kart Modülü (SPI)
 * NeoPixel Led WS8212 (Dijital Pin)
 * 4 Button Analog girişten alınmış! (A0)
 * 16x2 LCD Ekran I2C (I2C)
 * Buzzer (Dijital Pin)
 * Keypad ( Sonradan I2C protokolü ile eklenecek)
 * 
 */

// Modül Pin Tanımlamaları
#define BUZZER 4
#define ANALOG_TUSLAR A0




/*
const int SDKartPin = 3;
const int LedPin = 4;
const int BuzzerPin = 5;
const int RFID_Rst = 6;
const int RFID_Ss = 7;
const int tft_rst = 8; // Arduino Reset-Pin
const int tft_cs = 9; // Arduino-Pin an Display CS
const int tft_dc = 10; // Arduino-Pin an Display A0
const int AnalogButonPin = A0;

// SD Kart
String SD_YONETICI = "/MASTER/";
String SD_KARTLAR = "/KART/";
//File dosya;

*/

// KART OKUYUCU
//MFRC522 rfid(RFID_Ss, RFID_Rst);
//MFRC522::MIFARE_Key anahtar;

// LCD Ekran
//LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ANALOG_TUSLAR, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(analogRead(ANALOG_TUSLAR));
  delay(500);
}
