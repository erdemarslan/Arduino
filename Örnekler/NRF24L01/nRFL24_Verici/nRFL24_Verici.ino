#include <Enrf24.h>
#include <nRF24L01.h>
#include <string.h> // konuda bahsedilen string kütüphanesi
#include <SPI.h>

Enrf24 nRF(9, 10, 2);  // CE , CSN/CS/SS , IRQ

// aşağıdaki değişken tanımlaması satırlarından sadece biri kullanılacak
const byte alici_adresi[] = { 0xDE, 0xAD, 0xBE, 0x0F, 0x01 }; // verici kodları için
const byte verici_adresi[] = { 0xDE, 0xAD, 0xBE, 0x0F, 0x02 }; // verici kodları için

const int ledPin = 6;

int sayi = 0;

bool aliciMi = true;

void setup() {
  Serial.begin(9600);
   // Verici için Setup() bloğu //
   ///////////////////////////////
   SPI.begin(); // SPI başlat
   SPI.setDataMode(SPI_MODE0); // SPI MODE0 seçildi
   SPI.setBitOrder(MSBFIRST); // bit sıralaması MSB'den LSB'ye doğru ayarlandı
   
   // veri-oranı 250000/1000000/2000000, kanal 0/125
   nRF.begin(1000000,64);  
   nRF.setTXaddress(verici_adresi);

   nRF.setRXaddress(alici_adresi);
   nRF.enableRX();  // Dinlemeye başla
}

void loop() {
  // put your main code here, to run repeatedly:

  char gelen_bilgi[33]; // gelen bilgi için geçici dizi değişken
   int bilgi=0; // strinden sayısala dönüşümden sonra okunana değerin saklanacağı değişken tanımlandı
   if (nRF.read(gelen_bilgi)) // vericiden bilgi geldiyse bunu gelen_bilgi adlı dizi değişkene aktarmaktadır.
   {
     Serial.print("2. cihazdan Alinan veri: ");
     bilgi = atoi(gelen_bilgi); // string ifadeyi decimal yani sayısal hale dönüştürme işlemi

     if(bilgi % 2 == 0) {
       digitalWrite(ledPin, HIGH);
     } else {
       digitalWrite(ledPin, LOW);
     }
     
     Serial.println(bilgi);
   }
  
  Serial.print("1. cihaz Gonderilen deger: ");
  nRF.print(sayi);
  nRF.flush();
  Serial.println(sayi);
  sayi++;
  delay(1000);
}
