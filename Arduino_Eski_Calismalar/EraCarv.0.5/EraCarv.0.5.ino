#include <SoftwareSerial.h>
#include <Servo.h>
/*
 * EraCar v.0.5
 * Erdem ARSLAN
 * Bu program engelden kaçan arabayı kontrol eder. Daha sonra bluetooth da eklenecek!
 * 14.10.2017 15:32
 * 
 * Kullanılan Malzemeler
 *  2 adet motor
 *  1 adet motor sürücü
 *  1 adet servo motor
 *  1 adet hc-sr04 ultrasonik mesafe sensörü
 *  1 adet pil yuvası
 *  1 adet araç şasesi
 *  yeterince kablo
 *  4 adet pil
 *  Arduino Nano
 * 
 * PİN DİZİLİMİ
 * Motorlar - 4,5,6,7
 * Servo - 8
 * Motor Hız Kontrolleri 9,10
 * Mesafe Sensörü 11,12
 */

// Değişkenleri tanımlayalım
int solA, solB, sagA, sagB, servoPin, onAci, solAci, sagAci, trigPin, echoPin;
Servo motor;
SoftwareSerial bt(2,3);
int yon = 0;  // 0-dur, 1- ileri, 2-sola, 3 -saga, 4-geri


void setup() {
  // Pin Tanımlamaları
  solA = 4;
  solB = 5;
  sagA = 6;
  sagB = 7;
  servoPin = 8;
  trigPin = 11;
  echoPin = 12;
  onAci = 90;
  solAci = 180;
  sagAci = 0;

  Serial.begin(9600);

  pinMode(solA, OUTPUT);
  pinMode(solB, OUTPUT);
  pinMode(sagA, OUTPUT);
  pinMode(sagB, OUTPUT);
  pinMode(servoPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  /*
  motor.attach(servoPin);
  motor.write(onAci);
  delay(500);
  */
  bt.begin(9600);
  // motor ve pin testi
  araba_ileri(250);
}

void loop() {
  //bluetooth();
}
