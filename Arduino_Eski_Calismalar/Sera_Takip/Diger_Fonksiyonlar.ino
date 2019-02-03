// sensor bilgilerini okur
void Sensor_Oku() {
  //Sensor.readSensor();
  sicaklik = Sensor.temp();
  nem = Sensor.hum();
  basinc = Sensor.pres();
  zaman_SonSensorOkuma = millis();

  Sensor_Kontrol();
}

void Sensor_Kontrol() {
  if(sicaklik > 25.00) {
    // Sıcaklık değeri sınırı aşmış mesaj gönder!
    
    sprintf(mesaj, "SICAKLIK: %d.%02d *C \nNEM: %%%d.%02d",  (int)sicaklik, (int)(sicaklik*100)%100, (int)nem, (int)(nem*100)%100);
    //snprintf(mesaj, sizeof mesaj, );

    Serial.print("Mesaj: ");
    Serial.println(mesaj);

    mesajGonder(TelNo, String(mesaj));

    memset(mesaj, 0, sizeof(mesaj));
  }

  if(sicaklik < altSicaklik) {
    // Sıcaklık değeri sınırı aşmış mesaj gönder!
    String mesaj = "ORTAM SICAKLIGI ISTENILEN DEGERIN ALTINA INDI. SICAKLIK DEGERI: ";
    mesaj.concat(sicaklik);
    
    mesajGonder(TelNo, mesaj);
  }
}

