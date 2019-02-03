//#include <SoftwareSerial.h>

//Serial1 sim;

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600); // RX 7 - TX 8
  Serial.begin(9600);
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
    Serial1.write(Serial.read());
  }

  if(Serial1.available()) {
    Serial.println("#####");
    Serial.write(Serial1.read());
  }
  
}
