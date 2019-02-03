#include <Tone.h>

Tone solo;
Tone bass;
Tone ritim;

const byte ldrPin = 2;

const byte ritimBuzzer = 7;
const byte soloBuzzer = 8;
const byte bassBuzzer = 9;

const byte ritimLed = 10;
const byte soloLed = 11;
const byte bassLed = 12;

volatile int muzikCal = 0;

const int t = 600; // çeyrek not süresi
const int tt = t*2;
const int t14 = round(t*1/4);
const int t24 = round(t*2/4);
const int t34 = round(t*3/4);

int bassLedDurum = LOW;
int ritimLedDurum = LOW;
int soloLedDurum = LOW;

void bassLedDegistir() {
  bassLedDurum = bassLedDurum == LOW ? HIGH : LOW;
  digitalWrite(bassLed, bassLedDurum);
}
void ritimLedDegistir() {
  ritimLedDurum = ritimLedDurum == LOW ? HIGH : LOW;
  digitalWrite(ritimLed, ritimLedDurum);
}
void soloLedDegistir() {
  soloLedDurum = soloLedDurum == LOW ? HIGH : LOW;
  digitalWrite(soloLed, soloLedDurum);
}
void bekle(Tone t) {
  while(t.isPlaying()) {}
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(bassLed, OUTPUT);
  pinMode(soloLed, OUTPUT);
  pinMode(ritimLed, OUTPUT);
  pinMode(ldrPin, INPUT);

  
  solo.begin(soloBuzzer);
  ritim.begin(ritimBuzzer);
  bass.begin(bassBuzzer);
/**/
  solo.play(NOTE_D4, t34); soloLedDegistir();
  bekle(solo);
  solo.play(NOTE_D4, t14); soloLedDegistir();
  bekle(solo);
  
  attachInterrupt(digitalPinToInterrupt(ldrPin), ldrDegisti, CHANGE);
}

