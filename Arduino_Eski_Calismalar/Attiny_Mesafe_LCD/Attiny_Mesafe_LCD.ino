#include <TinyWireM.h>      // Wire/I2C library for Trinket and Gemma
#include <LiquidCrystal_attiny.h>

LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int trigPin = 1;
int echoPin = 4;

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  lcd.init();
  lcd.backlight();
  lcd.print("Mesafe");

  lcd.setCursor(5,1);
  lcd.print("cm");
}

void loop() {
  // put your main code here, to run repeatedly:
  int uz = uzunluk_olc();

  lcd.setCursor(0,1);
  lcd.print(F("    "));
  lcd.setCursor(0,1);
  lcd.print(uz);

  delay(1000);
}

int uzunluk_olc() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  int zaman = pulseIn(echoPin, HIGH);
  int mesafe = zaman / 2 / 29.1;
  return mesafe;
}
