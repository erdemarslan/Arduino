/*
 * GSM Kontrol
 * 
 * Biga İmam Hatip Ortaokulu
 * Robocanlar v.1.0
 * 
 * Erdem ARSLAN
 * Fen Bilimleri Öğretmeni
 */
#include <SoftwareSerial.h>

SoftwareSerial gsm(10,11);
const int ledKirmizi = 4;
const int ledYesil = 5;
const int ledMavi = 6;

String _data;
bool _devam;
unsigned long _zaman;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledKirmizi, OUTPUT);
  pinMode(ledYesil, OUTPUT);
  pinMode(ledMavi, OUTPUT);

  _data.reserve(255);
  _devam = false;
  
  gsm.begin(9600);
  Serial.begin(9600);

  delay(2000);

  gsm.println(F("AT+CFUN=1"));
  bekle(F("OK"), F("ERROR"), 5000);

  gsm.println(F("AT+CMGF=1"));
  bekle(F("OK"), F("ERROR"), 5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(gsm.available()) {
    _data = gsm.readString();

    Log(_data);

    // Kırmızı Açık
    if(_data.indexOf(F("K.ACIK")) != -1) {
      digitalWrite(ledKirmizi, HIGH);
      delay(500);
    }

    // Kırmızı Kapalı
    if(_data.indexOf(F("K.KAPALI")) != -1) {
      digitalWrite(ledKirmizi, LOW);
      delay(500);
    }

    // Yeşil Açık
    if(_data.indexOf(F("Y.ACIK")) != -1) {
      digitalWrite(ledYesil, HIGH);
      delay(500);
    }

    // Yeşil Kapalı
    if(_data.indexOf(F("Y.KAPALI")) != -1) {
      digitalWrite(ledYesil, LOW);
      delay(500);
    }

    // Mavi Açık
    if(_data.indexOf(F("M.ACIK")) != -1) {
      digitalWrite(ledMavi, HIGH);
      delay(500);
    }

    // Mavi Kapalı
    if(_data.indexOf(F("M.KAPALI")) != -1) {
      digitalWrite(ledMavi, LOW);
      delay(500);
    }
  }
}


// Verilen at komutunu çalıştırır!
int bekle(String istenilen, String hatali, int bekleme) {

  _devam = false;
  _zaman = millis();
  int sonuc = 0;
  while(!_devam) {
    if(gsm.available()) {
      _data = gsm.readString();
      Log(_data);
      if(_data.indexOf(istenilen) != -1) {
        sonuc = 1;
        _devam = true;
      } else if(_data.indexOf(hatali) != -1) {
        sonuc = 2;
        _devam = true;
      } else {
        sonuc = 3;
        _devam = true;
      }
    }

    if(millis() - _zaman > bekleme && _devam == false) {
      Log(F("AT Komutunu bekleme suresi asildi!"));
      _devam = true;
    }
  }

  return sonuc;
}

void Log(String metin) {
  Serial.println(metin);
}
