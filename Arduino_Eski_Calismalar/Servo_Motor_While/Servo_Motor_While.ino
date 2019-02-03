#include <Servo.h>

Servo motor;

void setup() {
  // Motoru başlat
  motor.attach(4);
  // motoru sıfırla
  motor.write(0);

  // motorun derecesini tutar
  int derece = 0;
  // yönü belirle | 0 - ileri | 1 - geri
  int yon = 0;
  // while döngüsünün devam etmesi için şart
  boolean tamammi = true;

  while(tamammi) {
    // Eğer yön ileri ise
    if(yon == 0) {
      // ileri gidiyor
      // motora dereceyi yaz
      motor.write(derece);
      // 5 milisaniye bekle
      delay(5);
      // dereceyi 1 arttır
      derece++;

      // Eğer derece 180 olmuş ise, yönü geriye çevir
      if(derece == 180) {
        yon = 1;
      }
    }
    else {
      // geri dönüyor
      // motora dereceyi yaz
      motor.write(derece);
      // 5 milisaniye bekle
      delay(5);
      // dereceyi 1 azalt
      derece--;

      // Eğer derece 0 olursa yönü ileriye çevir
      if(derece == 0) {
        yon = 0;
      }
    }
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
