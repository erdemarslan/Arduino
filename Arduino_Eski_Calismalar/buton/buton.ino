
const int led = 4;
const int buton = 5;
//boolean acikmi = false;
int butondegeri = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(buton, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if( digitalRead(buton) == HIGH ) {
    butondegeri++;
  }

  if(butondegeri % 2 == 0) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
}
