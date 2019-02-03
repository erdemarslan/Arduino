
#include <Adafruit_NeoPixel.h>

#define PIN            6
#define NUMPIXELS      24
#define SENSOR         A0

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);



void setup() {
  // put your setup code here, to run once:
  pixels.begin(); // Neopixeli başlat

  pixels.show(); // daha önceden ledlerin renk bilgisi verilmediğinden bütün ledleri söndürür.

  Serial.begin(9600); // seri ekranı başlat
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensor = analogRead(SENSOR); // sensörden gelen değeri oku
  Serial.println(sensor); // seri ekrana değeri yaz
  int ledSayisi = map(sensor, 0, 800, -1,24); // gelen değeri -1 ile 24 arasında bir sayıya dönüştür
  Serial.println(ledSayisi); // ortaya çıkan sayıyı seri ekrana yazdır
  ledYak(ledSayisi); // ledleri yak
}


void ledYak(int ledsayisi) {

  int k = random(0,255); // rasgele bir renk kodu oluştur
  int y = random(0,255); // rasgele bir renk kodu oluştur
  int m = random(0,255); // rasgele bir renk kodu oluştur

  // bütün ledler için döndür
  for(int i=0; i < NUMPIXELS; i++){
    if(i > ledsayisi) {
      pixels.setPixelColor(i, pixels.Color(0,0,0)); // ledi renksiz yap yani söndür.
    } else {
      pixels.setPixelColor(i, pixels.Color(k,y,m)); // rasgele oluşturulan rengi lede ata
    }
    
    pixels.show(); // ledleri belirttiğimiz renkte yak
    //delay(10); // bekle
  }
  
}

