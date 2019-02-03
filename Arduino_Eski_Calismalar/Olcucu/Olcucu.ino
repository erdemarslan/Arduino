#include <NewPing.h> // HC-SR04 mesafe sensörü için kütüphane
#include <LiquidCrystal_I2C.h> // Ekran kütüphanesi

const int butonPin = 2;
const int trigPin = 7;
const int echoPin = 8;
const int maxMesafe = 200;

volatile int bosMesafe = 0;
volatile int boslukBoyu = 0;
volatile int cisminBoyu = 0;
volatile bool kurulumDevamEtsinmi = false;

volatile int oncekiEkran = 0;
volatile int simdikiEkran = 0;

LiquidCrystal_I2C lcd(0x27, 16,2); // LCD yi burada tanımladık.
NewPing sensor(trigPin, echoPin, maxMesafe);
void butonaBastim() {
  // Bu kodlar sadece kurulum esnasında çalışacak!
  if(kurulumDevamEtsinmi == false) {
    bosMesafe = sensor.ping_cm();
    Serial.print("Bos mesafe :");
    Serial.println(bosMesafe);
    kurulumDevamEtsinmi = true;
  }
  // burası da kurulum dışında çalışacak!
  else {
    boslukBoyu = 0;
    cisminBoyu = 0;
    
    boslukBoyu = sensor.ping_cm();
    cisminBoyu = bosMesafe - boslukBoyu;

    Serial.print("Bosluk boyu: ");
    Serial.println(boslukBoyu);
    Serial.print("Cismin boyu: ");
    Serial.println(cisminBoyu);
    simdikiEkran = 1;
  }
}
void setup() {
  Serial.begin(9600);
  // başlangıç kodları da buraya yazılacak!
  attachInterrupt(digitalPinToInterrupt(butonPin), butonaBastim, RISING);
  
  // LCD yi başlatıyoruz!
  lcd.init();
  lcd.backlight();

  // LCD ekrana yazı yazdırıyoruz!
  lcd.home();
  lcd.print("OLCUM ICIN");
  lcd.setCursor(0,1);
  lcd.print("BUTONA BASIN");

  while(kurulumDevamEtsinmi == false) {
    ;
  }
  
  delay(200);
  lcd.clear();
  lcd.home();
  lcd.print("BOS MESAFE :");
  lcd.setCursor(0,1);
  lcd.print(bosMesafe);
  lcd.setCursor(4,1);
  lcd.print("cm");
  
  delay(3000);

  lcd.clear();
  lcd.home();
  lcd.print("OLCUM ICIN");
  lcd.setCursor(0,1);
  lcd.print("BUTONA BASIN");
}

void loop() {
  // Ana kodlarımız buraya konulacak!
  if(simdikiEkran == 1) {
    lcd.clear();
    lcd.home();
    lcd.print("OGRENCININ BOYU :");
    lcd.setCursor(0,1);
    lcd.print(cisminBoyu);
    lcd.setCursor(4,1);
    lcd.print("cm");
    
    delay(5000);
    simdikiEkran = 0;
  } else {
    lcd.clear();
    lcd.home();
    lcd.print("OLCUM ICIN");
    lcd.setCursor(0,1);
    lcd.print("BUTONA BASIN");
  }
}
