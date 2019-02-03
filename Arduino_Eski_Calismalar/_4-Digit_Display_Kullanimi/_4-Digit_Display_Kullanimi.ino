/*
 * 4-Digit Display (TM1637) Gösterge Kullanımı
 * 
 * Erdem ARSLAN
 * www.erdemarslan.com
 * www.erdemarslan.com.tr
 * www.robothane.net
 * www.robocanlar.com
 * 
//      A
//     ---
//  F |   | B
//     -G-
//  E |   | C
//     ---
//      D
 * 
 * 
 */

#include <Arduino.h>
#include <TM1637Display.h>

#define CLK 6
#define DIO 7


const uint8_t SEG_EVET[] =  {
  SEG_A | SEG_F | SEG_G | SEG_E | SEG_D, // E
  SEG_E | SEG_D | SEG_C, // v
  SEG_A | SEG_F | SEG_G | SEG_E | SEG_D, // E
  SEG_F | SEG_G | SEG_E | SEG_D // E
};

TM1637Display display(CLK, DIO);

void setup() {
  // Parlaklık - 0 ile 7 arasında 7 en parlak, true false ışık açık kapalı
  display.setBrightness(7, true);
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < 10; i++) {
    if(i%2 == 0) {
      display.showNumberDecEx(1715, 64); // ortadaki : çıkıyor 64 ve daha büyükse
    } else {
      display.showNumberDecEx(1715, 63); // ortadaki : çıkmıyor 63 ve daha küçükse
    }
    delay(1000);
  }

  display.setSegments(SEG_EVET);
  while(1);
}
