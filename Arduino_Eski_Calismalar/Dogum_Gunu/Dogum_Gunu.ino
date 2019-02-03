const byte ldrPin = 2;
volatile bool kapakAcikmi = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(ldrPin), budaSanaKapakOlsun, CHANGE);
}

void budaSanaKapakOlsun() {
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int deger = digitalRead(ldrPin);
  Serial.println(deger);
  delay(500);
}
