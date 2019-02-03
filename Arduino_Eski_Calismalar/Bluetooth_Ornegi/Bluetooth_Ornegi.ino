#include <SoftwareSerial.h> //IDE >= 1.0

const int rxPin = 2;
const int txPin = 3;
const int atPin = 4;
SoftwareSerial bluetooth(rxPin, txPin); //IDE >= 1.0

void setup() {
Serial.begin(9600);
bluetooth.begin(9600);
pinMode(atPin, OUTPUT);
Serial.println("Seriali attive...");
digitalWrite(atPin, HIGH);
}

void loop() {
if (bluetooth.available()) {
Serial.write(bluetooth.read());
}
if (Serial.available()) {
bluetooth.write(Serial.read());
}
}
