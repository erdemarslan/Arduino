/*
 * EraBot Maze v.1.3
 * Yukarıdaki kart için hazırlanmıştır!
 * Biga İmam Hatip Ortaokulu
 * Tübitak 4006 Projesi
 */

// Pin Tanımlamaları
// Motorlar
#define M1A 7
#define M1B 8
#define M2A 9
#define M2B 10
#define M1E 3
#define M2E 5
#define HIZ_NORMAL 170
#define HIZ_YAVAS 75
#define HIZ_HIZLI 225

// Çizgi İzleme Sensörleri
#define S1 A0
#define S2 A1
#define S3 A2
#define S4 A3
#define S5 A4
#define S6 A5
#define ATLAMASURESI 200

// BUZZER
#define BUZZER 11
// Led
#define LED_Y 12
#define LED_K 13

char yol[30] = {};
int yolUzunlugu = 0;
int okumaUzunlugu = 0;
int tekrarDurumu = 0;

unsigned int sol_dis, sol_ic, orta_sol, orta_sag, sag_ic, sag_dis;


void setup() {
  // Açılış kodları burası
  // Serial monitörü aç!
  //Serial.begin(9600);
  //Serial.println("BULMACA COZEN ROBOT");
  //Serial.println("KART VERSIYON - 1.2");
  //Serial.println("BIGA IMAM HATIP ORTAOKULU");
  //Serial.println("TUBITAK 4006 SERGISI - 2018");
  //Serial.println("***********************************");
  //Serial.println();
  //delay(250);
  
  // Ledi tanımla!
  pinMode(LED_K, OUTPUT);
  pinMode(LED_Y, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  //Serial.println("LEDLER TANIMLANDI...");
  //Serial.println("***********************************");
  //Serial.println();
  delay(250);

  // Ayarlamaların yapıldığına dair yeşil ledi yakalım!
  Led(LED_K, HIGH);

  // Sensörler
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);
  pinMode(S6, INPUT);
  //Serial.println("SENSORLER TANIMLANDI...");
  //Serial.println("***********************************");
  //Serial.println();
  delay(250);

  // Motorlar
  pinMode(M1E, OUTPUT);
  pinMode(M2E, OUTPUT);
  pinMode(M1A, OUTPUT);
  pinMode(M1B, OUTPUT);
  pinMode(M2A, OUTPUT);
  pinMode(M2B, OUTPUT);
  //Serial.println("MOTORLAR TANIMLANDI...");
  //Serial.println("***********************************");
  //Serial.println();
  delay(250);

  // Hız ayarı yapalım!
  Hiz_Degistir(M1E, HIZ_NORMAL);
  Hiz_Degistir(M2E, HIZ_NORMAL);
  //Serial.println("MOTOR HIZLARI AYARLANDI...");
  //Serial.println("***********************************");
  //Serial.println();
  //delay(250);

  //Serial.println("SISTEM BASLIYOR...");
  //Serial.println("***********************************");
  //Serial.println();
  delay(500);
  
  Led(LED_K, LOW);
  delay(100);
  Led(LED_Y, HIGH);
}

// Ledi yakıp, kapatır. Kolaylık olsun diye eklendi!
void Led(unsigned int led, unsigned int durum) {
  digitalWrite(led, durum);
}

// Motor hızlarını değiştirir! Şekil olsun diye yapıldı!
void Hiz_Degistir(unsigned int motor, unsigned int hiz) {
  analogWrite(motor, hiz);
}

void Sensor_Oku() {
  sol_dis = digitalRead(S6);
  sol_ic = digitalRead(S5);
  orta_sol = digitalRead(S4);
  orta_sag = digitalRead(S3);
  sag_ic = digitalRead(S2);
  sag_dis = digitalRead(S1);
  //Serial.println("SENSORLER OKUNDU");
  //Serial.print(sol_dis);
  //Serial.print(" - ");
  //Serial.print(sol_ic);
  //Serial.print(" - ");
  //Serial.print(orta_sol);
  //Serial.print(" - ");
  //Serial.print(orta_sag);
  //Serial.print(" - ");
  //Serial.print(sag_ic);
  //Serial.print(" - ");
  //Serial.println(sag_dis);
}

// Siyah - 1
// Beyaz - 0

