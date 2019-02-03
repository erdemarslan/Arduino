#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <Servo.h>
#include <LiquidCrystal_I2C.h>


#define buttonMavi 3
#define buttonKirmizi 5
#define buzzerPin 6

#define SERVO_UST 8
#define SERVO_ALT 9
#define LCD_ADRES 0x3F
#define SERVO_ILK_ACI 85
#define SERVO_OKUMA_ACI 45
#define SERVO_BIRAKMA_ACI 10
#define SERVO_CANAK1 140
#define SERVO_CANAK2 100
#define SERVO_CANAK3 60

unsigned int yesil, mavi, sari, yesil_eski, mavi_eski, sari_eski = 0;
volatile boolean calisiyormu = false;

LiquidCrystal_I2C lcd(LCD_ADRES, 16, 2);
Servo servoAlt, servoUst;
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Color View Test!");

  pinMode(buttonMavi, INPUT);
  pinMode(buttonKirmizi, INPUT);
  pinMode(buzzerPin, OUTPUT);

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }
  
  servoAlt.attach(SERVO_ALT);
  servoUst.attach(SERVO_UST);
  delay(200);
  servoAlt.write(SERVO_CANAK2);
  servoUst.write(SERVO_OKUMA_ACI);

  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.home();
  lcd.print("Y:0     M:0");
  lcd.setCursor(0,1);
  lcd.print("S:0     BEKLIYOR");

  attachInterrupt(digitalPinToInterrupt(buttonMavi), butonumaBastilar, RISING);
}

void butonumaBastilar() {
  if(!calisiyormu) {
    calisiyormu = true;
  }
}

void servoUstGit(int aci) {
  servoUst.write(aci);
  delay(500);
}

void servoAltGit(int aci) {
  servoAlt.write(aci);
  delay(300);
}

int renkOku() {

  uint16_t r, g, b, c, colorTemp, lux;
  
  tcs.getRawData(&r, &g, &b, &c);
  colorTemp = tcs.calculateColorTemperature(r, g, b);
  lux = tcs.calculateLux(r, g, b);

  int sayi = -1;

  Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  Serial.println(" ");


  if(colorTemp < 7100 && colorTemp > 6700 && lux < 650 && lux > 490) {
    Serial.println("Renk alani bos. Basa donduk!");
    sayi = 0;
  }


  if(colorTemp < 6600 && colorTemp > 6100 && lux < 850 && lux > 680) {
    Serial.println("Yesil renk!");
    sayi = SERVO_CANAK1;
    tone(buzzerPin, 440, 200);
    delay(200);
    noTone(buzzerPin);
    yesil = yesil + 1;
  }

  if(colorTemp < 13000 && colorTemp > 9500 && lux < 580 && lux > 480) {
    Serial.println("Mavi!");
    sayi = SERVO_CANAK2;
    tone(buzzerPin, 880, 200);
    delay(200);
    noTone(buzzerPin);
    mavi = mavi + 1;
  }
      
  if(colorTemp < 4600 && colorTemp > 3500 && lux < 1300 && lux > 850) {
    Serial.println("Sarı!");
    sayi = SERVO_CANAK3;
    tone(buzzerPin, 220, 200);
    delay(200);
    noTone(buzzerPin);
    sari = sari + 1;
  }

  if(yesil != yesil_eski) {
    yesil_eski = yesil;
    lcd.setCursor(3,0);
    lcd.print("     ");
    lcd.setCursor(3,0);
    lcd.print(yesil);
  }

  if(mavi != mavi_eski) {
    mavi_eski = mavi;
    lcd.setCursor(11,0);
    lcd.print("     ");
    lcd.setCursor(11,0);
    lcd.print(mavi);
  }

  if(sari != sari_eski) {
    sari_eski = sari;
    lcd.setCursor(3,1);
    lcd.print("     ");
    lcd.setCursor(3,1);
    lcd.print(sari);
  }

  return sayi;
}

void ekranSifirla() {
  yesil = 0;
  mavi = 0;
  sari = 0;
  yesil_eski = 0;
  mavi_eski = 0;
  sari_eski = 0;

  lcd.clear();
  lcd.home();
  lcd.print("Y:0     M:0");
  lcd.setCursor(0,1);
  lcd.print("S:0     BEKLIYOR");
}

void loop() {

  if(calisiyormu) {
    
    ekranSifirla();
    delay(200);
    lcd.setCursor(8,1);
    lcd.print("        ");
    lcd.setCursor(8,1);
    lcd.print("OKUYOR");

    bool devam = true;

    while(devam == true) {
      servoUstGit(SERVO_ILK_ACI);
      servoUstGit(SERVO_OKUMA_ACI);
      int renk = renkOku();

      if(renk == 0) {
        servoUstGit(SERVO_OKUMA_ACI);
        devam = false;
        lcd.setCursor(8,1);
        lcd.print("        ");
        lcd.setCursor(8,1);
        lcd.print("BITTI");
        break;
        // LCDye bitti Yaz
      }

      if(renk == -1) {
        servoUstGit(SERVO_OKUMA_ACI);
        devam = false;

        lcd.setCursor(8,1);
        lcd.print("        ");
        lcd.setCursor(8,1);
        lcd.print("HATA");
        break;
      }    
     
      delay(200);
  
      servoAltGit(renk);
      servoUstGit(SERVO_BIRAKMA_ACI);
    }

    calisiyormu = false;
  }

  if(!calisiyormu && digitalRead(buttonKirmizi) == HIGH) {
    ekranSifirla();
  }

  delay(50);
}