void ldrDegisti() {
  muzikCal++;
  if(muzikCal > 1) {
    muzikCal = 0;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(analogRead(ldrPin));
  //delay(500);
iyikiDogdun();
  if(muzikCal == 1) {
    
  } else {
    delay(100);
  }
  
}


void iyikiDogdun() {
  solo.play(NOTE_D4, t34); soloLedDegistir();
  bekle(solo);
  solo.play(NOTE_D4, t14); soloLedDegistir();
  bekle(solo);
  
  bass.play(NOTE_G3, t); bassLedDegistir();
  ritim.play(NOTE_G4, t24); ritimLedDegistir();
  solo.play(NOTE_E4, t); soloLedDegistir();
  bekle(ritim);
  ritim.play(NOTE_B4, t14); ritimLedDegistir();
  bekle(ritim);
  ritim.play(NOTE_D5, t14); ritimLedDegistir();
  bekle(ritim);
  bass.play(NOTE_B3, t); bassLedDegistir();
  ritim.play(NOTE_G4, t24); ritimLedDegistir();
  solo.play(NOTE_D4, t); soloLedDegistir();
  bekle(ritim);
  ritim.play(NOTE_B4, t14); ritimLedDegistir();
  bekle(ritim);
  ritim.play(NOTE_D5, t14); ritimLedDegistir();
  bekle(ritim);
  bass.play(NOTE_D4, t); bassLedDegistir();
  ritim.play(NOTE_G4, t24); ritimLedDegistir();
  solo.play(NOTE_G4, t); soloLedDegistir();
  bekle(ritim); 
  ritim.play(NOTE_B4, t14); ritimLedDegistir();
  bekle(ritim);
  ritim.play(NOTE_D5, t14); ritimLedDegistir();
  bekle(ritim);

  bass.play(NOTE_D4, t); bassLedDegistir();
  ritim.play(NOTE_D5, t24); ritimLedDegistir();
  solo.play(NOTE_FS4, tt); soloLedDegistir();
  bekle(ritim);
  ritim.play(NOTE_FS5, t14); ritimLedDegistir();
  bekle(ritim);
  ritim.play(NOTE_A5, t14); ritimLedDegistir();
  bekle(ritim);
  bass.play(NOTE_FS4, t); bassLedDegistir();
  ritim.play(NOTE_D5, t24); ritimLedDegistir();
  bekle(ritim);
  ritim.play(NOTE_FS5, t14); ritimLedDegistir();
  bekle(ritim);
  ritim.play(NOTE_A5, t14); ritimLedDegistir();
  bekle(ritim);
  bass.play(NOTE_A4, t); bassLedDegistir();
  ritim.play(NOTE_D5, t24); ritimLedDegistir();
  solo.play(NOTE_D4, t34); soloLedDegistir();
  bekle(ritim);        
  ritim.play(NOTE_FS5, t14); ritimLedDegistir();
  bekle(ritim);
  ritim.play(NOTE_A5, t14); ritimLedDegistir();    
  solo.play(NOTE_D4, t14); soloLedDegistir();
  bekle(ritim);

  bass.play(NOTE_D4, t); bassLedDegistir();
  ritim.play(NOTE_D5, t24); ritimLedDegistir();
  solo.play(NOTE_E4, t); soloLedDegistir();
  bekle(ritim);
  ritim.play(NOTE_FS5, t14); ritimLedDegistir();
  bekle(ritim);
  ritim.play(NOTE_A5, t14); ritimLedDegistir();
  bekle(ritim);        
  bass.play(NOTE_FS4, t); bassLedDegistir();
  ritim.play(NOTE_D5, t24); ritimLedDegistir();
  solo.play(NOTE_D4, t); soloLedDegistir();
  bekle(ritim);
  ritim.play(NOTE_FS5, t14); ritimLedDegistir();
  bekle(ritim);
  ritim.play(NOTE_A5, t14); ritimLedDegistir();
  bekle(ritim);         
  bass.play(NOTE_A4, t); bassLedDegistir();
  ritim.play(NOTE_D5, t24); ritimLedDegistir();
  solo.play(NOTE_A4, t); soloLedDegistir();
  bekle(ritim);
  ritim.play(NOTE_FS5, t14); ritimLedDegistir();
  bekle(ritim);
  ritim.play(NOTE_A5, t14); ritimLedDegistir();
  bekle(ritim);  


  bass.play(NOTE_G3, t); bassLedDegistir();
  ritim.play(NOTE_G4, t24); ritimLedDegistir();
  solo.play(NOTE_G4, tt); soloLedDegistir();
  bekle(ritim);        
  ritim.play(NOTE_B4, t14); ritimLedDegistir();
  bekle(ritim);
  ritim.play(NOTE_D5, t14); ritimLedDegistir();
  bekle(ritim);
  bass.play(NOTE_B3, t); bassLedDegistir();
  ritim.play(NOTE_G4, t24); ritimLedDegistir();
  bekle(ritim);
  ritim.play(NOTE_B4, t14); ritimLedDegistir();
  bekle(ritim);
  ritim.play(NOTE_D5, t14); ritimLedDegistir();
  bekle(ritim);        
  bass.play(NOTE_D4, t); bassLedDegistir();
  ritim.play(NOTE_G4, t24); ritimLedDegistir();
  solo.play(NOTE_D4, t34); soloLedDegistir();
  bekle(ritim);
  ritim.play(NOTE_B4, t14); ritimLedDegistir();
  bekle(ritim);
  ritim.play(NOTE_D5, t14); ritimLedDegistir();       
  solo.play(NOTE_D4, t14); soloLedDegistir();
  bekle(ritim);

  bass.play(NOTE_G3, t); bassLedDegistir();
  ritim.play(NOTE_G4, t24); ritimLedDegistir();
  solo.play(NOTE_D5, t); soloLedDegistir();
  bekle(ritim);
  ritim.play(NOTE_B4, t14); ritimLedDegistir();
  bekle(ritim);
  ritim.play(NOTE_D5, t14); ritimLedDegistir();
  bekle(ritim);        
  bass.play(NOTE_B3, t); bassLedDegistir();
  ritim.play(NOTE_G4, t24); ritimLedDegistir();
  solo.play(NOTE_B4, t); soloLedDegistir();
  bekle(ritim);
  ritim.play(NOTE_B4, t14); ritimLedDegistir();
  bekle(ritim);
  ritim.play(NOTE_D5, t14); ritimLedDegistir();
  bekle(ritim);          
  bass.play(NOTE_D4, t); bassLedDegistir();
  ritim.play(NOTE_G4, t24); ritimLedDegistir();
  solo.play(NOTE_G4, t); soloLedDegistir();
  bekle(ritim);
  ritim.play(NOTE_B4, t14); ritimLedDegistir();
  bekle(ritim);
  ritim.play(NOTE_D5, t14); ritimLedDegistir();
  bekle(ritim);       

  bass.play(NOTE_C4, t); bassLedDegistir();
  ritim.play(NOTE_C5, t24); ritimLedDegistir();
  solo.play(NOTE_FS4, t); soloLedDegistir();
  bekle(ritim);
  ritim.play(NOTE_E5, t14); ritimLedDegistir();  
  bekle(ritim);
  ritim.play(NOTE_G5, t14); ritimLedDegistir();   
  bekle(ritim);       
  bass.play(NOTE_E4, t);  bassLedDegistir();
  ritim.play(NOTE_C5, t24); ritimLedDegistir();
  solo.play(NOTE_E4, t); soloLedDegistir();
  bekle(ritim);
  ritim.play(NOTE_E5, t14); ritimLedDegistir();   
  bekle(ritim);
  ritim.play(NOTE_G5, t14); ritimLedDegistir();   
  bekle(ritim);          
  bass.play(NOTE_G4, t); bassLedDegistir();
  ritim.play(NOTE_C5, t24); ritimLedDegistir();
  solo.play(NOTE_C5, t34); soloLedDegistir();
  bekle(ritim);
  ritim.play(NOTE_E5, t14); ritimLedDegistir();
  bekle(ritim); 
  ritim.play(NOTE_G5, t14); ritimLedDegistir();     
  solo.play(NOTE_C5, t14); soloLedDegistir();
  bekle(ritim);

  bass.play(NOTE_G3, t); bassLedDegistir();
  ritim.play(NOTE_G4, t24); ritimLedDegistir();
  solo.play(NOTE_B4, t); soloLedDegistir();
  bekle(ritim);
  ritim.play(NOTE_B4, t14); ritimLedDegistir();
  bekle(ritim);
  ritim.play(NOTE_D5, t14); ritimLedDegistir();
  bekle(ritim);         
  bass.play(NOTE_D3, t); bassLedDegistir();
  ritim.play(NOTE_G4, t24); ritimLedDegistir();
  solo.play(NOTE_G4, t); soloLedDegistir();
  bekle(ritim);
  ritim.play(NOTE_B4, t14); ritimLedDegistir();
  bekle(ritim);
  ritim.play(NOTE_D5, t14); ritimLedDegistir();
  bekle(ritim); 
  bass.play(NOTE_FS3, t); bassLedDegistir();
  ritim.play(NOTE_D5, t24); ritimLedDegistir();
  solo.play(NOTE_A4, t); soloLedDegistir();
  bekle(ritim);
  bekle(ritim);
  ritim.play(NOTE_FS5, t14); ritimLedDegistir();
  bekle(ritim);
  ritim.play(NOTE_A5, t14); ritimLedDegistir();
  bekle(ritim);          

  bass.play(NOTE_G3, t); bassLedDegistir();
  ritim.play(NOTE_G4, t24); ritimLedDegistir();
  solo.play(NOTE_G4, tt); soloLedDegistir();
  bekle(ritim);        
  ritim.play(NOTE_B4, t14); ritimLedDegistir();
  bekle(ritim);
  ritim.play(NOTE_D5, t14); ritimLedDegistir();
  bekle(ritim);
  bass.play(NOTE_B3, t); bassLedDegistir();
  ritim.play(NOTE_G4, t24); ritimLedDegistir(); 
  bekle(ritim);
  ritim.play(NOTE_B4, t14); ritimLedDegistir();
  bekle(ritim);
  ritim.play(NOTE_D5, t14); ritimLedDegistir();
  bekle(ritim);
}




