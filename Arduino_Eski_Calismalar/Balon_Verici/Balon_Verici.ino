#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <SoftwareSerial.h>

#define DENIZSEVIYESIBASINCI (1004.70)
#define SETPIN 4
#define WIFI_RX 5
#define WIFI_TX 6

Adafruit_BME280 Sensor;

SoftwareSerial wifi(WIFI_RX, WIFI_TX);

float sicaklik, nem, basinc, yukseklik;


void setup() {
  pinMode(SETPIN, OUTPUT);
  Serial.begin(9600);
  wifi.begin(57600); 

  /*if(!) {
    Serial.println("wifi baslayamadi!");
    while(1);
  }
  */

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
  if(Serial.available()) {
    wifi.write(Serial.read());
  }

  if(wifi.available()) {
    Serial.write(wifi.read());
  }

  //Değerleri okuyalım sensörden
  sicaklik = Sensor.readTemperature();
  nem = Sensor.readHumidity();
  basinc = Sensor.readPressure() / 100.0F; // hPa
  yukseklik = Sensor.readAltitude(DENIZSEVIYESIBASINCI);

  String veri = "#S:" + String(sicaklik) + "|N:" + String(nem) + "|B:" + String(basinc) + "|Y:" + String(yukseklik) + "*";
  Serial.println(veri);
  wifi.print(veri);
  Serial.println("Veri gonderildi");
  delay(500);
}

