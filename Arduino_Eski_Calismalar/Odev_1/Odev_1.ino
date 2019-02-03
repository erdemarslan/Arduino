
/*
 * Bir sayı tanımla!
 * Bu sayıyı 7 kere 10 ile çarp - For döngüsü ile
 * Çıkan sayıyı
 * 3 kere 5 e böl - while döngüsü ile
 * elde ettiğin sayının 8e bölümünden kalanı bul
 * Her adımı serial ekranına yaz
 */

/*
 * Sayıyı seç - 12
 * 12 * 10 * 10 * 10 * 10 * 10 * 10 * 10 = a
 * a / 5 / 5 / 5 = b
 * 
 * b % 8 = c
 * 
 */

/*
 * 1.645.098.112

 * long -> -2147483648 ile 2.147.483.647 arasında değer alır.
 * 
 */

long benimSayim = 8;


void setup() {
  Serial.begin(9600);

  Serial.println("Tanımladigim sayi = " + String(benimSayim));
  
  // For Döngüsü ile Çarpma

  // 1 - 2 - 3 - 4 - 5 - 6 - 7
  for(int i = 1; i <= 7; i++) {
    benimSayim = benimSayim * 10;
  }

  Serial.println("10 kez carpma sonucu = " + String(benimSayim));

  int dongu = 1;

  // 1 - 2 - 3
  while(dongu <= 3) {
    benimSayim = benimSayim / 5;

    dongu++;
  }

  Serial.println("3 kez 5 e bolme sonucu cikan sayi = " + String(benimSayim));

  
  int kalan = benimSayim % 8;
  
  Serial.println("Cikan sayinin 8 e bolumunden kalan = " + String(kalan));

  Serial.println("Yeni odev geliyor....");
}



void loop() {}
