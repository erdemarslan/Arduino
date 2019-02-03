// Ekran aydınlatmayı açar ve kapatır
void Ekran_Aydinlatma(bool aktif) {
  if(aktif) {
    lcd.backlight();
  } else {
    lcd.noBacklight();
  }
}

// Ekrana Başlangıç aşamasında bilgi bas
void Ekran_Baslangic_Bilgi_Yaz(String satir1, String satir2, String satir3, String satir4, int bekle) {

  lcd.setCursor(0,0);
  lcd.print("                    ");
  lcd.setCursor(0,0);
  lcd.print(satir1);

  lcd.setCursor(0,1);
  lcd.print("                    ");
  lcd.setCursor(0,1);
  lcd.print(satir2);


  lcd.setCursor(0,2);
  lcd.print("                    ");
  lcd.setCursor(0,2);
  lcd.print(satir3);


  lcd.setCursor(0,3);
  lcd.print("                    ");
  lcd.setCursor(0,3);
  lcd.print(satir4);

  delay(bekle);
}

// Yan Ekranı gösterir
void Ekran_Yan() {
  if(operator_adi == "BAGLANTI YOK!") {
    lcd.setCursor(19,0);
    lcd.write((uint8_t)3);
  } else {
    lcd.setCursor(19,0);
    lcd.write((uint8_t)2);
  }
  
  
  lcd.setCursor(19,1);
  if(internetDurum) {
    lcd.write((uint8_t)6);
  } else {
    lcd.write((uint8_t)3);
  }
}

// Sensörden gelen değerleri yerine yazar!
void Ekran_Sensor_Degeri_Yaz() {
  lcd.setCursor(11,1);
  lcd.print("       ");
  lcd.setCursor(12,1);
  lcd.print(sicaklik);

  lcd.setCursor(7,2);
  lcd.print("          ");
  lcd.setCursor(8,2);
  lcd.print(nem);
}

void Ekran_Operator_Guncelle() {
  lcd.setCursor(0,0);
  lcd.print("                  ");
  lcd.setCursor(0,0);
  lcd.print(operator_adi);
}

void Ekran_Gonderim(bool goster) {
  lcd.setCursor(19,3);
  if(goster) {
    lcd.write((uint8_t)5);
  } else {
    lcd.print(" ");
  }
}

void Ekran_Mesaj_Gonder(bool goster) {
  lcd.setCursor(19,2);
  if(goster) {
    lcd.write((uint8_t)1);
  } else {
    lcd.print(" ");
  }
}

void Ekran_Sicaklik_Durum(String ifade) {
  lcd.setCursor(0,3);
  lcd.print("                  ");
  lcd.setCursor(0,3);
  lcd.print(ifade);
}



