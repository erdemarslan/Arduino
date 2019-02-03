#include <Tone.h>

Tone solo;
Tone bass;
Tone rythm;

const int t = 600;  // quater note duration
const int tt = t*2;
const int t14 = round(t*1/4);
const int t24 = round(t*2/4);
const int t34 = round(t*3/4);

const int bassLedPin = 6;  // bass led signal pin (aka A1)
const int rythmLedPin = 7;  // rythm led signal pin (aka A3)
const int soloLedPin = 8;  // solo led signal pin (aka A5)

void wait(Tone t)
{
  while (t.isPlaying()) { }  
}

int bassLedState = LOW;
void switchBassLed()
{
  if (bassLedState == LOW)
    bassLedState = HIGH;
  else
    bassLedState = LOW;
  digitalWrite(bassLedPin, bassLedState);
}

int rythmLedState = LOW;
void switchRythmLed()
{
  if (rythmLedState == LOW)
    rythmLedState = HIGH;
  else
    rythmLedState = LOW;
  digitalWrite(rythmLedPin, rythmLedState);
}

int soloLedState = LOW;
void switchSoloLed()
{
  if (soloLedState == LOW)
    soloLedState = HIGH;
  else
    soloLedState = LOW;
  digitalWrite(soloLedPin, soloLedState);
}



void setup(void)
{
  pinMode(14, OUTPUT); // led ground pin (aka A0)
  pinMode(16, OUTPUT); // led ground pin (aka A2)
  pinMode(18, OUTPUT); // led ground pin (aka A4)
  pinMode(bassLedPin, OUTPUT);  // bass led signal pin
  pinMode(rythmLedPin, OUTPUT);  // rythm led signal pin
  pinMode(soloLedPin, OUTPUT);  // solo led signal pin

  pinMode(2, OUTPUT);  // solo buzzer ground pin
  pinMode(9, OUTPUT);  // rythm buzzer ground pin 

  solo.begin(4);  // solo buzzer signal pin
  bass.begin(5);  // bass buzzer signal pin
  rythm.begin(3);  // rythm buzzer signal pin

        solo.play(NOTE_D4, t34); switchSoloLed();
        wait(solo);
        solo.play(NOTE_D4, t14); switchSoloLed();
        wait(solo);
}



