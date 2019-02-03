#include <SPI.h>
#include "octasonic.h"
#include "notes.h"

int notes[] = {
  NOTE_A3, 
  NOTE_B3, 
  NOTE_C4,
  NOTE_D4,
  NOTE_E4,
  NOTE_F4,
  NOTE_G4,
  NOTE_A4
};

const int chipSelectPin = 10;
const int speakerPin = 9;
const int sensorCount = 8;

Octasonic octasonic(chipSelectPin);

void setup() {
  Serial.begin(9600);

  octasonic.set_sensor_count(sensorCount);
}

void loop() {
  
  // determine the first sensor that had a distance less than 20
  int note = -1;
  for (int i=0; i<sensorCount; i++) {
    int j = octasonic.get_sensor_reading(i);
    if (j < 20) {
      note = i;
      break;
    }
  }
  // play the selected note
  if (note == -1) {
    noTone(speakerPin); 
  } else {
    tone(speakerPin, notes[note]);
  }
}