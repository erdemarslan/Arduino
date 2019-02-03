#include <LiquidCrystal_I2C.h>
#include <LedControl.h>
#include <Servo.h>
#include <EEPROM.h>

// Tanimlamalar
#define buttonPin2 4
#define rolePin 10
#define motorPin 12
#define buzzerPin 13
#define yesilLedPin A0
#define kirmiziLedPin A1
#define kapakPin A2
#define sekerPin A3
#define eepromAdres 8

byte kalanSeker = 10;
byte sonKalanSekerBilgisi = 10;
byte sonKapakDurumu = 0;
bool paraMakineDurum = false;

byte tl[8] = {
  0b01010,
  0b01100,
  0b11010,
  0b01100,
  0b11000,
  0b01001,
  0b01010,
  0b01100
};

  


volatile unsigned int sinyal = 0;
volatile unsigned long sonSinyalZamani = 0;
volatile double lira = 0.00;
volatile bool paraGeldimi = false;

// Ekran
LiquidCrystal_I2C lcd(0x3F, 16,2);

// Led bar Graph
LedControl lb = LedControl(9,8,7,1);

// Depoda kalan sıvı miktarı
//NewPing depo(16, 16, 200); // depoda kalan miktarı gösterir!

Servo motor;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Serial acildi!");

  pinMode(2, INPUT); // para makinesi
  pinMode(buttonPin2, INPUT);
  pinMode(rolePin, OUTPUT); // röle pini
  pinMode(buzzerPin, OUTPUT);
  pinMode(sekerPin, INPUT);
  pinMode(kapakPin, INPUT);
  pinMode(kirmiziLedPin, OUTPUT);
  pinMode(yesilLedPin, OUTPUT);
  Serial.println("G/C Tamamlandi!");

  //EEPROM.update(eepromAdres, kalanSeker);
  kalanSeker = EEPROM.read(eepromAdres);
  Serial.print("Hafizadan iceride son kalan seker sayisi okundu: ");
  Serial.println(kalanSeker);

  
  motor.attach(motorPin);
  motor.write(89);
  Serial.println("Seker motoru ayarlandi ve durma konumunda ayarlandi.");
  

  // Para Makinesini Kapat!
  paraMakinesiniKapat();
  
  lcd.init();
  lcd.createChar(0, tl);
  lcd.backlight();
  lcd.clear();
  lcd.home();
  lcd.print("SISTEM BASLIYOR");
  lcd.setCursor(0,1);
  lcd.print("LUTFEN BEKLEYIN");
  delay(2000);

  Serial.println("Ekran baslatildi.");
  
  lb.shutdown(0,false);
  lb.setIntensity(0, 15);

  depoGoster();

  Serial.println("Seker sayisi led barda gosterildi");
  

  // Para Makinesini Aç!
  paraMakinesiniAc();
  delay(500);
  attachInterrupt(digitalPinToInterrupt(2), paraAttilar, RISING);
  Serial.println("Para icin interrupt acildi");
  
  lcd.clear();
  lcd.home();
  lcd.print("LUTFEN PARA ATIN");
  lcd.setCursor(0,1);
  lcd.print("Bakiye 0.00 ");
  lcd.write((uint8_t)0);
  
  Serial.println("Setup kismi bitti");
}

void paraAttilar() {
  sinyal++;
  sonSinyalZamani = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long sonSinyaldenGecenZaman = millis() - sonSinyalZamani;
  if(sinyal > 0 && sonSinyaldenGecenZaman > 150) {
    if(sinyal < 6) {
      paraGeldimi = true;
      lira = lira + 0.5; 
    }

    if(sinyal > 5) {
      paraGeldimi = true;
      lira = lira + 1.0;
    }
    sinyal = 0;
  }
  
  if(paraGeldimi) {
    lcd.setCursor(0,1);
    lcd.print("                ");
    lcd.setCursor(0,1);
    String veri = "Bakiye " + String(lira) + " ";
    lcd.print(veri);
    lcd.write((uint8_t)0);
    paraGeldimi = false;
  }

  //Serial.println("Kapak acik mi kontrol ediliyor.");
  while(digitalRead(kapakPin) == HIGH) {
    // kapak açık olduğu sürece bekle!
    if(paraMakineDurum) {
      lcd.home();
      lcd.print("                ");
      lcd.home();
      lcd.print("KAPAK ACIK");
      paraMakinesiniKapat();
    }
    delay(250);
  }

  if(digitalRead(kapakPin) == LOW && paraMakineDurum == false) {
    kalanSeker = 10;
    EEPROM.update(eepromAdres, kalanSeker);
    depoGoster();
    paraMakinesiniAc();
    lcd.home();
    lcd.print("                ");
    lcd.home();
    lcd.print("LUTFEN PARA ATIN");
  }

  if(kalanSeker != 0 && sonKalanSekerBilgisi == 0) {
    lcd.home();
    lcd.print("                ");
    lcd.home();
    lcd.print("LUTFEN PARA ATIN");

    sonKalanSekerBilgisi = 10;
    paraMakinesiniAc();
  }

  if(kalanSeker == 0 && sonKalanSekerBilgisi != 0) {
    lcd.home();
    lcd.print("                ");
    lcd.home();
    lcd.print("CIKOLATA KOYUN");

    sonKalanSekerBilgisi = 0;
    paraMakinesiniKapat();

    while(digitalRead(kapakPin) == LOW) {
      delay(100);
    }
    sinyal = 0;
    return;
  }
  
  if(lira > 0 && digitalRead(buttonPin2)) {
    // Limonata ver!
    // para makinesini kapat!
    paraMakinesiniKapat();

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("CIKOLATA VERILI.");
    lcd.setCursor(0,1);
    lcd.print("LUTFEN  BEKLEYIN");

    // parayı eksilt!
    lira = lira - 0.50;

    // Şekeri ver!
    sekerVer();

    sinyal = 0;
    
    paraMakinesiniAc();
    delay(250);

    lcd.clear();
    lcd.home();
    lcd.print("LUTFEN PARA ATIN");
    lcd.setCursor(0,1);
    String veri = "Bakiye " + String(lira) + " ";
    lcd.print(veri);
    lcd.write((uint8_t)0);
  }

  
  delay(50);
}


