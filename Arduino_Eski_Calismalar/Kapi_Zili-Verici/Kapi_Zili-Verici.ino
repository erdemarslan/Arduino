/*
 * Kapı Zili - Verici
 * 
 * Biga İmam Hatip Ortaokulu
 * Robocanlar v.1.0
 * 
 * Erdem ARSLAN
 */

#include <Enrf24.h>
#include <nRF24L01.h>
#include <SPI.h>
Enrf24 nRF(9, 10, 2);  // CE , CSN/CS/SS , IRQ

const byte verici_adresi[] = { 0xEA, 0xEA, 0xBE, 0x0F, 0x02 }; // verici kodları için

const int butonPin = 3;

void setup() {
  // Verici için Setup() bloğu //
  ///////////////////////////////
  SPI.begin(); // SPI başlat
  SPI.setDataMode(SPI_MODE0); // SPI MODE0 seçildi
  SPI.setBitOrder(MSBFIRST); // bit sıralaması MSB'den LSB'ye doğru ayarlandı

  // veri-oranı 250000/1000000/2000000, kanal 0/125
  nRF.begin(1000000,64);  
  nRF.setTXaddress(verici_adresi);

  pinMode(butonPin, INPUT);

  Serial.begin(9600);
  Serial.println("Verici basladi!");

  //attachInterrupt(digitalPinToInterrupt(butonPin), butonaBastim, RISING);
  
}

// Bu kısım sadece interrupt çalıştırılırsa devreye kullanılacak!
/*
void butonaBastim() {
  nRF.print(101);
  nRF.flush();
}
*/
void loop() {
  // put your main code here, to run repeatedly:
  int butonDurum = digitalRead(butonPin);

  if(butonDurum == HIGH) {
    Serial.println("Butona basildi");
    nRF.print(101);
    nRF.flush();
    delay(1000);
  }

  delay(500);
}
