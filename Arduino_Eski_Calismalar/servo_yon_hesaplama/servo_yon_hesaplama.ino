/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 90;    // variable to store the servo position

int lastpos = 90;

char harf;

void setup() {
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(pos);

  Serial.print("Position: ");
  Serial.println(pos);
}

void loop() {

  if(Serial.available()) {
    harf = Serial.read();

    if(harf == '+') {
      pos = pos + 5;
    }

    if(harf == '-') {
      pos = pos -5;
    }

    
  }

  if(pos != lastpos) {
      myservo.write(pos);
      lastpos = pos;
      Serial.print("Position:");
      Serial.println(pos);
   }
  /*
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);            // tell servo to go to position in variable 'pos'
    Serial.println(pos);
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  */
}

