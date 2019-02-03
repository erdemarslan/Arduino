void Sensor_Oku() {
  sensor.readSensor();

  Sicaklik = sensor.getTemperature_C();
  Nem = sensor.getHumidity();
  Basinc = sensor.getPressure_MB();

  Son_Sensor_Okuma = millis();

  Sensor_Durum_Kontrol();
}

void Sensor_Durum_Kontrol() {
  // Sıcaklık yüksekse!
  if(Sicaklik > Sicaklik_Ust_Limit) {
    Log(F("Sıcaklik degeri olması gerekenden fazla!"));
    Log(F("Olculen deger:"));
    Log(String(Sicaklik));

    if(Mesaj_Gonderimi) {
      sprintf(Mesaj, "SICAKLIK: %d.%02d *C \nISTENILEN: %d.%02d \nDURUM: YUKSEK",  (int)Sicaklik, (int)(Sicaklik*100)%100, (int)Sicaklik_Ust_Limit, (int)(Sicaklik_Ust_Limit*100)%100);
      Log(F("Mesaj:"));
      Log(String(Mesaj));
  
      Mesaj_Gonder(TelNo, String(Mesaj));
  
      memset(Mesaj, 0, sizeof(Mesaj));
    }
  }

  // Sıcaklık Düşükse!
  if(Sicaklik < Sicaklik_Alt_Limit) {
    Log(F("Sıcaklik degeri olması gerekenden az!"));
    Log(F("Olculen deger:"));
    Log(String(Sicaklik));

    if(Mesaj_Gonderimi) {
      sprintf(Mesaj, "SICAKLIK: %d.%02d *C \nISTENILEN: %d.%02d \nDURUM: DUSUK",  (int)Sicaklik, (int)(Sicaklik*100)%100, (int)Sicaklik_Alt_Limit, (int)(Sicaklik_Alt_Limit*100)%100);
      Log(F("Mesaj:"));
      Log(String(Mesaj));
  
      Mesaj_Gonder(TelNo, String(Mesaj));
  
      memset(Mesaj, 0, sizeof(Mesaj));
    }
  }
}

