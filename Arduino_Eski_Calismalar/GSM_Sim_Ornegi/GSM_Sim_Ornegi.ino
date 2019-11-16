#include <SoftwareSerial.h>

//Serial1 sim;
SoftwareSerial gsm(10,11);

void setup() {
  // put your setup code here, to run once:
  gsm.begin(57600); // RX 7 - TX 8
  Serial.begin(57600);
  //Serial.println("Sim baslatildi!");
  
  //Serial.println(sim.smsTextMode(true));
  //delay(500);

  //Serial.println(sim.smsListUnread());

  //delay(2000);
  
  //Serial.println(sim.smsRead(6, false));

  //Serial.println(sim.smsReadMessageCenter());

  
  /*
  char* no = "+905598008000";
  Serial.println(sim.smsChangeMessageCenter(no));

  Serial.println(sim.smsReadMessageCenter());
  
  
  String imei = sim.moduleIMEI();
  Serial.print("Cihaz IMEI :");
  Serial.println(imei);

  delay(500);

  
  
  
  char* no = "+905321130193";
  char* mesaj = "Sicaklik 38 derece oldu.";

  Serial.println(sim.smsSend(no, mesaj));
  */
  Serial.println("Basladik!");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()) {
    gsm.write(Serial.read());
  }

  if(gsm.available()) {
    Serial.println("#####");
    Serial.write(gsm.read());
  }
  
}
