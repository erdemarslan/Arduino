const int led = 5;
#define buton 2



void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(buton, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(buton) == HIGH) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
  delay(20);
}
