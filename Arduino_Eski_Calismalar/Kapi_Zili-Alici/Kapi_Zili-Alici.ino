/*
 * Kapı Zili - Alıcı
 * 
 * Biga İmam Hatip Ortaokulu
 * Robocanlar v.1.0
 * 
 * Erdem ARSLAN
 */

#include <Enrf24.h>
#include <nRF24L01.h>
#include <string.h> // gelen stringleri işlemek için
#include <SPI.h>
#include <Adafruit_NeoPixel.h>

Enrf24 nRF(9, 10, 2);  // CE , CSN/CS/SS , IRQ

const byte alici_adresi[] = { 0xEA, 0xEA, 0xBE, 0x0F, 0x02 }; // verici kodları için

#define PIXEL_PIN    6    // Neopixelin bağlı olduğu pin
#define PIXEL_COUNT  8    // Neopixelin led sayısı

Adafruit_NeoPixel pixel = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  // Alıcı için Setup() bloğu //
  ///////////////////////////////
  pixel.begin();
  pixel.show(); // Initialize all pixels to 'off'

  Serial.begin(9600);
  
  SPI.begin(); // SPI başlat
  SPI.setDataMode(SPI_MODE0); // SPI MODE0 seçildi
  SPI.setBitOrder(MSBFIRST); // bit sıralaması MSB'den LSB'ye doğru ayarlandı

  // veri-oranı 250000/1000000/2000000, kanal 0/125
  nRF.begin(1000000,64);

  nRF.setRXaddress(alici_adresi);
  nRF.enableRX();  // Dinlemeye başla

  Serial.println("Dinlemeye basladik!");
}

void loop() {
  // put your main code here, to run repeatedly:
  char gelen_bilgi[33];
  if(nRF.read(gelen_bilgi)) {
    int bilgi = atoi(gelen_bilgi);
    Serial.println(bilgi);
    if(bilgi == 101) {
      // ledleri yak!
      gokkusagi(20);
      delay(500);
    }
  }
}


void gokkusagi(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<pixel.numPixels(); i++) {
      pixel.setPixelColor(i, Wheel((i+j) & 255));
    }
    pixel.show();
    delay(wait);
  }

  for(int z=0; z<PIXEL_COUNT; z++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixel.setPixelColor(z, pixel.Color(0,0,0)); // Moderately bright green color.
    pixel.show(); // This sends the updated pixel color to the hardware.
    delay(20); // Delay for a period of time (in milliseconds).
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixel.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixel.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixel.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
