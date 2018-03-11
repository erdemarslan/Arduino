/*
 * Şarj Otomatı 4 Kanal Röle
 * v.1.2
 * 
 * Erdem Arslan
 * http://www.erdemarslan.com/
 * Her hakkı saklıdır.
 * GPL v.2.0
 * 
 */

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 20,4);

// Değişkenlerin başındaki const onların yazılım içinde değişmeyeceğini ifade eder! const - sabit demektir.

// Para Pini Belirtelim
const byte coinPin = 2;

// Ledleri Belirtelim - 4 Led Kullanıldı. Röle Aktifse led yanacak, değilse sönecek
const byte ledPin_1 = 3;
const byte ledPin_2 = 4;
const byte ledPin_3 = 5;
const byte ledPin_4 = 6;

// 4 Adet buton tanımlandı
const byte buttonPin_1 = A0;
const byte buttonPin_2 = A1;
const byte buttonPin_3 = A2;
const byte buttonPin_4 = A3;

// Röle pinleri tanımlandı
const byte relayPin_1 = 7;
const byte relayPin_2 = 8;
const byte relayPin_3 = 9;
const byte relayPin_4 = 10;

// Para ile ilgili tanımlamalar
volatile double pulseKacPara = 1.00; // bu makineden para atıldığında gelen 1 pulsenin kaç liraya denk geleceğini ifade eder.
double sarjdanDusulecekPara = 1.00; // butona bastığında kaç para düşelim bakiyeden!
volatile double lira = 0.00;

// Ekran Modu ile ilgili tanımlamalar!
byte ekranModu = 0; // 0 - Ana Menü | 1 - Şarj Menüsü
byte oncekiEkranModu = 1;
volatile bool modGosterildimi = false;
unsigned int ekranDonguSuresi = 5000; // 5 saniye!
unsigned long sonEkranDegisimi = 0;
unsigned long sonSaniyeGosterimi = 0;


// Rölelerin açık ya da kapalı olması
bool sarjVarmi = false;
bool role_1_Acikmi = false;
bool role_2_Acikmi = false;
bool role_3_Acikmi = false;
bool role_4_Acikmi = false;

unsigned long roleAcikKalmaSuresi = 3600000; // 1 saat milisaniye cinsinden!
//unsigned long roleAcikKalmaSuresi = 10000;

unsigned long role_1_bitmeSuresi = 0;
unsigned long role_2_bitmeSuresi = 0;
unsigned long role_3_bitmeSuresi = 0;
unsigned long role_4_bitmeSuresi = 0;


// Para geldiğinde interrupt ile çalışacak fonksiyon
void paraGeldi() {
  lira = lira + pulseKacPara; // o anki bakiyeye para ekliyoruz!
  ekranModu = 1;
  modGosterildimi = false;
  sonEkranDegisimi = millis() - ekranDonguSuresi - 1000; // her halükarda ekranın değişmesini sağlar!
}

void setup() {

  Serial.begin(9600);
  
  pinMode(ledPin_1, OUTPUT);
  pinMode(ledPin_2, OUTPUT);
  pinMode(ledPin_3, OUTPUT);
  pinMode(ledPin_4, OUTPUT);

  // Buttonlar elektriksel olarak Pullup yapılmalı. 10K direnç kullanın
  // Yazılımsal olarak da pullup yapılabilir ama kararlı çalışmayabilir. tercih meselesi.
  pinMode(buttonPin_1, INPUT_PULLUP);
  pinMode(buttonPin_2, INPUT_PULLUP);
  pinMode(buttonPin_3, INPUT_PULLUP);
  pinMode(buttonPin_4, INPUT_PULLUP);

  
  pinMode(relayPin_1, OUTPUT);
  pinMode(relayPin_2, OUTPUT);
  pinMode(relayPin_3, OUTPUT);
  pinMode(relayPin_4, OUTPUT);

  // Coin Pin mutlaka elektriksel olarak pullup yapılmalı. 10K direnç ile.
  pinMode(coinPin, INPUT);

  // Para makinesi NO ve FAST modlarına getirilirse daha iyi olur
  attachInterrupt(digitalPinToInterrupt(coinPin), paraGeldi, RISING);

  lcd.init();
  lcd.backlight();
  lcd.clear();

  // Son ekran değişimini kaydedelim!
  sonEkranDegisimi = millis();
}

