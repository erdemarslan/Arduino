#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16,2);

const byte paraPin = 2;
const byte butonPin = 3;
const byte motorPin = 7;

const double pulseKacLira = 0.25;

volatile double lira = 0.00;
volatile bool paraGeldimi = false;
volatile bool motorCalissinmi = false;

void setup() {
  pinMode(paraPin, INPUT);
  pinMode(butonPin, INPUT);
  pinMode(motorPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(paraPin), paraAttilar, RISING);
  attachInterrupt(digitalPinToInterrupt(butonPin), butonaBastilar, RISING);
  
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.home();
  lcd.print("Bakiye: 0 TL");
  lcd.setCursor(0,1);
  lcd.print("Motor: Durdu");
}

void butonaBastilar() {
  if(!motorCalissinmi) {
    motorCalissinmi = true;
  }
}

void paraAttilar() {
  if(!paraGeldimi) {
    paraGeldimi = true;
    lira = lira + pulseKacLira;
  }
}


void loop() {
  if(paraGeldimi) {
    lcd.setCursor(8,0);
    lcd.print("       ");
    lcd.setCursor(8,0);
    String veri = String(lira) + " TL";
    lcd.print(veri);
    paraGeldimi = false;
  }

  if(motorCalissinmi) {
    lcd.setCursor(7,1);
    lcd.print("         ");
    lcd.setCursor(7,1);

    lcd.print("Calisiyor");
    delay(100);
    digitalWrite(motorPin, HIGH);
    delay(3000);
    digitalWrite(motorPin, LOW);
    delay(100);
    
    lcd.setCursor(7,1);
    lcd.print("         ");
    lcd.setCursor(7,1);
    lcd.print("Durdu");
    motorCalissinmi = false;
  }

}
