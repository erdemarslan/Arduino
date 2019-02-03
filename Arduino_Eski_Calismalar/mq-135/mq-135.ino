/*
Library Repository : https://github.com/ckalpha/MQ135
Author : Damrongwit Nusuk
Email : jack@racksync.com
Website : http://www.racksync.com
*/

#include "MQ135.h"
#define ANALOGPIN A0    //  Define Analog PIN on Arduino Board
#define RZERO 822.60    //  Define RZERO Calibration Value
MQ135 gasSensor = MQ135(ANALOGPIN);

void setup()
{
  Serial.begin(9600);
  Serial.println("Cihaz Isiniyor...");
  delay(10000);
  Serial.println("Olcum Yapiliyor.");
  float rzero = gasSensor.getRZero();
  delay(3000);
  Serial.print("MQ135 RZERO Kalibrasyon Degeri: ");
  Serial.println(rzero);
}

void loop() {
  
}
