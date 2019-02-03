/*
 * Mesefe Sensörü + nRF24L01
 * Boy Ölçer
 * 
 * Erdem Arslan
 * İstemci
 */
#include <Enrf24.h>
#include <nRF24L01.h>
#include <string.h> // konuda bahsedilen string kütüphanesi
#include <SPI.h>

#include <NewPing.h>

Enrf24 nRF(9, 10, 2);  // CE , CSN/CS/SS , IRQ

NewPing sonar(3, 4, 300); // NewPing setup of pins and maximum distance.

// aşağıdaki değişken tanımlaması satırlarından sadece biri kullanılacak
const byte verici_adresi[] = { 0x74, 0x65, 0x72, 0x6d, 0x69 }; // alıcı kodları için
const byte alici_adresi[] = { 0x63, 0x6c, 0x69, 0x65, 0x6e }; // verici kodları için

unsigned int mesafe;

void setup() {
  // Ayarlama kodları
  mesafe = 0;
  Serial.begin(9600);
  
  SPI.begin();
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);

  nRF.begin(1000000, 64);
  nRF.setTXaddress(verici_adresi);

  nRF.setRXaddress(alici_adresi);
  nRF.enableRX();
}

void loop() {
  // Dönen kodlar
  char gelen_bilgi[10];
  int bilgi = 0;

  if(bilgi == 100) {
      nRF.print(sonar.ping_cm());
      nRF.flush();
      delay(500);
    }

  if(nRF.read(gelen_bilgi)) {
    Serial.print("Gelen veri: ");
    bilgi = atoi(gelen_bilgi);
    Serial.println(bilgi);

    if(bilgi == 100) {
      nRF.print(sonar.ping_cm());
      nRF.flush();
      delay(500);
    }
  }
}

