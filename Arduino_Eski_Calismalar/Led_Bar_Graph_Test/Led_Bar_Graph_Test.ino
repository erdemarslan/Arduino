#include "LedControl.h"

#define MAX_LED 10 // Number of LEDs in bar graph array
#define MAX_BRIGHTNESS 15 // 0-15 LED brightness
#define pauseLED 50
#define BLINK_SPEED 250 // Speed of blinking
#define LED_TIMEOUT 10000 // Time out after which LED bar turns off


LedControl lc = LedControl(9,8,7,1);

void setup() {
  // put your setup code here, to run once:
  lc.shutdown(0,false);

  lc.setIntensity(0, MAX_BRIGHTNESS);

  

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
  //lastOn=millis();
  //isSleeping=false;
}

void loop() {
  // put your main code here, to run repeatedly:
  lc.clearDisplay(0);
  //delay(1000);

  for(int i=0; i < 11; i++) {
    LEDBarDisplay(i);
    delay(1000);
  }
}