void loop() {
  // Kodlar buraya!
  Sensor_Oku();

  if(sol_dis == 0 && sag_dis == 0 && (orta_sol == 1 || orta_sag == 1) ){ 
    //Serial.println("ileriliyorum...");
    Duz_Git();
  } else {
    //Serial.println("Sol elim duvarda...");
    Sol_Elim_Duvarda();
  }
}

/**/
void Sol_Elim_Duvarda() {

  // Her iki kenar da siyah görüyorsa!
  if(sol_dis == 1 && sag_dis == 1) {
    // 1 adım daha git! Eğer hala siyahsa, tamamdır oyun bitti! Yok değilse o zaman sola dön!
    digitalWrite(M1A, HIGH);
    digitalWrite(M1B, LOW);
    digitalWrite(M2A, HIGH);
    digitalWrite(M2B, LOW);
    delay(ATLAMASURESI);

    Sensor_Oku();

    if(sol_dis == 1 || sag_dis == 1) {
      //Serial.println("Bulmaca tamamlandı!");
      Tamamlandi();
    }

    // İki tarafta beyaz o zaman sola dön!
    if(sol_dis == 0 && sag_dis == 0) {
      //Serial.println("Sola dönüyoruz!");
      Sola_Don();
    }
  }

  // Eğer sola dönebiliyorsan dön!
  if(sol_dis == 1) {
    digitalWrite(M1A, HIGH);
    digitalWrite(M1B, LOW);
    digitalWrite(M2A, HIGH);
    digitalWrite(M2B, LOW);
    delay(ATLAMASURESI);

    Sensor_Oku();
    if(sol_dis == 0 && sag_dis == 0) {
      //Serial.println("Sola Donuyoruz!");
      Sola_Don();
    } else {
      //Serial.println("Bulmaca Tamamlandi!");
      Tamamlandi();
    }
    
  }

  // Sağ tarafa dönelim mi?
  if(sag_dis == 1) {
    digitalWrite(M1A, HIGH);
    digitalWrite(M1B, LOW);
    digitalWrite(M2A, HIGH);
    digitalWrite(M2B, LOW);
    delay(30);
    Sensor_Oku();

    if(sol_dis == 1) {
      delay(ATLAMASURESI-30);
      Sensor_Oku();

      if(sag_dis == 1 && sol_dis == 1) {
        //Serial.println("Bulmaca tamamlandi.");
        Tamamlandi();
      } else {
        //Serial.println("Sola donuyoruz...");
        Sola_Don();
        return;
      }
    }

    delay(ATLAMASURESI-30);
    Sensor_Oku();
    if(sol_dis == 0 && sol_ic == 0 && sag_ic == 0 && sag_dis == 0) {
      //Serial.println("Saga donuyoruz...");
      Saga_Don();
      return;
    }

    yol[yolUzunlugu] = 'S';
    yolUzunlugu++;
    if(yol[yolUzunlugu-2] == 'B') {
      //Serial.println("Kisa yol");
      Kisa_Yol();
    }
    //Serial.println("Duz gidiyoruz...");
    Duz_Git();
  }

  Sensor_Oku();
  if(sol_dis == 0 && sol_ic == 0 && orta_sol == 0 && orta_sag == 0 && sag_ic == 0 && sag_dis == 0) {
    //Serial.println("Geri donuyorum...");
    Geri_Don();
  }
  
}

// Yol Tamamlandığında Çalışacak Kodlar
void Tamamlandi() {
  digitalWrite(M1A, LOW);
  digitalWrite(M1B, LOW);
  digitalWrite(M2A, LOW);
  digitalWrite(M2B, LOW);

  tekrarDurumu = 1;
  yol[yolUzunlugu] = 'D';
  yolUzunlugu++;

  Led(LED_Y, LOW);
  delay(100);

  // sol dış sensör tekrar beyazı görene kadar led yak!
  while(digitalRead(S6) == 1) {
    Led(BUZZER, LOW);
    delay(150);
    Led(BUZZER, HIGH);
    delay(150);
  }

  delay(500);
  Tekrar_Oynat();
}