void loop(void)
{

bass.play(NOTE_G3, t); switchBassLed();
  rythm.play(NOTE_G4, t24); switchRythmLed();
        solo.play(NOTE_E4, t); switchSoloLed();
        wait(rythm);
  rythm.play(NOTE_B4, t14); switchRythmLed();
        wait(rythm);
  rythm.play(NOTE_D5, t14); switchRythmLed();
        wait(rythm);
bass.play(NOTE_B3, t); switchBassLed();
  rythm.play(NOTE_G4, t24); switchRythmLed();
        solo.play(NOTE_D4, t); switchSoloLed();
        wait(rythm);
  rythm.play(NOTE_B4, t14); switchRythmLed();
        wait(rythm);
  rythm.play(NOTE_D5, t14); switchRythmLed();
        wait(rythm);
bass.play(NOTE_D4, t); switchBassLed();
  rythm.play(NOTE_G4, t24); switchRythmLed();
        solo.play(NOTE_G4, t); switchSoloLed();
        wait(rythm); 
  rythm.play(NOTE_B4, t14); switchRythmLed();
        wait(rythm);
  rythm.play(NOTE_D5, t14); switchRythmLed();
        wait(rythm);

bass.play(NOTE_D4, t); switchBassLed();
  rythm.play(NOTE_D5, t24); switchRythmLed();
        solo.play(NOTE_FS4, tt); switchSoloLed();
        wait(rythm);
  rythm.play(NOTE_FS5, t14); switchRythmLed();
        wait(rythm);
  rythm.play(NOTE_A5, t14); switchRythmLed();
        wait(rythm);
bass.play(NOTE_FS4, t); switchBassLed();
  rythm.play(NOTE_D5, t24); switchRythmLed();
        wait(rythm);
  rythm.play(NOTE_FS5, t14); switchRythmLed();
        wait(rythm);
  rythm.play(NOTE_A5, t14); switchRythmLed();
        wait(rythm);
bass.play(NOTE_A4, t); switchBassLed();
  rythm.play(NOTE_D5, t24); switchRythmLed();
        solo.play(NOTE_D4, t34); switchSoloLed();
        wait(rythm);        
  rythm.play(NOTE_FS5, t14); switchRythmLed();
        wait(rythm);
  rythm.play(NOTE_A5, t14); switchRythmLed();    
        solo.play(NOTE_D4, t14); switchSoloLed();
        wait(rythm);

bass.play(NOTE_D4, t); switchBassLed();
  rythm.play(NOTE_D5, t24); switchRythmLed();
        solo.play(NOTE_E4, t); switchSoloLed();
        wait(rythm);
  rythm.play(NOTE_FS5, t14); switchRythmLed();
        wait(rythm);
  rythm.play(NOTE_A5, t14); switchRythmLed();
        wait(rythm);        
bass.play(NOTE_FS4, t); switchBassLed();
  rythm.play(NOTE_D5, t24); switchRythmLed();
        solo.play(NOTE_D4, t); switchSoloLed();
        wait(rythm);
  rythm.play(NOTE_FS5, t14); switchRythmLed();
        wait(rythm);
  rythm.play(NOTE_A5, t14); switchRythmLed();
        wait(rythm);         
bass.play(NOTE_A4, t); switchBassLed();
  rythm.play(NOTE_D5, t24); switchRythmLed();
        solo.play(NOTE_A4, t); switchSoloLed();
        wait(rythm);
  rythm.play(NOTE_FS5, t14); switchRythmLed();
        wait(rythm);
  rythm.play(NOTE_A5, t14); switchRythmLed();
        wait(rythm);  


bass.play(NOTE_G3, t); switchBassLed();
  rythm.play(NOTE_G4, t24); switchRythmLed();
        solo.play(NOTE_G4, tt); switchSoloLed();
        wait(rythm);        
  rythm.play(NOTE_B4, t14); switchRythmLed();
        wait(rythm);
  rythm.play(NOTE_D5, t14); switchRythmLed();
        wait(rythm);
bass.play(NOTE_B3, t); switchBassLed();
  rythm.play(NOTE_G4, t24); switchRythmLed();
        wait(rythm);
  rythm.play(NOTE_B4, t14); switchRythmLed();
        wait(rythm);
  rythm.play(NOTE_D5, t14); switchRythmLed();
        wait(rythm);        
bass.play(NOTE_D4, t); switchBassLed();
  rythm.play(NOTE_G4, t24); switchRythmLed();
        solo.play(NOTE_D4, t34); switchSoloLed();
        wait(rythm);
  rythm.play(NOTE_B4, t14); switchRythmLed();
        wait(rythm);
  rythm.play(NOTE_D5, t14); switchRythmLed();       
        solo.play(NOTE_D4, t14); switchSoloLed();
        wait(rythm);

bass.play(NOTE_G3, t); switchBassLed();
  rythm.play(NOTE_G4, t24); switchRythmLed();
        solo.play(NOTE_D5, t); switchSoloLed();
        wait(rythm);
  rythm.play(NOTE_B4, t14); switchRythmLed();
        wait(rythm);
  rythm.play(NOTE_D5, t14); switchRythmLed();
        wait(rythm);        
bass.play(NOTE_B3, t); switchBassLed();
  rythm.play(NOTE_G4, t24); switchRythmLed();
        solo.play(NOTE_B4, t); switchSoloLed();
        wait(rythm);
  rythm.play(NOTE_B4, t14); switchRythmLed();
        wait(rythm);
  rythm.play(NOTE_D5, t14); switchRythmLed();
        wait(rythm);          
bass.play(NOTE_D4, t); switchBassLed();
  rythm.play(NOTE_G4, t24); switchRythmLed();
        solo.play(NOTE_G4, t); switchSoloLed();
        wait(rythm);
  rythm.play(NOTE_B4, t14); switchRythmLed();
        wait(rythm);
  rythm.play(NOTE_D5, t14); switchRythmLed();
        wait(rythm);       

bass.play(NOTE_C4, t); switchBassLed();
  rythm.play(NOTE_C5, t24); switchRythmLed();
        solo.play(NOTE_FS4, t); switchSoloLed();
        wait(rythm);
  rythm.play(NOTE_E5, t14); switchRythmLed();  
        wait(rythm);
  rythm.play(NOTE_G5, t14); switchRythmLed();   
        wait(rythm);       
bass.play(NOTE_E4, t);  switchBassLed();
  rythm.play(NOTE_C5, t24); switchRythmLed();
        solo.play(NOTE_E4, t); switchSoloLed();
        wait(rythm);
  rythm.play(NOTE_E5, t14); switchRythmLed();   
        wait(rythm);
  rythm.play(NOTE_G5, t14); switchRythmLed();   
        wait(rythm);          
bass.play(NOTE_G4, t); switchBassLed();
  rythm.play(NOTE_C5, t24); switchRythmLed();
        solo.play(NOTE_C5, t34); switchSoloLed();
        wait(rythm);
  rythm.play(NOTE_E5, t14); switchRythmLed();
        wait(rythm); 
  rythm.play(NOTE_G5, t14); switchRythmLed();     
        solo.play(NOTE_C5, t14); switchSoloLed();
        wait(rythm);

bass.play(NOTE_G3, t); switchBassLed();
  rythm.play(NOTE_G4, t24); switchRythmLed();
        solo.play(NOTE_B4, t); switchSoloLed();
        wait(rythm);
  rythm.play(NOTE_B4, t14); switchRythmLed();
        wait(rythm);
  rythm.play(NOTE_D5, t14); switchRythmLed();
        wait(rythm);         
bass.play(NOTE_D3, t); switchBassLed();
  rythm.play(NOTE_G4, t24); switchRythmLed();
        solo.play(NOTE_G4, t); switchSoloLed();
        wait(rythm);
  rythm.play(NOTE_B4, t14); switchRythmLed();
        wait(rythm);
  rythm.play(NOTE_D5, t14); switchRythmLed();
        wait(rythm); 
bass.play(NOTE_FS3, t); switchBassLed();
  rythm.play(NOTE_D5, t24); switchRythmLed();
        solo.play(NOTE_A4, t); switchSoloLed();
        wait(rythm);
        wait(rythm);
  rythm.play(NOTE_FS5, t14); switchRythmLed();
        wait(rythm);
  rythm.play(NOTE_A5, t14); switchRythmLed();
        wait(rythm);          

bass.play(NOTE_G3, t); switchBassLed();
  rythm.play(NOTE_G4, t24); switchRythmLed();
        solo.play(NOTE_G4, tt); switchSoloLed();
        wait(rythm);        
  rythm.play(NOTE_B4, t14); switchRythmLed();
        wait(rythm);
  rythm.play(NOTE_D5, t14); switchRythmLed();
        wait(rythm);
bass.play(NOTE_B3, t); switchBassLed();
  rythm.play(NOTE_G4, t24); switchRythmLed(); 
        wait(rythm);
  rythm.play(NOTE_B4, t14); switchRythmLed();
        wait(rythm);
  rythm.play(NOTE_D5, t14); switchRythmLed();
        wait(rythm);      
        solo.play(NOTE_D4, t34); switchSoloLed();
        wait(solo);
        solo.play(NOTE_D4, t14); switchSoloLed();
        wait(solo);

}

