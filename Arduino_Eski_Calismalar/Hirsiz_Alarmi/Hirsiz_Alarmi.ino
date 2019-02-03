#include <LiquidCrystal.h>
#include <GSMSim.h>


int SIM_RX = 7;
int SIM_TX = 8;
int SIM_RST = 2;
int PIR_PIN = 9;

int durum = LOW;
bool mesaj_gonderilsinmi = false;

unsigned long son_mesaj;
//long mesaj_bekleme = 300000;
unsigned long mesaj_bekleme = 30000;


char* numara = "+905321130193";
char* mesaj = "Dukkana siciyolar...";


GSMSim gsm(SIM_RX, SIM_TX, SIM_RST);
LiquidCrystal lcd(12,11,6,5,4,3);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.print("ERA HA-GS v.1.0");
  
  gsm.start();
  gsm.smsTextMode(true);
  lcd.setCursor(0,1);
  lcd.print("GSM BASLADI !");
  Serial.println("GSM BASLADI !");

  delay(3000);
  lcd.clear();

  pinMode(PIR_PIN, INPUT);

  lcd.setCursor(0,0);
  lcd.print("SENSOR BASLIYOR");
  /*
  for(int i = 0; i < 30; i++) {
    if(i % 2 == 0) {
      lcd.setCursor(i/2, 1);
      lcd.print(".");
    }
    delay(1000);
  }
  */
  Serial.println("PIR BASLADI !");
  

  lcd.clear();

  
  /*
  lcd.setCursor(0,0);
  lcd.print("SMS Gonderiliyor");
  Serial.println("SMS Gonderiliyor");
  lcd.setCursor(0,1);
  if(gsm.smsSend(numara, mesaj)) {
    lcd.print("SMS Gitti");
    Serial.println("SMS Gitti");
  } else {
    lcd.print("SMS Gitmedi");
    Serial.println("SMS Gitmedi");
  }
  */
}

void loop() {
  // put your main code here, to run repeatedly:
  
  /*if(Serial.available()) {
    gsm.write(Serial.read());
  }

  if(gsm.available()) {
    Serial.write(gsm.read());
  }
  */

  durum = digitalRead(PIR_PIN);
  
  lcd.setCursor(0,0);

  if(durum == HIGH && mesaj_gonderilsinmi == false) {
    mesaj_gonderilsinmi = true;
    son_mesaj = millis();
    Serial.print("Son mesaj: ");
    Serial.println(son_mesaj);

    // gsm.smsSend(numara,mesaj);
    Serial.println("Mesaj Gitti");
  }
  
  unsigned long topla = son_mesaj + mesaj_bekleme;
  long sonuc = topla - millis();

  Serial.print("Topla : ");
  Serial.println(topla);

  Serial.print("Sonuc : ");
  Serial.println(sonuc);

  
  if(sonuc < 0) {
    mesaj_gonderilsinmi = false;
    Serial.println("Sifirlama tamam!");
  }

  delay(500);
  
}
