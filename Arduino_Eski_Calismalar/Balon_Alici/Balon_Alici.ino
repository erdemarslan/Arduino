#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <SoftwareSerial.h>

#define DENIZSEVIYESIBASINCI (1002.70)
#define SETPIN 3
#define WIFI_RX 4
#define WIFI_TX 5

#define LCD_RX 10
#define LCD_TX 11

Adafruit_BME280 Sensor;


SoftwareSerial lcd(LCD_RX, LCD_TX);
SoftwareSerial wifi(WIFI_RX, WIFI_TX);

float sicaklik, nem, basinc, yukseklik;
char veri[40];
bool veri_basladi, veri_bitti, veri_islendi;


void setup() {
  // put your setup code here, to run once:
  pinMode(SETPIN, OUTPUT);

  veri_islendi = true;
  veri_basladi = false;
  veri_bitti = false;

  Serial.begin(9600);
  wifi.begin(57600);
  lcd.begin(9600);
  

  
  bool durum;

  durum = Sensor.begin();
  if(!durum) {
    Serial.println("BME280 Baslayamadi!");
    while(1);
  }
  digitalWrite(SETPIN, HIGH);
  Serial.println("Loop a akiyoruz....");

}

void loop() {
  // put your main code here, to run repeatedly:
  wifi.listen();
  static byte sira = 0;

  if(wifi.available()) {
    char harf = wifi.read();

    if(harf == '#') {
      veri_islendi = false;
      veri_basladi = true;
      veri_bitti = false;
      sira = 0;
    }

    if(veri_basladi == true && veri_bitti == false) {
      veri[sira] = harf;
      sira++;
      if(harf == '*') {
        veri_bitti = true;
      }
    }
  }


  


  if(veri_islendi == false && veri_basladi == true && veri_bitti == true) {
    //Serial.println(String(veri));
    String _data, gSicaklik, gNem, gBasinc, gYukseklik;
    _data = String(veri);
    
    gSicaklik = _data.substring(_data.indexOf(F("S:"))+2, _data.indexOf(F("|N:")));
    gNem = _data.substring(_data.indexOf(F("N:"))+2, _data.indexOf(F("|B:")));
    gBasinc = _data.substring(_data.indexOf(F("B:"))+2, _data.indexOf(F("|Y:")));
    gYukseklik = _data.substring(_data.indexOf(F("Y:"))+2, _data.indexOf(F("*")));

    sicaklik = Sensor.readTemperature();
    nem = Sensor.readHumidity();
    basinc = Sensor.readPressure() / 100.0F; // hPa
    //yukseklik = Sensor.readAltitude(DENIZSEVIYESIBASINCI);

    Serial.println(basinc);
    
    lcd.listen();
    
    lcd.print("txtSY.txt=\"");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    lcd.print(String(sicaklik));// This is the value you want to send to that object and atribute mention before.
    lcd.print("\"");
    lcd.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
    lcd.write(0xff);
    lcd.write(0xff);

    
    lcd.print("txtSB.txt=\"");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    lcd.print(String(gSicaklik));// This is the value you want to send to that object and atribute mention before.
    lcd.print("\"");
    lcd.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
    lcd.write(0xff);
    lcd.write(0xff);

    lcd.print("txtNY.txt=\"");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    lcd.print(String(nem));// This is the value you want to send to that object and atribute mention before.
    lcd.print("\"");
    lcd.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
    lcd.write(0xff);
    lcd.write(0xff);

    lcd.print("txtNB.txt=\"");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    lcd.print(String(gNem));// This is the value you want to send to that object and atribute mention before.
    lcd.print("\"");
    lcd.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
    lcd.write(0xff);
    lcd.write(0xff);

    lcd.print("txtY.txt=\"");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    lcd.print(String(gYukseklik));// This is the value you want to send to that object and atribute mention before.
    lcd.print("\"");
    lcd.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
    lcd.write(0xff);
    lcd.write(0xff);

    Serial.println("Ekrana yazildi!");

    

    veri_islendi = true;
    veri_basladi = false;
    veri_bitti = false;
    sira = 0;
  }
}
