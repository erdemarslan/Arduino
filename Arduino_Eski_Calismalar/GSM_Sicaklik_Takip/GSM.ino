// Verilen at komutunu çalıştırır!
int bekle(String istenilen, String hatali, int bekleme) {

  _devam = false;
  _zaman = millis();
  int sonuc = 0;
  while(!_devam) {
    if(gsm.available()) {
      _data = gsm.readString();
      Log(_data);
      if(_data.indexOf(istenilen) != -1) {
        sonuc = 1;
        _devam = true;
      } else if(_data.indexOf(hatali) != -1) {
        sonuc = 2;
        _devam = true;
      } else {
        sonuc = 3;
        _devam = true;
      }
    }

    if(millis() - _zaman > bekleme && _devam == false) {
      Log(F("AT Komutunu bekleme suresi asildi!"));
      _devam = true;
    }
  }

  return sonuc;
}

// Mesaj Gönder
bool Mesaj_Gonder(String numara, String mesaj) {
  gsm.flush();
  delay(2000);
  _sonuc = 0;
  gsm.print(F("AT+CMGS=\""));
  gsm.print(numara);
  gsm.println("\"");
  bekle(F(">"), F("ERROR"), 5000);
  gsm.println(mesaj);
  gsm.println((char)26);

  _sonuc = bekle(F("+CMGS:"), F("ERROR"), 5000);
  
  if(_sonuc == 1) {
    return true;
  } else {
    return false;
  }
}

// Operatör adını oku!
void Operator_Oku() {
  Operator = "BAGLANTI YOK";
  _devam = false;
  _zaman = millis();
  gsm.println(F("AT+CSPN?"));

  while(!_devam) {
    _data = gsm.readString();
    Log(_data);

    if(_data.indexOf(F("+CSPN:")) != -1) {
      Operator = _data.substring(_data.indexOf(F("\"")) +1, _data.lastIndexOf(F("\",")));
      _devam = true;
    }

    if(millis() - _zaman > 10000) {
      Log(F("Operatoru okumak icin zaman doldu!"));
      _devam = true;
    }
  }

  if(Operator == "") {
    Operator_Oku2();
  }
}

void Operator_Oku2() {
  Operator = "BAGLANTI YOK";
  _devam = false;
  _zaman = millis();
  gsm.println(F("AT+COPS?"));

  while(!_devam) {
    _data = gsm.readString();
    Log(_data);

    if(_data.indexOf(F("+COPS:")) != -1) {
      Operator = _data.substring(_data.indexOf(F(",\"")) +2, _data.lastIndexOf(F("\"")));
      _devam = true;
    }

    if(millis() - _zaman > 10000) {
      Log(F("Operatoru okumak icin zaman doldu 2!"));
      _devam = true;
    }
  }
}

// Sinyal Kalitesini verir
void Sinyal_Kalitesi() {
  Sinyal = 99;
  _devam = false;
  _zaman = millis();
  gsm.println(F("AT+CSQ"));
  while(!_devam) {
    _data = gsm.readString();
    Log(_data);

    if(_data.indexOf(F("+CSQ:")) != -1) {
      String snyl = _data.substring(_data.indexOf(F("+CSQ:")) +6, _data.indexOf(","));
      Sinyal = snyl.toInt();
      _devam = true;
    }

    if(millis() - _zaman > 10000) {
      Log(F("Sinyal kalitesini okumak icin zaman doldu!"));
      _devam = true;
    }
  }
}

// İnternete Bağlanır
void Internete_Baglan() {
  _sonuc = 0;
    
  gsm.println(F("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\""));
  bekle(F("OK"), F("ERROR"), 5000);

  gsm.println(F("AT+SAPBR=3,1,\"APN\",\"internet\""));
  bekle(F("OK"), F("ERROR"), 5000);

  gsm.println(F("AT+SAPBR=1,1"));
  delay(50);
  bekle(F("OK"), F("ERROR"), 10000);

  gsm.println(F("AT+SAPBR=2,1"));
  _sonuc = bekle(F("+SAPBR: 1,1,"), F("0.0.0.0"), 8000);

  if(_sonuc == 1) {
    Internet_Baglimi = true;
  } else {
    Internet_Baglimi = false;
  }
}

// Internete veri gönderir!
void Internete_Veri_Gonder() {
  
  Son_HTTP_Istek = millis();
  
  if(Internet_Baglimi) {
    Log(F("Veriler internete gonderiliyor..."));

    String url = "iot.robothane.net/sera.php?T=";
    url += API_TOKEN;
    url += "&S=";
    url += String(Sicaklik);
    url += "&N=";
    url += String(Nem);
    url +="&B=";
    url += String(Basinc);
    url += "&ST=1&K=GSM&KID=";
    url += API_ID;

    gsm.println(F("AT+HTTPTERM"));
    bekle(F("OK"), F("ERROR"), 5000);

    gsm.println("AT+HTTPINIT");
    bekle(F("OK"), F("ERROR"), 5000);

    gsm.println(F("AT+HTTPPARA=\"CID\",1"));
    bekle(F("OK"), F("ERROR"), 5000);

    gsm.print(F("AT+HTTPPARA=\"URL\",\""));
    gsm.print(url);
    gsm.println(F("\""));
    bekle(F("OK"), F("ERROR"), 5000);

    gsm.println(F("AT+HTTPACTION=0"));
    bekle(F("OK"), F("ERROR"), 5000);

    delay(100);
    _sonuc = 0;
    _sonuc = bekle(F(",200,"), F("ERROR"), 20000);

    if(_sonuc == 1) {
      Log(F("Veri basariyla gonderildi!"));
    } else {
      Log(F("Veri basariyla gonderilemedi!"));
    }

    gsm.println(F("AT+HTTPTERM"));
    bekle(F("OK"), F("ERROR"), 5000);
  } else {
    Log(F("Internet baglantisi olmadigindan, veri gonderilmedi!"));
  }
}

