// Ekran aydınlatmayı açar ve kapatır
void Ekran_Aydinlatma(bool aktif) {
  if(aktif) {
    lcd.backlight();
  } else {
    lcd.noBacklight();
  }
}
// Ekrana Başlangıç aşamasında bilgi bas
void Ekran_Baslangic_Bilgi_Yaz(String satir1, String satir2, int bekle) {
  Ekran_Baslangic_Temizle();
  delay(200);
  lcd.setCursor(0,0);
  lcd.print(satir1);
  lcd.setCursor(0,1);
  lcd.print(satir2);

  delay(bekle);
}
void Ekran_Baslangic_Temizle() {
  lcd.setCursor(0,0);
  lcd.print(F("                "));
  lcd.setCursor(0,1);
  lcd.print(F("                "));
}

void Ekran_Goster(int durum) {
  lcd.setCursor(14,0);
  lcd.print(" ");
  lcd.setCursor(14,0);
  lcd.write(4);
  lcd.setCursor(14,1);
  lcd.print(" ");
  lcd.setCursor(14,1);
  lcd.write(4);

  
  if(internetDurum) {
    lcd.setCursor(15,0);
    lcd.print(" ");
    lcd.setCursor(15,0);
    lcd.print("G");
  } else {
    lcd.setCursor(15,0);
    lcd.print(" ");
    lcd.setCursor(15,0);
    lcd.print("X");
  }

  lcd.setCursor(15,1);
  lcd.print(" ");
  lcd.setCursor(15,1);
  lcd.write(2);

  lcd.setCursor(0,0);
  lcd.print("              ");
  lcd.setCursor(0,0);
  lcd.print(operator_adi);

  
  if(durum == 0) {
    lcd.setCursor(0,1);
    lcd.print("              ");
    lcd.setCursor(0,1);
    lcd.print(ip);
  }

  if(durum == 2) {
    lcd.setCursor(0,1);
    lcd.print("              ");
    lcd.setCursor(0,1);
    lcd.print(sicaklik);
    lcd.setCursor(7,1);
    lcd.write((uint8_t)0);
  }

  if(durum == 3) {
    lcd.setCursor(0,1);
    lcd.print("              ");
    lcd.setCursor(0,1);
    lcd.print("%");
    lcd.setCursor(1,1);
    lcd.print(nem);
  }

  if(durum == 4) {
    lcd.setCursor(0,1);
    lcd.print("              ");
    lcd.setCursor(0,1);
    lcd.print(basinc);
    lcd.setCursor(8,1);
    lcd.print("mPa");
  }

  zaman_SonEkranGuncelleme = millis();
}