// Sola Dönüldüğünde çalışacak kodlar
void Sola_Don() {
  // Adam gibi sola dönelim!
  while(digitalRead(S3) == 1 || digitalRead(S4) == 1) {
    digitalWrite(M1A, LOW);
    digitalWrite(M1B, HIGH);
    digitalWrite(M2A, HIGH);
    digitalWrite(M2B, LOW);
    delay(2);
    digitalWrite(M1A, LOW);
    digitalWrite(M1B, LOW);
    digitalWrite(M2A, LOW);
    digitalWrite(M2B, LOW);
    delay(1);
  }

  while(digitalRead(S3) == 0) {
    digitalWrite(M1A, LOW);
    digitalWrite(M1B, HIGH);
    digitalWrite(M2A, HIGH);
    digitalWrite(M2B, LOW);
    delay(2);
    digitalWrite(M1A, LOW);
    digitalWrite(M1B, LOW);
    digitalWrite(M2A, LOW);
    digitalWrite(M2B, LOW);
    delay(1);
  }

  if(tekrarDurumu == 0){
    yol[yolUzunlugu] = 'L';
    yolUzunlugu++;
    if(yol[yolUzunlugu] == 'B') {
      Kisa_Yol();
    }
  }
}

// Sağa dönülünce çalışacak kodlar
void Saga_Don() {
  // Sağa dönelim!
  while(digitalRead(S3) == 1) {
    digitalWrite(M1A, HIGH);
    digitalWrite(M1B, LOW);
    digitalWrite(M2A, LOW);
    digitalWrite(M2B, HIGH);
    delay(2);
    digitalWrite(M1A, LOW);
    digitalWrite(M1B, LOW);
    digitalWrite(M2A, LOW);
    digitalWrite(M2B, LOW);
    delay(1);
  }

  while(digitalRead(S3) == 0) {
    digitalWrite(M1A, HIGH);
    digitalWrite(M1B, LOW);
    digitalWrite(M2A, LOW);
    digitalWrite(M2B, HIGH);
    delay(2);
    digitalWrite(M1A, LOW);
    digitalWrite(M1B, LOW);
    digitalWrite(M2A, LOW);
    digitalWrite(M2B, LOW);
    delay(1);
  }

  while(digitalRead(S4) == 0) {
    digitalWrite(M1A, HIGH);
    digitalWrite(M1B, LOW);
    digitalWrite(M2A, LOW);
    digitalWrite(M2B, HIGH);
    delay(2);
    digitalWrite(M1A, LOW);
    digitalWrite(M1B, LOW);
    digitalWrite(M2A, LOW);
    digitalWrite(M2B, LOW);
    delay(1);
  }

  if(tekrarDurumu == 0) {
    yol[yolUzunlugu] = 'R';
    yolUzunlugu++;

    if(yol[yolUzunlugu-2] == 'B') {
      Kisa_Yol();
    }
  }
  
}

// Düz gider!
void Duz_Git() {
  if(digitalRead(S4) == 0) {
    digitalWrite(M1A, HIGH);
    digitalWrite(M1B, LOW);
    digitalWrite(M2A, HIGH);
    digitalWrite(M2B, LOW);
    delay(1);
    digitalWrite(M1A, HIGH);
    digitalWrite(M1B, LOW);
    digitalWrite(M2A, LOW);
    digitalWrite(M2B, LOW);
    delay(5);
    return;
  }

  if(digitalRead(S3) == 0) {
    digitalWrite(M1A, HIGH);
    digitalWrite(M1B, LOW);
    digitalWrite(M2A, HIGH);
    digitalWrite(M2B, LOW);
    delay(1);
    digitalWrite(M1A, LOW);
    digitalWrite(M1B, LOW);
    digitalWrite(M2A, HIGH);
    digitalWrite(M2B, LOW);
    delay(5);
    return;
  }

  digitalWrite(M1A, HIGH);
  digitalWrite(M1B, LOW);
  digitalWrite(M2A, HIGH);
  digitalWrite(M2B, LOW);
  delay(4);
  digitalWrite(M1A, LOW);
  digitalWrite(M1B, LOW);
  digitalWrite(M2A, LOW);
  digitalWrite(M2B, LOW);
  delay(1);
}

