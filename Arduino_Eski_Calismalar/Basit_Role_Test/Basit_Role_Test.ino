int rolePin = 8;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(rolePin, OUTPUT);
  Serial.println("Basit Role Test v.1.0.0");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Role Acik");
  digitalWrite(rolePin, HIGH);
  delay(3000);
  Serial.println("Role Kapali");
  digitalWrite(rolePin, LOW);
  delay(3000);
}
