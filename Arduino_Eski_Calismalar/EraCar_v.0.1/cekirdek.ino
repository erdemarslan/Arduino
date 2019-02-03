// Switch değerlerini okuyarak arabanın modunu belirler
void mod_belirle() {
  int s1 = digitalRead(0);
  int s2 = digitalRead(1);
  // Mod 0 - Araba Kapalı
  if(s1 == LOW && s2 == LOW) {
    mod = 0;
  }
  // Mod 1 - Engelden Kaçan
  if(s1 == HIGH && s2 == LOW) {
    mod = 1;
  }
  // Mod 2 - Bluetooth
  if(s1 == HIGH && s2 == HIGH) {
    mod = 2;
  }
  // Mod 3 - Çizgi İzleyen
  if(s1 == LOW && s2 == HIGH) {
    mod = 3;
  }
}

// Arabayı İleri Götürür
void araba_ileri(int sure) {
  digitalWrite(solA, HIGH);
  digitalWrite(solB, LOW);
  digitalWrite(sagA, HIGH);
  digitalWrite(sagB, LOW);
  led_cakar();
  delay(sure);
}

// Arabayı Geri Götürür
void araba_geri(int sure) {
  digitalWrite(solA, LOW);
  digitalWrite(solB, HIGH);
  digitalWrite(sagA, LOW);
  digitalWrite(sagB, HIGH);
  led_cakar();
  delay(sure);
}

// Arabayı sola Döndürür
void araba_sola(int sure) {
  digitalWrite(solA, LOW);
  digitalWrite(solB, HIGH);
  digitalWrite(sagA, HIGH);
  digitalWrite(sagB, LOW);
  led_cakar();
  delay(sure);
}

// Arabayı sağa döndürür
void araba_saga(int sure) {
  digitalWrite(solA, HIGH);
  digitalWrite(solB, LOW);
  digitalWrite(sagA, LOW);
  digitalWrite(sagB, HIGH);
  led_cakar();
  delay(sure);
}

// arabayı durdurur
void araba_dur(int sure) {
  digitalWrite(solA, LOW);
  digitalWrite(solB, LOW);
  digitalWrite(sagA, LOW);
  digitalWrite(sagB, LOW);
  delay(sure);
}

// Engele olan uzaklığı ölçer!
int uzaklik_olc(int servoaci) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  motor.write(servoaci);
  delay(200);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  int sure = pulseIn(echoPin, HIGH);
  int mesafe = (sure / 2) / 29.1;
  return mesafe;
}

// LED i Polis Çakarına Döndürür!
void led_cakar() {

  for(int k = 0; k < 3; k++) {

    for(int i=0; i<4; i++) {
      led.setPixelColor(i, led.Color(255,0,0));
      led.show();
    }
  
    delay(50);
  
    for(int i=0; i<4; i++) {
      led.setPixelColor(i, led.Color(0,0,0));
      led.show();
    }
  
    delay(50);
  }


  for(int k = 0; k < 3; k++) {

    for(int i=4; i<8; i++) {
      led.setPixelColor(i, led.Color(0,0,255));
      led.show();
    }
  
    delay(50);
  
    for(int i=4; i<8; i++) {
      led.setPixelColor(i, led.Color(0,0,0));
      led.show();
    }
  
    delay(50);
  }
}

void yon_belirle(int yon) {
  arabaYon = yon;
  if(arabaYon != arabaEskiYon) {
    arabaEskiYon = arabaYon;
  }
}


