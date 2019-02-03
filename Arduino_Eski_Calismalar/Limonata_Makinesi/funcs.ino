void paraMakinesiniAc() {
  digitalWrite(kirmiziLedPin, LOW);
  digitalWrite(rolePin, LOW);
  digitalWrite(yesilLedPin, HIGH);
  Serial.println("Para makinesi acildi");
  paraMakineDurum = true;
  delay(250);
  sinyal = 0;
}

void paraMakinesiniKapat() {
  digitalWrite(yesilLedPin, LOW);
  digitalWrite(rolePin, HIGH);
  digitalWrite(kirmiziLedPin, HIGH);
  Serial.println("Para makinesi kapatildi");
  paraMakineDurum = false;
  delay(250);
  sinyal = 0;
}

void sekerVer() {
  motor.write(0); // döndür
  while(digitalRead(sekerPin) == HIGH) {
    // şekerin geçmesini bekle
    delay(100);
  }
  motor.write(89); // motoru durdur

  kalanSeker = kalanSeker - 1;
  if(kalanSeker < 0) {
    kalanSeker = 0;
  }
  EEPROM.update(eepromAdres, kalanSeker);
  delay(100);
  Serial.print("Verildikten sonra kalan seker sayisi: ");
  Serial.println(kalanSeker);
  depoGoster();
}

void depoGoster() {
  kalanSeker = EEPROM.read(eepromAdres);
  if(kalanSeker < 0 || kalanSeker > 10) {
    kalanSeker = 0;
  }
  
  Serial.print("kalanSeker: ");
  Serial.println(kalanSeker);
  
  LedBarGoster(kalanSeker);
}

// =============================================================================
// --- Ledlerin gösteren fonksiyon!
// =============================================================================
void LedBarGoster(int mark) {
  if (mark < 0 || mark > 10) return; // Sanity check, cannot be more than max or less than 0 LEDs
  //lb.clearDisplay(0);
  switch(mark) {
    default:
    case 0:
      lb.clearDisplay(0);
    break;

    case 1:
      lb.setLed(0,1,1,true);
      lb.setLed(0,1,0,false);
      lb.setLed(0,0,7,false);
      lb.setLed(0,0,6,false);
      lb.setLed(0,0,5,false);
      lb.setLed(0,0,4,false);
      lb.setLed(0,0,3,false);
      lb.setLed(0,0,2,false);
      lb.setLed(0,0,1,false);
      lb.setLed(0,0,0,false);
    break;

    case 2:
      lb.setLed(0,1,1,true);
      lb.setLed(0,1,0,true);
      lb.setLed(0,0,7,false);
      lb.setLed(0,0,6,false);
      lb.setLed(0,0,5,false);
      lb.setLed(0,0,4,false);
      lb.setLed(0,0,3,false);
      lb.setLed(0,0,2,false);
      lb.setLed(0,0,1,false);
      lb.setLed(0,0,0,false);
    break;

    case 3:
      lb.setLed(0,1,1,true);
      lb.setLed(0,1,0,true);
      lb.setLed(0,0,7,true);
      lb.setLed(0,0,6,false);
      lb.setLed(0,0,5,false);
      lb.setLed(0,0,4,false);
      lb.setLed(0,0,3,false);
      lb.setLed(0,0,2,false);
      lb.setLed(0,0,1,false);
      lb.setLed(0,0,0,false);
    break;

    case 4:
      lb.setLed(0,1,1,true);
      lb.setLed(0,1,0,true);
      lb.setLed(0,0,7,true);
      lb.setLed(0,0,6,true);
      lb.setLed(0,0,5,false);
      lb.setLed(0,0,4,false);
      lb.setLed(0,0,3,false);
      lb.setLed(0,0,2,false);
      lb.setLed(0,0,1,false);
      lb.setLed(0,0,0,false);
    break;

    case 5:
      lb.setLed(0,1,1,true);
      lb.setLed(0,1,0,true);
      lb.setLed(0,0,7,true);
      lb.setLed(0,0,6,true);
      lb.setLed(0,0,5,true);
      lb.setLed(0,0,4,false);
      lb.setLed(0,0,3,false);
      lb.setLed(0,0,2,false);
      lb.setLed(0,0,1,false);
      lb.setLed(0,0,0,false);
    break;

    case 6:
      lb.setLed(0,1,1,true);
      lb.setLed(0,1,0,true);
      lb.setLed(0,0,7,true);
      lb.setLed(0,0,6,true);
      lb.setLed(0,0,5,true);
      lb.setLed(0,0,4,true);
      lb.setLed(0,0,3,false);
      lb.setLed(0,0,2,false);
      lb.setLed(0,0,1,false);
      lb.setLed(0,0,0,false);
    break;

    case 7:
      lb.setLed(0,1,1,true);
      lb.setLed(0,1,0,true);
      lb.setLed(0,0,7,true);
      lb.setLed(0,0,6,true);
      lb.setLed(0,0,5,true);
      lb.setLed(0,0,4,true);
      lb.setLed(0,0,3,true);
      lb.setLed(0,0,2,false);
      lb.setLed(0,0,1,false);
      lb.setLed(0,0,0,false);
    break;

    case 8:
      lb.setLed(0,1,1,true);
      lb.setLed(0,1,0,true);
      lb.setLed(0,0,7,true);
      lb.setLed(0,0,6,true);
      lb.setLed(0,0,5,true);
      lb.setLed(0,0,4,true);
      lb.setLed(0,0,3,true);
      lb.setLed(0,0,2,true);
      lb.setLed(0,0,1,false);
      lb.setLed(0,0,0,false);
    break;

    case 9:
      lb.setLed(0,1,1,true);
      lb.setLed(0,1,0,true);
      lb.setLed(0,0,7,true);
      lb.setLed(0,0,6,true);
      lb.setLed(0,0,5,true);
      lb.setLed(0,0,4,true);
      lb.setLed(0,0,3,true);
      lb.setLed(0,0,2,true);
      lb.setLed(0,0,1,true);
      lb.setLed(0,0,0,false);
    break;

    case 10:
      lb.setLed(0,1,1,true);
      lb.setLed(0,1,0,true);
      lb.setLed(0,0,7,true);
      lb.setLed(0,0,6,true);
      lb.setLed(0,0,5,true);
      lb.setLed(0,0,4,true);
      lb.setLed(0,0,3,true);
      lb.setLed(0,0,2,true);
      lb.setLed(0,0,1,true);
      lb.setLed(0,0,0,true);
    break;
  }
}