void loop() {
  // Döngüdeki kodlarımız
  // Önce butonları kontrol edelim çünkü mühimler! Para yoksa butonlar çalışmasın!
  if( lira > 0) {
    buttonKontrol();
  }

  // Açık röle varsa zamanlarını kontrol et!
  if(sarjVarmi) {
    roleKontrol();

    if(millis() - sonEkranDegisimi > ekranDonguSuresi) {
      if(ekranModu == 0) {
        ekranModu = 1;
        sonEkranDegisimi = millis();
      } else {
        ekranModu = 0;
        modGosterildimi = false;
        sonEkranDegisimi = millis();
      }
    }
  } else {
    if(ekranModu == 1) {
        ekranModu = 0;
        modGosterildimi = false;
        sonEkranDegisimi = millis();
    }
  }
  
  EkranGoster();
}

void EkranGoster() {
  if(ekranModu == 0) {
    if(modGosterildimi == false) {
      lcd.clear();
      lcd.home();
      lcd.print(" LUTFEN PARA ATINIZ");
      lcd.setCursor(0,1); // 2. satır!
      String bakiye = "BAKIYE: " + String(lira) + " TL";
      lcd.print(bakiye);
      lcd.setCursor(0,2); // 3. satır
      lcd.print("R1    R2    R3    R4");
      lcd.setCursor(0,3); // 4. satır!
      String r1d = role_1_Acikmi == true ? "A" : "K";
      String r2d = role_2_Acikmi == true ? "A" : "K";
      String r3d = role_3_Acikmi == true ? "A" : "K";
      String r4d = role_4_Acikmi == true ? "A" : "K";
      lcd.print(r1d + "     " + r2d + "     " + r3d + "     " + r4d);
      modGosterildimi = true;
      sonEkranDegisimi = millis();
    }
  }

  if(ekranModu == 1) {
    if(millis() - sonSaniyeGosterimi > 1000) {
      lcd.clear();
      long kalansure1 = role_1_Acikmi == true ? role_1_bitmeSuresi - millis() : 0;
      long kalansure2 = role_2_Acikmi == true ? role_2_bitmeSuresi - millis() : 0;
      long kalansure3 = role_3_Acikmi == true ? role_3_bitmeSuresi - millis() : 0;
      long kalansure4 = role_4_Acikmi == true ? role_4_bitmeSuresi - millis() : 0;

      if(kalansure1 == 0) {
        lcd.home();
        lcd.print("ROLE1 - 00:00:00");
      } else {
        int sa1 = kalansure1 / 3600000;
        int da1 = (kalansure1 - (sa1 * 3600000)) / 60000;
        int sn1 = (kalansure1 - (sa1 * 3600000) - (da1 * 60000)) / 1000;

        String ssa1 = sa1 > 10 ? String(sa1) : "0" + String(sa1);
        String sda1 = da1 > 10 ? String(da1) : "0" + String(da1);
        String ssn1 = sn1 > 10 ? String(sn1) : "0" + String(sn1);

        lcd.home();
        lcd.print("ROLE1 - " + ssa1 + ":" + sda1 + ":" + ssn1);
      }

      if(kalansure2 == 0) {
        lcd.setCursor(0,1);
        lcd.print("ROLE2 - 00:00:00");
      } else {
        int sa2 = kalansure2 / 3600000;
        int da2 = (kalansure2 - (sa2 * 3600000)) / 60000;
        int sn2 = (kalansure2 - (sa2 * 3600000) - (da2 * 60000)) / 1000;

        String ssa2 = sa2 > 10 ? String(sa2) : "0" + String(sa2);
        String sda2 = da2 > 10 ? String(da2) : "0" + String(da2);
        String ssn2 = sn2 > 10 ? String(sn2) : "0" + String(sn2);

        lcd.setCursor(0,1);
        lcd.print("ROLE2 - " + ssa2 + ":" + sda2 + ":" + ssn2);
      }


      if(kalansure3 == 0) {
        lcd.setCursor(0,2);
        lcd.print("ROLE3 - 00:00:00");
      } else {
        int sa3 = kalansure3 / 3600000;
        int da3 = (kalansure3 - (sa3 * 3600000)) / 60000;
        int sn3 = (kalansure3 - (sa3 * 3600000) - (da3 * 60000)) / 1000;

        String ssa3 = sa3 > 10 ? String(sa3) : "0" + String(sa3);
        String sda3 = da3 > 10 ? String(da3) : "0" + String(da3);
        String ssn3 = sn3 > 10 ? String(sn3) : "0" + String(sn3);

        lcd.setCursor(0,2);
        lcd.print("ROLE3 - " + ssa3 + ":" + sda3 + ":" + ssn3);
      }


      if(kalansure4 == 0) {
        lcd.setCursor(0,3);
        lcd.print("ROLE4 - 00:00:00");
      } else {
        int sa4 = kalansure4 / 3600000;
        int da4 = (kalansure4 - (sa4 * 3600000)) / 60000;
        int sn4 = (kalansure4 - (sa4 * 3600000) - (da4 * 60000)) / 1000;

        String ssa4 = sa4 > 10 ? String(sa4) : "0" + String(sa4);
        String sda4 = da4 > 10 ? String(da4) : "0" + String(da4);
        String ssn4 = sn4 > 10 ? String(sn4) : "0" + String(sn4);

        lcd.setCursor(0,3);
        lcd.print("ROLE4 - " + ssa4 + ":" + sda4 + ":" + ssn4);
      }

      sonSaniyeGosterimi = millis();
    }
  }
}


