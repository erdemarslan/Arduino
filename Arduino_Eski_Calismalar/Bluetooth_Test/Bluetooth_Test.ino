#include <SoftwareSerial.h>
SoftwareSerial bt(2,3);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Serial ekrani basladi");

  bt.begin(9600);
  Serial.println("Bluetooth basladi");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()) {
    bt.write( Serial.read() );
  }

  if(bt.available()) {
    Serial.write(bt.read());
  }
}
