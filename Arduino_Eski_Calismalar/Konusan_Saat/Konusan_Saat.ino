/*
 * Erdem Arslan
 * Biga İmam Hatip Ortaokulu
 * 
 */


#include <Arduino.h>
#include <TM1637Display.h>
#include <Wire.h>
#include "RTClib.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mp3Serial(10, 11); // RX, TX
DFRobotDFPlayerMini mp3;


#define CLK 6
#define DIO 7
#define BUTTON 2
#define DURUM 4
volatile bool tusaBasildimi = false;
volatile bool sesCaliyormu = false;
bool ikiNokta = true;

TM1637Display ekran(CLK, DIO);
DS1307 saat;

void haydiSoyle() {
  if(!tusaBasildimi && !sesCaliyormu) {
    tusaBasildimi = true;
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(BUTTON, INPUT);
  pinMode(DURUM, INPUT);
  Serial.begin(9600);

  
  Wire.begin();
  saat.begin();
  ekran.setBrightness(4, true);
  
  if (! saat.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    saat.adjust(DateTime(__DATE__, __TIME__));
  }

  mp3Serial.begin(9600);

  if (!mp3.begin(mp3Serial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("MP3 Modulu Baslayamadi:"));
    Serial.println(F("1.Kablolari kontrol edin!"));
    Serial.println(F("2.SD Kart yerlestirin!"));
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }

  mp3.volume(30);

  attachInterrupt(digitalPinToInterrupt(BUTTON), haydiSoyle, RISING);
}

void loop() {

  // buradan devam
  DateTime simdi = saat.now();
  static unsigned long sonSaatGosterimi = millis();

  if(millis() - sonSaatGosterimi > 1000) {
    int saatSayisi = (simdi.hour()) * 100;
    saatSayisi = saatSayisi + simdi.minute();

    if(ikiNokta) {
      ekran.showNumberDecEx(saatSayisi, 64);
    } else {
      ekran.showNumberDecEx(saatSayisi, 63);
    }

    ikiNokta = !ikiNokta;
    sonSaatGosterimi = millis();
  }

  if(tusaBasildimi == true && sesCaliyormu == false) {
    
    sesCaliyormu = true;
    mp3.playFolder(15,15); // Saat!
    bekle();
    
    
    int saat = simdi.hour();
    int saat_onluk = saat/10;
    int saat_birlik = saat%10;
    
    int dakika = simdi.minute();
    int dakika_onluk = dakika/10;
    int dakika_birlik = dakika%10;
    

    switch(saat_onluk) {
      case 0:
        mp3.playFolder(15,0);
        bekle();
      break;

      case 1:
        mp3.playFolder(15,10);
        bekle();
      break;

      case 2:
        mp3.playFolder(15,11);
        bekle();
      break;
    }
    
    switch(saat_birlik) {
      case 0:
        mp3.playFolder(15,0);
        bekle();
      break;

      case 1:
        mp3.playFolder(15,1);
        bekle();
      break;

      case 2:
        mp3.playFolder(15,2);
        bekle();
      break;

      case 3:
        mp3.playFolder(15,3);
        bekle();
      break;

      case 4:
        mp3.playFolder(15,4);
        bekle();
      break;

      case 5:
        mp3.playFolder(15,5);
        bekle();
      break;

      case 6:
        mp3.playFolder(15,6);
        bekle();
      break;

      case 7:
        mp3.playFolder(15,7);
        bekle();
      break;

      case 8:
        mp3.playFolder(15,8);
        bekle();
      break;

      case 9:
        mp3.playFolder(15,9);
        bekle();
      break;
    }

    switch(dakika_onluk) {
      case 0:
        mp3.playFolder(15,0);
        bekle();
      break;

      case 1:
        mp3.playFolder(15,10);
        bekle();
      break;

      case 2:
        mp3.playFolder(15,11);
        bekle();
      break;

      case 3:
        mp3.playFolder(15,12);
        bekle();
      break;

      case 4:
        mp3.playFolder(15,13);
        bekle();
      break;

      case 5:
        mp3.playFolder(15,14);
        bekle();
      break;
    }
    
    switch(dakika_birlik) {
      case 0:
        mp3.playFolder(15,0);
        bekle();
      break;

      case 1:
        mp3.playFolder(15,1);
        bekle();
      break;

      case 2:
        mp3.playFolder(15,2);
        bekle();
      break;

      case 3:
        mp3.playFolder(15,3);
        bekle();
      break;

      case 4:
        mp3.playFolder(15,4);
        bekle();
      break;

      case 5:
        mp3.playFolder(15,5);
        bekle();
      break;

      case 6:
        mp3.playFolder(15,6);
        bekle();
      break;

      case 7:
        mp3.playFolder(15,7);
        bekle();
      break;

      case 8:
        mp3.playFolder(15,8);
        bekle();
      break;

      case 9:
        mp3.playFolder(15,9);
        bekle();
      break;
    }

    sesCaliyormu = false;
    tusaBasildimi = false;
  }
}

void bekle() {
  delay(100);
  while(digitalRead(DURUM) == LOW) {
    delay(50);
  }
}

