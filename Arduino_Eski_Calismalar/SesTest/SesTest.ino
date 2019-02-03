int DO = 2; //D0 pini
int DA = A0; // A0 pini
int sensorvalue = 0;
 
void setup() {
  Serial.begin(9600);
  Serial.println("Basliyoruz....");
}
 
void loop() {
  sensorvalue = analogRead(DA);  //Analog değeri okuyoruz.
  Serial.print("Analog: ");
  Serial.print(sensorvalue);  //Analog değeri yazdırıyoruz.
  Serial.print("  ");
  Serial.print("Digital: ");
  Serial.println(digitalRead(DO));  //Dijital değeri yazdırıyoruz
}
