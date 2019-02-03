/*
 * Mesefe Sensörü + nRF24L01
 * Boy Ölçer
 * 
 * Erdem Arslan
 * Terminal
 */
#include <Enrf24.h>
#include <nRF24L01.h>
#include <string.h> // konuda bahsedilen string kütüphanesi
#include <SPI.h>

Enrf24 nRF(9, 10, 2);  // CE , CSN/CS/SS , IRQ

// aşağıdaki değişken tanımlaması satırlarından sadece biri kullanılacak
const byte alici_adresi[] = { 0x74, 0x65, 0x72, 0x6d, 0x69 }; // alıcı kodları için
const byte verici_adresi[] = { 0x63, 0x6c, 0x69, 0x65, 0x6e }; // verici kodları için


volatile bool dinleme = false;
volatile bool kalibreEdildi = false;

unsigned int mesafe, boy, mod;


void setup() {
  // Ayarlama kodları
  mod = 0;
  mesafe = 0;
  boy = 0;

  Serial.begin(9600);
  
  SPI.begin();
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);

  nRF.begin(1000000, 64);
  nRF.setTXaddress(verici_adresi);

  nRF.setRXaddress(alici_adresi);
  nRF.enableRX();

  attachInterrupt(digitalPinToInterrupt(3), butonaBasildi, RISING);

  Serial.println("Kalibrasyon icin lutfen tusa basiniz...");

  while(dinleme == false) {
    ;
  }
}

void loop() {
  // Dönen kodlar
  //Serial.println(dinleme);
  char gelen_bilgi[10];
  int bilgi = 0;

  if(nRF.read(gelen_bilgi)) {
    Serial.print("Gelen veri: ");
    bilgi = atoi(gelen_bilgi);
    Serial.println(bilgi);

    if(dinleme) {
      if(mod == 0) {
        mesafe = bilgi;
        Serial.print("Cihaz kalibre edildi: ");
        Serial.print(bilgi);
        Serial.println(" cm");
        mod = 1;
      }

      if(mod == 1) {
        boy = bilgi;
        int cisminBoyu = 0;
        cisminBoyu = mesafe - boy;

        Serial.print("Cismin Boyu: ");
        Serial.print(cisminBoyu);
        Serial.println(" cm");
      }

      dinleme = false;
      delay(200);
    }
  }
}

void butonaBasildi() {
  dinleme = true;
  nRF.print("100");
  nRF.flush();
  delay(100);
}

