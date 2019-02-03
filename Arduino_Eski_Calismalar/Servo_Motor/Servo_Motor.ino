#include <Servo.h>

Servo motor;  // motor u tanımladım

void setup() {
  // put your setup code here, to run once:
  motor.attach(4); // motoru dijital pine bağladım
  motor.write(0); // motoru 0 dereceye çektim
} // setup sonu

void loop() {
  // put your main code here, to run repeatedly:
  // For döngüsü ile 0 dan 180 e kadar motoru döndürdük
  for(int i = 0; i <= 180; i++) {
    motor.write(i);
    delay(2);
  } // for sonu

  for(int k = 180; k >= 0; k--) {
    motor.write(k);
    delay(2);
  } // for sonu
}