// Geri dönüyoruz!
void Geri_Don() {
  // biraz ileri git! araba boyu kadar olabilir!
  digitalWrite(M1A, HIGH);
  digitalWrite(M1B, LOW);
  digitalWrite(M2A, HIGH);
  digitalWrite(M2B, LOW);
  delay(150);

  // artık yolu bul bakalım!
  while(digitalRead(S4) == 0) {
    digitalWrite(M1A, LOW);
    digitalWrite(M1B, HIGH);
    digitalWrite(M2A, HIGH);
    digitalWrite(M2B, LOW);
    delay(2);
    digitalWrite(M1A, LOW);
    digitalWrite(M1B, LOW);
    digitalWrite(M2A, HIGH);
    digitalWrite(M2B, LOW);
    delay(1);
  }

  yol[yolUzunlugu] = 'B';
  yolUzunlugu++;

  Duz_Git();
}

// Kısa yolu gider!
void Kisa_Yol() {
  int kisaTamam = 0;

  if(yol[yolUzunlugu-3] == 'L' && yol[yolUzunlugu-1] == 'R') {
    yolUzunlugu-=3;
    yol[yolUzunlugu] = 'B';
    kisaTamam = 1;
  }

  if(yol[yolUzunlugu-3] == 'L' && yol[yolUzunlugu-1] == 'S' && kisaTamam == 0) {
    yolUzunlugu-=3;
    yol[yolUzunlugu] = 'R';
    kisaTamam = 1;
  }

  if(yol[yolUzunlugu-3] == 'R' && yol[yolUzunlugu-1] == 'L' && kisaTamam == 0) {
    yolUzunlugu-=3;
    yol[yolUzunlugu] = 'B';
    kisaTamam = 1;
  }

  if(yol[yolUzunlugu-3] == 'S' && yol[yolUzunlugu-1] == 'L' && kisaTamam == 0) {
    yolUzunlugu-=3;
    yol[yolUzunlugu] = 'R';
    kisaTamam = 1;
  }

  if(yol[yolUzunlugu-3] == 'S' && yol[yolUzunlugu-1] == 'S' && kisaTamam == 0) {
    yolUzunlugu-=3;
    yol[yolUzunlugu] = 'B';
    kisaTamam = 1;
  }

  if(yol[yolUzunlugu-3] == 'L' && yol[yolUzunlugu-1] == 'L' && kisaTamam == 0) {
    yolUzunlugu-=3;
    yol[yolUzunlugu] = 'S';
    kisaTamam = 1;
  }

  yol[yolUzunlugu+1] = 'D';
  yol[yolUzunlugu+2] = 'D';
  yolUzunlugu++;
}

// Aracı tekrar oynat!
void Tekrar_Oynat() {
  Sensor_Oku();

  if(sol_dis == 0 && sag_dis == 0) {
    Duz_Git();
  } else {
    if(yol[okumaUzunlugu] == 'D') {
      digitalWrite(M1A, HIGH);
      digitalWrite(M1B, LOW);
      digitalWrite(M2A, HIGH);
      digitalWrite(M2B, LOW);
      delay(100);
      digitalWrite(M1A, LOW);
      digitalWrite(M1B, LOW);
      digitalWrite(M2A, LOW);
      digitalWrite(M2B, LOW);
      Bitir();
    }

    if(yol[okumaUzunlugu] == 'L') {
      digitalWrite(M1A, HIGH);
      digitalWrite(M1B, LOW);
      digitalWrite(M2A, HIGH);
      digitalWrite(M2B, LOW);
      delay(ATLAMASURESI);
      Sola_Don();
    }

    if(yol[okumaUzunlugu] == 'R') {
      digitalWrite(M1A, HIGH);
      digitalWrite(M1B, LOW);
      digitalWrite(M2A, HIGH);
      digitalWrite(M2B, LOW);
      delay(ATLAMASURESI);
      Saga_Don();
    }

    if(yol[okumaUzunlugu] == 'S') {
      digitalWrite(M1A, HIGH);
      digitalWrite(M1B, LOW);
      digitalWrite(M2A, HIGH);
      digitalWrite(M2B, LOW);
      delay(ATLAMASURESI);
      Duz_Git();
    }

    okumaUzunlugu++;
  }

  Tekrar_Oynat();
}

// Oyunu bitirir!
void Bitir() {
  Led(LED_K, HIGH);
  delay(100);
  Led(LED_K,LOW);
  delay(50);

  Led(LED_Y, HIGH);
  delay(100);
  Led(LED_Y,LOW);
  delay(50);

  Led(BUZZER, HIGH);
  delay(100);
  Led(BUZZER,LOW);
  delay(100);

  Bitir();
}






















