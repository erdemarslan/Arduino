#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16,2);

const byte coinPin = 2;
const byte buttonPin = 3;
const byte motorPWM = 6;
const byte motorA = 4;
const byte motorB = 5;


volatile double lira = 0.00;
volatile int paraGeldimi = 0;

volatile int suAksin = 0;


void setup()
{
  pinMode(buttonPin, INPUT);
  pinMode(motorPWM, OUTPUT);
  pinMode(motorA, OUTPUT);
  pinMode(motorB, OUTPUT);
    lcd.init();
    //attachInterrupt(digitalPinToInterrupt(buttonPin), buttonPressed, RISING);
    attachInterrupt(digitalPinToInterrupt(coinPin), coinInserted, RISING);
    lcd.backlight();
    lcd.clear();
    lcd.home();
    lcd.print("Bakiye: 0 TL");
    lcd.setCursor(0,1);
    lcd.print("Motor: Durdu");
    
}

void coinInserted() {
  if(paraGeldimi == 0) {
    lira = lira + 0.25;
    paraGeldimi = 1;
  }
}

void buttonPressed() {
  if(suAksin == 0) {
    suAksin = 1;
  }
}

void loop()
{
  if(digitalRead(buttonPin) == HIGH) {
    lcd.setCursor(7,1);
    lcd.print("         ");
    lcd.setCursor(7,1);
    lcd.print("Calisiyor");
    analogWrite(motorPWM, 255);
    digitalWrite(motorA, LOW);
    digitalWrite(motorB, HIGH);
    delay(1000);
    analogWrite(motorPWM, 0);
    digitalWrite(motorA, LOW);
    digitalWrite(motorB, LOW);
    lcd.setCursor(7,1);
    lcd.print("         ");
    lcd.setCursor(7,1);
    lcd.print("Durdu");
    suAksin = 0;
  }
  
  if(paraGeldimi == 1) {
    lcd.setCursor(8,0);
    lcd.print("       ");
    lcd.setCursor(8,0);
    String veri = String(lira) + " TL";
    lcd.print(veri);
    paraGeldimi = 0;
  }

}
