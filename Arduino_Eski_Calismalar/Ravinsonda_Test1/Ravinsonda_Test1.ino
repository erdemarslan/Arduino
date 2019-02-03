
#include <BME280I2C.h>
#include <Wire.h>
//#include <Adafruit_Sensor.h>
#include <DHT.h>
//#include <DHT_U.h>

#define DHTPIN 8
#define DHTTYPE DHT22


DHT dht(DHTPIN, DHTTYPE);
BME280I2C bme;

BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
BME280::PresUnit presUnit(BME280::PresUnit_hPa);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  dht.begin();
  Serial.println("DHT Starts...");

  Wire.begin();
  while(!bme.begin()) {
    Serial.println("Could not find BME280 sensor!");
    delay(1000);
  }

  Serial.println("BME280 Starts...");

  switch(bme.chipModel())
  {
     case BME280::ChipModel_BME280:
       Serial.println("Found BME280 sensor! Success.");
       break;
     case BME280::ChipModel_BMP280:
       Serial.println("Found BMP280 sensor! No Humidity available.");
       break;
     default:
       Serial.println("Found UNKNOWN sensor! Error!");
  }
}

void loop() {
  
  float sicaklik_dht(NAN), nem_dht(NAN), sicaklik_endeksi_dht(NAN), sicaklik_bme(NAN), nem_bme(NAN), basinc_bme(NAN);
  // DHT Okumaları -----
  sicaklik_dht = dht.readTemperature();
  nem_dht = dht.readHumidity();
  sicaklik_endeksi_dht = dht.computeHeatIndex(sicaklik_dht, nem_dht, false);
  // BME Okumaları -----
  bme.read(basinc_bme, sicaklik_bme, nem_bme, tempUnit, presUnit);
  
  // Yaz Ekrana!
  Serial.print("Sicaklik(DHT): ");
  Serial.print(sicaklik_dht);
  Serial.print(" C\t\t Sicaklik(BME): ");
  Serial.print(sicaklik_bme);
  Serial.print(" C\t\t Nem(DHT): ");
  Serial.print(nem_dht);
  Serial.print(" %\t\t Nem(BME): ");
  Serial.print(nem_bme);
  Serial.print(" %\t\t Basinc: ");
  Serial.print(basinc_bme);
  Serial.print(" hPa\t\tSicaklik Endeksi(DHT): ");
  Serial.println(sicaklik_endeksi_dht);

  delay(2000);
}
