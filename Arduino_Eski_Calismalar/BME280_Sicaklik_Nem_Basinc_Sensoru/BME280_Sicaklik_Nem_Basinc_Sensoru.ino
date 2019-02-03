#include <Wire.h>
#include <BME280_I2C.h>


// Create BME280 object
//BME280_I2C bme; // I2C using address 0x77
BME280_I2C bme; // I2C using address 0x76

void setup() {

Serial.begin(9600);
Serial.println("Bosch BME280 Pressure - Humidity - Temp Sensor | cactus.io");

if (!bme.begin()) {
Serial.println("Could not find a valid BME280 sensor, check wiring!");
while (1);
}

bme.setTempCal(-1.5);// Temp was reading high so subtract 1 degree

Serial.println("Pressure\tHumdity\t\tTemp\t\tTemp");
}

void loop() {

bme.readSensor();

Serial.print(bme.getPressure_MB()); Serial.print(" mb\t"); // Pressure in millibars
Serial.print(bme.getHumidity()); Serial.print(" %\t\t");
Serial.print(bme.getTemperature_C()); Serial.print(" *C\t");
Serial.print(bme.getTemperature_F()); Serial.println(" *F");

// Add a 2 second delay.
delay(2000); //just here to slow down the output.
} 
