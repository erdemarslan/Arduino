// Ekranı Başlatır!
void Ekran_Baslat() {
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, santigrad);
  lcd.createChar(1, okey);
  lcd.createChar(2, hata);
  lcd.createChar(3, sinir);
  lcd.createChar(4, sinyal);

  Ekran_Aydinlatma(true);
  Son_Ekran_Guncelleme = millis();
}

// Ekran Aydınlatmayı açar kapatır
void Ekran_Aydinlatma(bool durum) {
  if(durum) {
    lcd.backlight();
  } else {
    lcd.noBacklight();
  }
}

// Ekrana Başlangıç aşamasında bilgi bas
void Ekran_Baslangic_Yaz(String satir1, String satir2, int bekle) {
  lcd.clear();
  delay(200);
  lcd.setCursor(0,0);
  lcd.print(satir1);
  lcd.setCursor(0,1);
  lcd.print(satir2);

  delay(bekle);
}


void Ekran_Goster(int durum) {
  // Sınır Çizgisini Çekelim!
  lcd.setCursor(14,0);
  lcd.print(F(" "));
  lcd.setCursor(14,0);
  lcd.write(3);
  lcd.setCursor(14,1);
  lcd.print(F(" "));
  lcd.setCursor(14,1);
  lcd.write(3);

  lcd.setCursor(15,0);
  lcd.print(F(" "));
  lcd.setCursor(15,0);
  if(Internet_Baglimi) {
    lcd.print(F("G"));
  } else {
    lcd.print(F("X"));
  }
  
  lcd.setCursor(0,0);
  lcd.print(F("              "));
  lcd.setCursor(0,0);
  lcd.print(Operator);

  lcd.setCursor(0,1);
  lcd.print(F("              "));
    
  if(durum == 0) {
    lcd.setCursor(0,1);

    if(Sinyal < 32) {
      int val = map(Sinyal, 0,31,0,13);
      for(int i = 0; i < val; i++) {
        lcd.setCursor(i,1);
        lcd.write((uint8_t)4);
      }
    }
  }

  if(durum == 1) {
    lcd.setCursor(0,1);
    lcd.print(Sicaklik);
    lcd.setCursor((String(Sicaklik)).length()+1, 1);
    lcd.write((uint8_t)0);
  }

  if(durum == 2) {
    lcd.setCursor(0,1);
    lcd.print(F("%"));
    lcd.setCursor(1,1);
    lcd.print(Nem);
  }

  if(durum == 3) {
    lcd.setCursor(0,1);
    lcd.print(Basinc);
    lcd.setCursor((String(Basinc)).length()+1, 1);
    lcd.print(F("mPa"));
  }

  Son_Ekran_Guncelleme = millis();
}

void Ekran_Islem(bool calisma) {
  
  lcd.setCursor(15,1);
  lcd.print(F(" "));
  lcd.setCursor(15,1);
  if(calisma) {
    lcd.write(2);
  } else {
    lcd.write(1);
  }
}