void roleKontrol() {
  unsigned long simdi = millis();
  bool sarj_1_kapat = false;
  bool sarj_2_kapat = false;
  bool sarj_3_kapat = false;
  bool sarj_4_kapat = false;
  // sadece röle açıksa işlem yap!

  //1. röle
  if(role_1_Acikmi) {
    if(role_1_bitmeSuresi < simdi) {
      sarj_1_kapat = true; // en son hepsini kontrol edeceğiz ona göre şarjıkapatalımmi yi değiştireceğiz!
      digitalWrite(ledPin_1, LOW); // ledi kapat!
      digitalWrite(relayPin_1, LOW); // röleyi kapat!
      role_1_bitmeSuresi = 0; // sayacı 0 la ne olur ne olmaz!
      role_1_Acikmi = false;
    }
  } else {
    sarj_1_kapat = true;
  }


  if(role_2_Acikmi) {
    if(role_2_bitmeSuresi < simdi) {
      sarj_2_kapat = true; // en son hepsini kontrol edeceğiz ona göre şarjıkapatalımmi yi değiştireceğiz!
      digitalWrite(ledPin_2, LOW); // ledi kapat!
      digitalWrite(relayPin_2, LOW); // röleyi kapat!
      role_2_bitmeSuresi = 0; // sayacı 0 la ne olur ne olmaz!
      role_2_Acikmi = false;
    }
  } else {
    sarj_2_kapat = true;
  }


  if(role_3_Acikmi) {
    if(role_3_bitmeSuresi < simdi) {
      sarj_3_kapat = true; // en son hepsini kontrol edeceğiz ona göre şarjıkapatalımmi yi değiştireceğiz!
      digitalWrite(ledPin_3, LOW); // ledi kapat!
      digitalWrite(relayPin_3, LOW); // röleyi kapat!
      role_3_bitmeSuresi = 0; // sayacı 0 la ne olur ne olmaz!
      role_3_Acikmi = false;
    }
  } else {
    sarj_3_kapat = true;
  }


  if(role_4_Acikmi) {
    if(role_4_bitmeSuresi < simdi) {
      sarj_4_kapat = true; // en son hepsini kontrol edeceğiz ona göre şarjıkapatalımmi yi değiştireceğiz!
      digitalWrite(ledPin_4, LOW); // ledi kapat!
      digitalWrite(relayPin_4, LOW); // röleyi kapat!
      role_4_bitmeSuresi = 0; // sayacı 0 la ne olur ne olmaz!
      role_4_Acikmi = false;
    }
  } else {
    sarj_4_kapat = true;
  }

  // tüm röleler kapanıyor mu?
  if(sarj_1_kapat == true && sarj_2_kapat == true && sarj_3_kapat == true && sarj_4_kapat == true) {
    sarjVarmi = false;
    // ekranı anamenüye alalım ne olur ne olmaz!
    ekranModu = 1;
    modGosterildimi = false;
    sonEkranDegisimi = millis() - ekranDonguSuresi - 1000; // her halükarda ekranın değişmesini sağlar!
  }
}

