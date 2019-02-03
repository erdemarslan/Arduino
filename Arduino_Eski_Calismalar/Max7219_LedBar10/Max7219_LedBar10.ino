// V4 2014-01-21 (Improved logic of bit shifting for last 2 LEDs)
// Notes: 33K Rset reisistor must! Also decoupling 10uF polarized and .1uf ceramic capacitors needed on VCC line
// (c) 2014 LensDigital.com
#include "LedControl.h"

#define MAX_LED 10 // Number of LEDs in bar graph array
#define MAX_BRIGHTNESS 15 // 0-15 LED brightness
#define pauseLED 50
#define BLINK_SPEED 250 // Speed of blinking
#define LED_TIMEOUT 10000 // Time out after which LED bar turns off

boolean isOn=true;
boolean isSleeping=false;
boolean okBlink=false; // Triggers blinking
unsigned long lastBlink = 0; // Last time LEDs blinked
unsigned long lastOn = 0; // Last time LED Bar was turned off

byte blinkCount=0; // Counts blinks/flashes
byte Bars=10; // Temp. number of barts to light up

/*
 pin 9 is connected to the DataIn 
 pin 8 is connected to the CLK 
 pin 7 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(9,8,7,1);

void setup() {
  Serial.begin(115200);
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,MAX_BRIGHTNESS);
  /* and clear the display */
  lc.clearDisplay(0);
 LEDBarDisplay (Bars);
 okBlink=true;
 delay (1000);
  Serial.println ("ready");
}

void loop() { 

  chaseLED();
}

// =============================================================================
// --- Main Function. Light up "mark" number of sequential LEDs in Bar Graph
// =============================================================================
void LEDBarDisplay(int mark) {
  if (mark < 0 || mark > MAX_LED) return; // Sanity check, cannot be more than max or less than 0 LEDs
  byte LEDBit=B11111111;
 if (mark <=8) { // First row (first 8 LEDs)
    LEDBit=LEDBit << (8-mark); // Shift bits to the left
    lc.setRow(0,0,LEDBit);  //Light up LEDs
    lc.setRow(0,1,B00000000); // Blank out second row
  }
  else { // Second row (LED 9-10)
   LEDBit=LEDBit << (16-mark); // Shift bits to the left. 16 is 8*row
   lc.setRow(0,0,B11111111);  //Light first 8 LEDs
   lc.setRow(0,1,LEDBit); 
  }
    //Serial.print ("Mark is: "); Serial.print (mark); Serial.print (". In Binary: ");
  //  Serial.println (LEDBit,BIN);
  lastOn=millis();
  isSleeping=false;
}

// ===================================================================================================
// --- Blinks LED Bar Graph for specified number of times. Must be permitted with okBlink global var
// ===================================================================================================
void LEDBarBlink (int blinkTimes) {
 if (!okBlink) return;
 if (millis()-lastBlink > BLINK_SPEED) { 
   if (isOn) { // Turn LEDs off
     isOn=false;
     LEDBarDisplay(0);
   }
   else { // Turn LEDs on
    isOn=true;
    LEDBarDisplay(Bars);
    blinkCount++;
    if (blinkCount > blinkTimes-1) {
    blinkCount=0;
    okBlink=false; 
    }
   }
   lastBlink=millis();
   
   }
}
// ====================================================================
// --- Sleep mode. Clears display after timeout period
// ====================================================================
void sleepLEDBar() {
  if (isSleeping) return; // Already off
  if (millis()-lastOn > LED_TIMEOUT) { 
       lc.clearDisplay(0);
       isSleeping=true;
  }
}

// ====================================================================
// --- Back and forth pattern chase
// ====================================================================
void chaseLED() {
  for (int i=0;i<=10;i++) {
    LEDBarDisplay(i);
    delay (pauseLED);
  }
  
  for (int i=10;i>=0;i--) {
    LEDBarDisplay(i);
    delay (pauseLED);
  }
      
}

// ====================================================================
// --- Back and forth pattern chase
// ====================================================================
void chaseLED_old() {
  for (int i=0;i<10;i++) {
    if (i<8) lc.setLed(0,0,i,true);
    else  lc.setLed(0,1,i-8,true);
    delay (pauseLED);
  }

  for (int i=10;i>=0;i--) {
    if (i<8) lc.setLed(0,0,i,false);
    else  lc.setLed(0,1,i-8,false);
    delay (pauseLED);
  }
      
}

