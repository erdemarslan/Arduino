// sensor bilgilerini okur
void Sensor_Oku() {
  nem = Sensor.readHumidity();
  sicaklik = Sensor.readTemperature();
  float basinc;
  Serial.print("Sicaklik: ");
  Serial.println(sicaklik);
  Serial.print("Nem: ");
  Serial.println(nem);
  zaman_SonSensorOkuma = millis();
  Ekran_Sensor_Degeri_Yaz();
  Sensor_Kontrol();
}

void Sensor_Kontrol() {
  String durum = "Hersey Normal";
  seraDurum = 0;
  if(sicaklik >= ustSicaklik) {
  //if(sicaklik > 25.00) {
    // aşırı sıcak!
    durum = "Ortam Sicak";
    seraDurum = 1;
    if(mesajAlimi) {
      sprintf(mesaj, "SICAKLIK DEGERI UST LIMITI ASTI! SICAKLIK: %d.%02d *C \nNEM: %%%d.%02d",  (int)sicaklik, (int)(sicaklik*100)%100, (int)nem, (int)(nem*100)%100);

      Serial.print("Mesaj: ");
      Serial.println(mesaj);

      Mesaj_Gonder(TelNo, String(mesaj));
      memset(mesaj, 0, sizeof(mesaj));
    }
  }

  if(sicaklik <= altSicaklik) {
  //if(sicaklik <= 30.00) {
    // aşırı soğuk
    durum = "Ortam Soguk";
    seraDurum = 2;
    if(mesajAlimi) {
      sprintf(mesaj, "SICAKLIK DEGERI ISTENILEN DEGERIN ALTINA DUSTU! SICAKLIK: %d.%02d *C \nNEM: %%%d.%02d",  (int)sicaklik, (int)(sicaklik*100)%100, (int)nem, (int)(nem*100)%100);

      Serial.print("Mesaj: ");
      Serial.println(mesaj);

      Mesaj_Gonder(TelNo, String(mesaj));
      memset(mesaj, 0, sizeof(mesaj));
    }
  }

  if(sonSicaklikDurumu != durum) {
    Ekran_Sicaklik_Durum(durum);
    sonSicaklikDurumu = durum;
  }
}

