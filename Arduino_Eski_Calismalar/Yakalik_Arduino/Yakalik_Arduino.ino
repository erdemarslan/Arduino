#include <LiquidCrystal_I2C.h>

int sesD = 2;
int sesA = A0;
int sinir = 516;

bool isikAcik = false;
unsigned long sonIslem;

LiquidCrystal_I2C lcd(0x3F, 20,4);


void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
  lcd.print("Sistem aciliyor...");
}

void loop() {
  // put your main code here, to run repeatedly:

}
