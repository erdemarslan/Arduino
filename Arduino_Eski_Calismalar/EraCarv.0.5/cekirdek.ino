// Arabayı ileriye götürür
void araba_ileri(int sure) {
  digitalWrite(solA, HIGH);
  digitalWrite(solB, LOW);
  digitalWrite(sagA, HIGH);
  digitalWrite(sagB, LOW);
  delay(sure);
}

// Arabayı geriye götürür
void araba_geri(int sure) {
  digitalWrite(solA, LOW);
  digitalWrite(solB, HIGH);
  digitalWrite(sagA, LOW);
  digitalWrite(sagB, HIGH);
  delay(sure);
}

// Arabayı sola götürür
void araba_sola(int sure) {
  digitalWrite(solA, LOW);
  digitalWrite(solB, HIGH);
  digitalWrite(sagA, HIGH);
  digitalWrite(sagB, LOW);
  delay(sure);
}

// Arabayı saga götürür
void araba_saga(int sure) {
  digitalWrite(solA, HIGH);
  digitalWrite(solB, LOW);
  digitalWrite(sagA, LOW);
  digitalWrite(sagB, HIGH);
  delay(sure);
}

// Arabayı durdurur
void araba_dur(int sure) {
  digitalWrite(solA, LOW);
  digitalWrite(solB, LOW);
  digitalWrite(sagA, LOW);
  digitalWrite(sagB, LOW);
  delay(sure);
}

// uzunluk_olc
// bu fonksiyon bize bir sayı geri döndürür!
// bu fonksiyon bir sayı alarak başlar. bu sayı servo motorun açısıdır!
int uzunluk_olc(int servo_acisi) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);

  motor.write(servo_acisi);
  delay(200);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  int zaman = pulseIn(echoPin, HIGH);
  int mesafe = zaman / 2 / 29.1;
  return mesafe;
}

void engelden_kacan() {
    // Arabayı yönetmeye başlıyoruz......
  // Ön Mesafeyi oku
  int on_mesafe = uzunluk_olc(onAci);
  // on_mesafe 30 dan büyük mü?
  if(on_mesafe > 30 || on_mesafe < 6) {
    araba_ileri(250);
  }
  // on_mesafe 30 dan büyük değilmiş!
  else {
    // Arabayı durduralım
    araba_dur(100);
    // sol ve sağ mesafeleri ölç
    int sol_mesafe = uzunluk_olc(solAci);
    delay(100);
    int sag_mesafe = uzunluk_olc(sagAci);
    delay(100);
    araba_geri(200);
    
    if(sol_mesafe > sag_mesafe) {
      araba_sola(250);
      araba_dur(10);
    }
    else {
      araba_saga(250);
      araba_dur(10);
    }
    
  }
}


void bluetooth() {
  char veri;
  if(bt.available()) {
    veri = bt.read();
    Serial.write(veri);

    // 0-dur, 1- ileri, 2-sola, 3 -saga, 4-geri
    if(veri == 'w') {
      yon = 1;
    }
    if(veri == 'a') {
      yon = 2;
    }
    if(veri == 'd') {
      yon = 3;
    }
    if(veri == 's') {
      yon == 4;
    }
    if(veri == 'b') {
      yon = 0;
    }
  }
  delay(250);
  
  

  if(yon == 0) {
    araba_dur(100);
  }
  else if(yon == 1) {
    araba_ileri(100);
  }
  else if(yon == 2) {
    araba_sola(100);
  }
  else if(yon == 3) {
    araba_saga(100);
  }
  else if(yon == 4) {
    araba_geri(100);  
  }


  
}

