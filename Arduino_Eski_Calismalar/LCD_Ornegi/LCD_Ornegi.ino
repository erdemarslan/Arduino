#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,20,4);

void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Merhaba");
  lcd.setCursor(0,1);
  lcd.print("Erdem");
  lcd.setCursor(0,2);
  lcd.print("Bugun");
  lcd.setCursor(0,3);
  lcd.print("Nasilsin?");
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
