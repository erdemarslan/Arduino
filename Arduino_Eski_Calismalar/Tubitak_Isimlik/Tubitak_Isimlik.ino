/*
 * Arduino ile yapılmış, Yaka kartı
 * Her 10 saniyede bir bilgiler değişir
 * 2. Satırda ise ses seviyesi verilir.
 * 
 */

#include <LiquidCrystal_I2C.h>

// LCD ekranı tanımlıyoruz. Adresi 0x3F 16 satır 2 sütun ekran
LiquidCrystal_I2C lcd(0x3F, 16,2);

const short mikrofonPin = A0;
const short orneklemeSayisi = 50; // 50ms = 20Hz 'lik bir örnekleme yapar. Yani 50 ms boyunca mikrofondan veri toplar ve analiz eder.
const unsigned long degisimSuresi = 10000; // 10000ms yani 10 sn. İsim bilgileri 10 saniyede bir değişsin
const unsigned long ekranBeklemeSuresi = 40000; // 40 saniye
const unsigned int ekranIsigiAcmaFarki = 10; // ses farkı ne kadar olursa ekran açılsın. Gürültülü ortamlarda bu değeri yükseltmek gerekir.

unsigned long oncekiDegisimZamani = 0; // Ekranın bir önceki değişim zamanı
unsigned long isikAcilmaZamani = 0; // ışığın bir önceki değişim zamanı
unsigned int sesDuzeyi; // ses düzeyini tutan değişken.
short durum = 0; // 0 - İsim, 1 - Proje Adı, 2 - Tübitak Bilgisi
bool ekranAcikmi = true; // ekranın açık olup olmadığı değerini tutuyor.

// LCD için özel karakter. LCD de bir alanı tamamen dolduruyor. Ses düzeyini göstermek için.
byte tamDolu[8] = {
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};


void setup() {
  // Hata ayıklama özelliğini aç
  Serial.begin(9600);
  // Ekranı başlat
  lcd.init();
  // Özel karakteri tanımla
  lcd.createChar(0, tamDolu);
  // Ekran arka ışığını yak
  lcd.backlight();
  // Ekrana hoş geldiniz yaz
  lcd.setCursor(2,0);
  lcd.print("Hos Geldiniz");
  lcd.setCursor(3,1);
  lcd.print("Basliyoruz");
  // bir kaç saniye de bekleyiverelim. Hoş geldin gözüksün
  delay(5000);
  lcd.clear();
  yaz("AKILLI iSiMLiK");
  //oncekiDegisimZamani = millis()+degisimSuresi;
}

void loop() {
  // Ekran ışığını kontrol et!
  isikKontrol(); // aşağıdaki aynı adlı fonksiyonu inceleyin.
  // Ekrana İsimleri Bas
  isimYaz(); // aşağıdaki aynı adlı fonksiyonu inceleyin.
  // Ses Düzeyini Yaz
  sesDuzeyiniYaz(); // aşağıdaki aynı adlı fonksiyonu inceleyin.
}

void isikKontrol() {
  // millis() fonksiyonu, arduino açıldıktan şimdiye kadar geçen süreyi milisaniye cinsinden bize geri verir. delay yerine iki millis arasındaki
  // farka bakarak ne kadar zaman geçtiğini anlayabilir ve istediğimiz değeri aştığında işlem yap deyebiliriz.
  // delaydan farkı delaydaki gibi işlemleri durdurmaz.
  // && ve anlamına gelir.
  if((millis() - isikAcilmaZamani) > ekranBeklemeSuresi && ekranAcikmi == true) {
    lcd.noBacklight(); // ekran ışığını kapat
    lcd.noDisplay(); // ekran görüntüsünü kapat.
    // yukarıdaki iki lcd komutu pil tasarrufu için kullanılacak!
    ekranAcikmi = false;
  }
}

void isimYaz() {
  if(millis() - oncekiDegisimZamani > degisimSuresi) {
    if(durum == 0) {
      // yaz(); fonksiyonu verilen metni düzenleyip yazar! Bu fonksiyonu biz yazdık.
      yaz(F("Erdem Arslan")); // Bir stringi (metni) F() içinde yazarsak, bu metin hafızada tutulmaz. böylelikle ram bellek boş yere dolmaz.
    }
    else if(durum == 1) {
      yaz(F("Proje Yurutucusu"));
    }
    else if(durum == 2) {
      yaz(F("Tubitak 4006"));
    }

    oncekiDegisimZamani = millis();
    durum = durum +1;
    if(durum > 2) {
      durum = 0;
    }
  }
}

void yaz(String metin) {
  lcd.setCursor(0,0);
  lcd.print("                ");
  // Aşağıda yaptığımız işlem metni ortaya yazdırmak içindi. metnin uzunluğunu bul, 16 dan çıkart, kalanı 2 ye böl ve çıkan sayı kadar imleci sağa al ve yazmaya başla
  int cikarma = 16 - metin.length();
  int baslama = cikarma % 2 == 0 ? (cikarma / 2) : ((cikarma + 1) / 2);
  lcd.setCursor(baslama, 0);
  lcd.print(metin);
}

void sesDuzeyiniYaz() {
  unsigned long baslamaZamani = millis();
  unsigned int frekansFarki = 0;

  unsigned int maxSinyal = 0;
  unsigned int minSinyal = 1024;

  // örnekleme sayısı kadar örnek al ve min ve max ses düzeylerini belirle!
  while(millis() - baslamaZamani < orneklemeSayisi) {
    sesDuzeyi = analogRead(mikrofonPin);

    if(sesDuzeyi < 1024) {
      if(sesDuzeyi > maxSinyal) {
        maxSinyal = sesDuzeyi;
      } else if(sesDuzeyi < minSinyal) {
        minSinyal = sesDuzeyi;
      }
    }
  }
  
  frekansFarki = maxSinyal - minSinyal;
  Serial.println(frekansFarki);
  // Eğer fark 10'dan fazlaysa ve ekran ışığı açık değilse aç!
  ekranIsigiKontrol(frekansFarki);
  // Frekans farkını ekrana bas!
  farkiEkranaBas(frekansFarki);
}

void ekranIsigiKontrol(int fark) {
  if(fark > ekranIsigiAcmaFarki) {
    if(ekranAcikmi == false) {
      lcd.backlight();
      lcd.display();
      ekranAcikmi = true;
      isikAcilmaZamani = millis();
    }
  }
}

void farkiEkranaBas(int fark) {
  if(fark > 15) fark = 15;
  for(int i = 0; i < 16; i++) {
    lcd.setCursor(i,1);
    if(i <= fark) {
      lcd.write((uint8_t)0); // özel karakterler yazdırılırken print yerine write komutu kullanılır.
      //lcd.print("*");
    } else {
      lcd.print(" ");
    }
  }
}


