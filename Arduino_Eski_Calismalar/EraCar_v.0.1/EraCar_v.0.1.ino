#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
#include <Servo.h>

// Bilgiler
/*
 * Multi Araba v.0.1 Rev.01
 * EraCar v.0.1
 * Erdem ARSLAN
 * erdemsaid@gmail.com
 * 14/08/2017
 * 
 * Özellikler:
 * 3 Farklı Modda Çalışma
 *  1. Mod - Engelden Kaçan
 *  2. Mod - Bluetooth Kontrolü
 *  3. Mod - Çizgi İzleyen
 * 
 * Bağlı Modüller
 * Arduino UNO CH340G Klon
 * L293B ile yapılmış Era Motor v.0.4 Motor Sürücü
 * HC-06 Bluetooth Modülü
 * I2C LED 128x64 Ekran
 * 2'li Dip Switch
 * WS8212B 8'li Adreslenebilir Led
 * 3 Adet TCT5000 Çizgi izleme modülü
 * 1 adet SG90 servo motor
 * 1 adet HC-SR04 ultrasonik mesafe sensörü
 * 
 * Pin Bağlantıları
 *  - Switch 0-1
 *  - Bluetooth 2-3
 *  - Servo 4
 *  - Motor PWM Pinleri 5-6
 *  - Motorlar 7-8-9-10
 *  - Adreslenebilir LED pini 11
 *  - HC-SR04 Ultrasonik Mesafe Sensörü 12-13
 *  - Çizgi İzleme Sensörleri A0-A1-A2
 *  - LED Ekran A4-A5
 *  
 * Switch Pinleri
 *  0-0 Bekleme Modu
 *  1-0 Engelden Kaçan
 *  1-1 Bluetooth Kontrollü
 *  0-1 Çizgi İzleyen
 *  
 */


int solA, solB, sagA, sagB, solH, sagH, trigPin, echoPin, mod, onAci, solAci, sagAci, solGoz, sagGoz, onGoz, arabaYon, arabaEskiYon;

SoftwareSerial BT(2,3); // Bluetooth Bağlantısı
Servo motor;
Adafruit_NeoPixel led = Adafruit_NeoPixel(8, 11, NEO_GRB + NEO_KHZ800);

// Araba Yönü
// araba_yon 0 -> duruyor
// araba_yon 1 -> ileri
// araba_yon 2 -> geri
// araba_yon 3 -> sol
// araba_yon 4 -> sag



void setup() {
  // Kurulum Kodları
  Serial.begin(9600);

  pinMode(A3, OUTPUT);
  digitalWrite(A3, HIGH);
  delay(500);
  
  // Önce Modu Belirle
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  mod_belirle();

  delay(500);
  digitalWrite(A3, LOW);

  arabaYon = 0;
  arabaEskiYon = 0;
  

  // Mesafe Sensörü Pinleri
  trigPin = 12;
  echoPin = 13;
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Çizgi izleme Gözleri
  sagGoz = A0;
  onGoz = A1;
  solGoz = A2;

  // Motor Pinlerini Belirle ve Tanımla
  solA = 8;
  solB = 7;
  sagA = 9;
  sagB = 10;
  solH = 5;
  sagH = 6;
  pinMode(solH, OUTPUT);
  pinMode(sagH, OUTPUT);
  pinMode(solA, OUTPUT);
  pinMode(solB, OUTPUT);
  pinMode(sagA, OUTPUT);
  pinMode(sagB, OUTPUT);
  digitalWrite(solH, HIGH);
  digitalWrite(sagH, HIGH);

  // Servo Ayarları
  onAci = 90;
  solAci = 180;
  sagAci = 0;
  motor.attach(4); // motor 4 nolu pinden kontrol ediliyor!
  for(int i = sagAci; i <= solAci; i++) {
    motor.write(i);
    delay(5); 
  }
  for(int k = solAci; k > onAci; k--) {
    motor.write(k);
    delay(5); 
  }

  // LED leri başlatıp ayarlıyoruz
  led.begin();
  led.show();
  led_cakar();
  
  // Bluetooth Ayarları
  BT.begin(9600);
  

  
  
  
  //araba_ileri(250);
}

void loop() {
  // Moda göre iş yapalım

  if(mod == 0) {
    yon_belirle(0);
    araba_dur(10);
  }
  else if(mod == 1) {
    engelden_kacan();
  }
  else if(mod == 2) {
    bluetooth();
  }
  else if(mod == 3) {
    cizgi_izleyen();
  }
  else {
    yon_belirle(0);
    araba_dur(10);
  }
  /*
  if (BT.available()) {
    Serial.write(BT.read());
  }
  if (Serial.available()) {
    BT.write(Serial.read());
  }
  */
}