void roleCalistir(byte roleNo) {
  sarjVarmi = true;

  if(roleNo == 1) {
    if(role_1_Acikmi) {
      // röle zaten açıksa süre ekle!
      role_1_bitmeSuresi = role_1_bitmeSuresi + roleAcikKalmaSuresi;
    } else {
      // röle açık değilse bitme süresini ayarla. ve çalıştır!
      role_1_bitmeSuresi = millis() + roleAcikKalmaSuresi;
      // ledi aktifleştir!
      digitalWrite(ledPin_1, HIGH);
      // röleyi aç!
      digitalWrite(relayPin_1, HIGH);
      // rölenin açık olduğunu kaydet!
      role_1_Acikmi = true;
    }
  }

  if(roleNo == 2) {
    if(role_2_Acikmi) {
      // röle zaten açıksa süre ekle!
      role_2_bitmeSuresi = role_2_bitmeSuresi + roleAcikKalmaSuresi;
    } else {
      // röle açık değilse bitme süresini ayarla. ve çalıştır!
      role_2_bitmeSuresi = millis() + roleAcikKalmaSuresi;
      // ledi aktifleştir!
      digitalWrite(ledPin_2, HIGH);
      // röleyi aç!
      digitalWrite(relayPin_2, HIGH);
      // rölenin açık olduğunu kaydet!
      role_2_Acikmi = true;
    }
  }

  if(roleNo == 3) {
    if(role_3_Acikmi) {
      // röle zaten açıksa süre ekle!
      role_3_bitmeSuresi = role_3_bitmeSuresi + roleAcikKalmaSuresi;
    } else {
      // röle açık değilse bitme süresini ayarla. ve çalıştır!
      role_3_bitmeSuresi = millis() + roleAcikKalmaSuresi;
      // ledi aktifleştir!
      digitalWrite(ledPin_3, HIGH);
      // röleyi aç!
      digitalWrite(relayPin_3, HIGH);
      // rölenin açık olduğunu kaydet!
      role_3_Acikmi = true;
    }
  }

  if(roleNo == 4) {
    if(role_4_Acikmi) {
      // röle zaten açıksa süre ekle!
      role_4_bitmeSuresi = role_4_bitmeSuresi + roleAcikKalmaSuresi;
    } else {
      // röle açık değilse bitme süresini ayarla. ve çalıştır!
      role_4_bitmeSuresi = millis() + roleAcikKalmaSuresi;
      // ledi aktifleştir!
      digitalWrite(ledPin_4, HIGH);
      // röleyi aç!
      digitalWrite(relayPin_4, HIGH);
      // rölenin açık olduğunu kaydet!
      role_4_Acikmi = true;
    }
  }
  ekranModu = 1;
  modGosterildimi = false;
  sonEkranDegisimi = millis() - ekranDonguSuresi - 1000; // her halükarda ekranın değişmesini sağlar!
}

void buttonKontrol() {
  byte button_deger_1 = digitalRead(buttonPin_1);
  byte button_deger_2 = digitalRead(buttonPin_2);
  byte button_deger_3 = digitalRead(buttonPin_3);
  byte button_deger_4 = digitalRead(buttonPin_4);

  //delay(100);

  if(button_deger_1 == HIGH) {
    lira = lira - sarjdanDusulecekPara;
    roleCalistir(1);
    delay(100);
    return; // looptan burada çıkar ve loopun başına döner! böylelikle butonlara aynı anda basılsa bile ilk sıradaki çalışır.
  }

  if(button_deger_2 == HIGH) {
    lira = lira - sarjdanDusulecekPara;
    roleCalistir(2);
    delay(100);
    return;
  }

  if(button_deger_3 == HIGH) {
    lira = lira - sarjdanDusulecekPara;
    roleCalistir(3);
    delay(100);
    return;
  }

  if(button_deger_4 == HIGH) {
    lira = lira - sarjdanDusulecekPara;
    roleCalistir(4);
    delay(100);
    return;
  }
}