// Mesaj Okur ve gereğini yapar!
void Mesaj_Oku() {

  _devam = false;
  _zaman = millis();
  int sonuc = 0;
  while(!_devam) {
    if(gsm.available()) {
      _data = gsm.readString();
      Log(_data);
      
      if(_data.indexOf(F("SENSOR OKU")) != -1) {
        sensor.readSensor();
        Sicaklik = sensor.getTemperature_C();
        Nem = sensor.getHumidity();
        Basinc = sensor.getPressure_MB();

        sprintf(Mesaj, "SICAKLIK: %d.%02d *C \nNEM: %%%d.%02d",  (int)Sicaklik, (int)(Sicaklik*100)%100, (int)Nem, (int)(Nem*100)%100);
        Log(F("Mesaj:"));
        Log(String(Mesaj));
    
        Mesaj_Gonder(TelNo, String(Mesaj));
    
        memset(Mesaj, 0, sizeof(Mesaj));
      }

      if(_data.indexOf(F("INTERNET KAPAT")) != -1) {
        Internet_Aktifmi = false;
        gsm.println(F("AT+SAPBR=0,1"));
        bekle(F("OK"), F("ERROR"), 5000);
        Internet_Baglimi = false;
        Son_Ekran_Guncelleme -= 500000;

        Mesaj_Gonder(TelNo, F("INTERNET KAPATILDI"));
      }

      if(_data.indexOf(F("INTERNET AC")) != -1) {
        Internet_Aktifmi = true;
        Internete_Baglan();
        Son_Ekran_Guncelleme -= 500000;

        Mesaj_Gonder(TelNo, F("INTERNET ACILDI"));
      }

      if(_data.indexOf(F("MESAJ AC")) != -1) {
        Mesaj_Gonderimi = true;
        
        Son_Ekran_Guncelleme -= 500000;
        
        Mesaj_Gonder(TelNo, F("MESAJ GONDERIMI ACILDI"));
      }

      if(_data.indexOf(F("MESAJ KAPAT")) != -1) {
        Mesaj_Gonderimi = true;
        
        Son_Ekran_Guncelleme -= 500000;
        
        Mesaj_Gonder(TelNo, F("MESAJ GONDERIMI KAPATILDI"));
      }

      if(_data.indexOf(F("MESAJ SIL")) != -1) {

        gsm.println(F("AT+CMGDA=\"DEL ALL\""));
        bekle(F("OK"), F("ERROR"), 30000);
        
        Son_Ekran_Guncelleme -= 500000;
        
        Mesaj_Gonder(TelNo, F("TUM MESAJLAR SILINDI"));
      }
      /*
      if(_data.indexOf(F("SICAKLIK UST")) != -1) {
        String veri = _data.substring(_data.indexOf(F("UST")) + 4, _data.lastIndexOf(F("OK")));
        veri.trim();

        Sicaklik_Ust_Limit = veri.toFloat();

        sprintf(Mesaj, "YENI SICAKLIK UST LIMIT: %d.%02d *C",  (int)Sicaklik_Ust_Limit, (int)(Sicaklik_Ust_Limit*100)%100);
        Log(F("Mesaj:"));
        Log(String(Mesaj));
    
        Mesaj_Gonder(TelNo, String(Mesaj));
    
        memset(Mesaj, 0, sizeof(Mesaj));
      }

      if(_data.indexOf(F("SICAKLIK ALT")) != -1) {
        String veri = _data.substring(_data.indexOf(F("ALT")) + 4, _data.lastIndexOf(F("OK")));
        veri.trim();

        Sicaklik_Alt_Limit = veri.toFloat();

        sprintf(Mesaj, "YENI SICAKLIK ALT LIMIT: %d.%02d *C",  (int)Sicaklik_Alt_Limit, (int)(Sicaklik_Alt_Limit*100)%100);
        Log(F("Mesaj:"));
        Log(String(Mesaj));
    
        Mesaj_Gonder(TelNo, String(Mesaj));
    
        memset(Mesaj, 0, sizeof(Mesaj));
      }

      if(_data.indexOf(F("SICAKLIK DUZELT")) != -1) {
        String veri = _data.substring(_data.indexOf(F("DUZELT")) + 4, _data.lastIndexOf(F("OK")));
        veri.trim();

        Sensor_Kalibre_Degeri = veri.toFloat();
        sensor.setTempCal(Sensor_Kalibre_Degeri);

        sprintf(Mesaj, "YENI SICAKLIK DUZELTME DEGERI: %d.%02d *C",  (int)Sensor_Kalibre_Degeri, (int)(Sensor_Kalibre_Degeri*100)%100);
        Log(F("Mesaj:"));
        Log(String(Mesaj));
    
        Mesaj_Gonder(TelNo, String(Mesaj));
    
        memset(Mesaj, 0, sizeof(Mesaj));
      }
      */

      if(_data.indexOf(F("CIHAZ RESET")) != -1) {
        digitalWrite(GSM_RESET_PIN, LOW);
        delay(3000);
        softReset();
      }


      if(_data.indexOf(F("BAKIYE SORGULA")) != -1) {

        if(Operator.indexOf(F("TURKCELL")) != -1) {
          gsm.println("AT+CUSD=1,\"*100#\"");
        } else {
          gsm.println("AT+CUSD=1,\"*123#\"");
        }
        bekle(F("OK"), F("ERROR"), 5000);
      }

      
      _devam = true;
    }

    if(millis() - _zaman > 20000 && _devam == false) {
      Log(F("Mesaj Okuma bekleme suresi asildi!"));
      _devam = true;
    }
  }
}
