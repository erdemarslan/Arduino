#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16,2);

const byte coinPin = 2;
const byte buttonPin = 3<;
const byte relayPin = 4;
const byte motorPin = 9;

volatile double lira = 0.00;
volatile int paraGeldimi = 0;
volatile int paraKabul = 0;

volatile int suAksin = 0;


void setup() {
  
  pinMode(coinPin, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(relayPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
  digitalWrite(relayPin, LOW);
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
  if(paraKabul == 0 && paraGeldimi == 0) {
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
  if(paraGeldimi == 1) {
    lcd.setCursor(8,0);
    lcd.print("       ");
    lcd.setCursor(8,0);
    String veri = String(lira) + " TL";
    lcd.print(veri);
    paraGeldimi = 0;
  }
  if(digitalRead(buttonPin) == HIGH) {
    lcd.setCursor(7,1);
    lcd.print("         ");
    lcd.setCursor(7,1);
    paraKabul = 1;
    digitalWrite(relayPin, HIGH);
    
    lcd.print("Calisiyor");
    delay(100);
    digitalWrite(motorPin, HIGH);
    delay(5000);
    digitalWrite(motorPin, LOW);
    delay(100);
    digitalWrite(relayPin, LOW);
    delay(100);
    paraKabul = 0;
    lcd.setCursor(7,1);
    lcd.print("         ");
    lcd.setCursor(7,1);
    lcd.print("Durdu");
    suAksin = 0;
  }

  
  
  

}
