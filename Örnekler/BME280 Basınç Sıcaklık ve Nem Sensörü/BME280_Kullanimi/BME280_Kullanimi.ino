#include <Wire.h>
#include <BME280_I2C.h>


// Create BME280 object
BME280_I2C bme; // I2C 0x76 adresini kullanıyor. Çin çakması :)

void setup() {

Serial.begin(9600);
Serial.println("Bosch BME280 Basinc - Nem - Sicaklik Sensoru");

if (!bme.begin()) {
  Serial.println("Bagli BME280 sensoru bulamadik, lutfen kablolari kontrol edin!");
  while (1);
}

  // Bu metod ayarlama yapar. Ölçülen sıcaklık ile gerçek ortam sıcaklığı arasında fark varsa bu fark burası ile ayarlanır.
  bme.setTempCal(-1.5);

  Serial.println("Basinc\t\tNem\t\tSicaklik\tSicaklik");
}

void loop() {

  bme.readSensor();

  Serial.print(bme.getPressure_MB()); Serial.print(" mb\t"); // milibar cinsinden basınç
  Serial.print(bme.getHumidity()); Serial.print(" %\t\t");
  Serial.print(bme.getTemperature_C()); Serial.print(" *C\t");
  Serial.print(bme.getTemperature_F()); Serial.println(" *F");

  // 2 sn bekle
  delay(2000); //çıkış değerlerini biraz düşür
}
