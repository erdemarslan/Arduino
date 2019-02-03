#include <Servo.h>

// SOL MOTOR
int solA = 11;
int solB = 12;

// SAĞ MOTOR
int sagA = 10;
int sagB = 9;

// SERVO MOTOR
int servoPin = 8;

// Mesafe Sensörü
int echoPin = 7;
int trigPin = 6;

Servo motor;

void setup() {
  Serial.begin(9600);
  // Motor Pinlerini Tanımlıyoruz
  pinMode(solA, OUTPUT);
  pinMode(solB, OUTPUT);
  pinMode(sagA, OUTPUT);
  pinMode(sagB, OUTPUT);

  Serial.println("Motorlar tanimlandi");

  // Servo motoru bağlıyoruz ve 0 konumuna getiriyoruz.
  motor.attach(servoPin);
  motor.write(0);
  delay(250);
  Serial.println("Servo motor tanımlandi ve 0 landi");

  // Mesafe sensörümü tanımlıyorum
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.println("Mesafe sensoru tanimlandi");
}


void ileri() {
  digitalWrite(solA, HIGH);
  digitalWrite(solB, LOW);
  digitalWrite(sagA, HIGH);
  digitalWrite(sagB, LOW);
}

void geri() {
  digitalWrite(solA, LOW);
  digitalWrite(solB, HIGH);
  digitalWrite(sagA, LOW);
  digitalWrite(sagB, HIGH);
}

void sol() {
  digitalWrite(solA, LOW);
  digitalWrite(solB, HIGH);
  digitalWrite(sagA, HIGH);
  digitalWrite(sagB, LOW);
}

void sag() {
  digitalWrite(sagA, LOW);
  digitalWrite(sagB, HIGH);
  digitalWrite(solA, HIGH);
  digitalWrite(solB, LOW);
}

void dur() {
  digitalWrite(sagA, LOW);
  digitalWrite(sagB, LOW);
  digitalWrite(solA, LOW);
  digitalWrite(solB, LOW);
}

int mesafe() {
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  int sure = pulseIn(echoPin, HIGH);
  int uzaklik = sure / 2 / 29.1;

  return uzaklik;
}

void loop() {
  int uzaklik = mesafe();

  Serial.print("On olculen mesafe = ");
  Serial.println(uzaklik);

  delay(100);

  ileri();

  /*
  if(uzaklik <= 30) {
    dur();
    motor.write(90);
    int saguzaklik = mesafe();


    if(saguzaklik > 30) {
      geri();
      sag();
    } else {
      motor.write(270);
      int soluzaklik = mesafe();

      if(soluzaklik > 30) {
        geri();
        sol();
      } else {
        geri();
        sol();
      }
    }
    
  } else {
    ileri();
  }

  */
}
