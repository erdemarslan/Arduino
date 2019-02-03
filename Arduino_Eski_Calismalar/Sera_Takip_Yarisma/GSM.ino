// Okeyi Bekler
void waitOK() {
  devam = false;
  zaman = millis();
  while(!devam) {
    if(Serial1.available()) {
      _data = Serial1.readString();
      //Serial.println(_data);
      if(_data.indexOf("OK") != -1) {
        devam = true;
      }
    }

    if(millis() - zaman > 5000) {
      Serial.println(F("OK donmedi, waitOK dan cikiliyor!"));
      devam = true;
    }
  }
}

// IMEI numarasını okur ve kaynakID ye aktarır
void IMEI_Oku() {
  String imei = "###############";
  Serial1.print(F("AT+GSN\r"));
  devam = false;
  zaman = millis();
  while(!devam) {
    _data = Serial1.readString();
    if(_data.indexOf("OK") != -1) {
      imei = _data.substring(_data.indexOf("AT+GSN")+7, _data.indexOf("OK"));
      imei.trim();
      devam = true;
    }
  }

  if(millis() - zaman > 10000) {
    Serial.println(F("OK zamaninda donmedi, ciktik bizde!"));
    devam = true;
  }

  Serial.print("IMEI: ");
  Serial.println(imei);
  kaynakID = imei;
}

// Operatörü okur!
void Operator_Oku() {
  String isim = "BAGLANTI YOK!";
  Serial1.print(F("AT+COPS?\r"));
  devam = false;
  zaman = millis();
  while(!devam) {
    _data = Serial1.readString();
    //Serial.println(_data);
    if(_data.indexOf("+COPS:") != -1) {
      isim = _data.substring(_data.indexOf("\"") +1, _data.lastIndexOf("\""));
      devam = true;
    }

    if(millis() - zaman > 10000) {
      Serial.println(F("OK donmedi, waitOK dan cikiliyor!"));
      devam = true;
    }
  }

  Serial.print("Operator Okundu: ");
  Serial.println(isim);
  
  if(isim == "28601") {
    operator_adi = "TURKCELL";
  } else if(isim == "28602") {
    operator_adi = "VODAFONE TR";
  } else if(isim == "28603" || isim == "28604") {
    operator_adi = "TURK TELEKOM";
  } else {
    operator_adi = "BAGLANTI YOK!";
  }
  
  Serial.println(operator_adi);
  
}

// interneti kontrol eder!
bool Internet_Varmi() {
  devam = false;
  bool iv = false;
  Serial1.print(F("AT+SAPBR=2,1\r"));
  //delay(100);
  zaman = millis();
  while(!devam) {
    if(Serial1.available()) {
      _data = Serial1.readString();
      //Serial.println(_data);

      if (_data.indexOf("ERR") != -1 || _data.indexOf("\"0.0.0.0\"") != -1) {
        internetDurum = false;
        iv = false;
        break;
      }
      else {
        ip = _data.substring(_data.indexOf(",\"")+2, _data.lastIndexOf("\""));
        internetDurum = true;
        iv = true;
        break;
      }
    }

    if(millis() - zaman > 10000) {
      Serial.println(F("OK donmedi, internetVarmi dan cikiliyor!"));
      devam = true;
    }
  }

  Serial.print("Internet Kontrol Edildi: ");
  Serial.println(internetDurum);
  return iv;
}

// İnternete bağlan
void Internete_Baglan() {
  if(!internetDurum) {
    Serial1.print(F("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"\r"));
    waitOK();
    Serial1.print(F("AT+SAPBR=3,1,\"APN\",\"internet\"\r"));
    waitOK();

    Serial1.print(F("AT+SAPBR=1,1\r"));
    delay(100);
    waitOK();

    Serial1.print(F("AT+SAPBR=2,1\r"));

    zaman = millis();
    while(!devam) {
      if(Serial1.available()) {
        _data = Serial1.readString();

        if(_data.indexOf("OK") != -1 && _data.indexOf("0.0.0.0") == -1) {
          ip = _data.substring(_data.indexOf(",\"")+2, _data.lastIndexOf("\""));
          internetDurum = true;
          devam = true;
          Serial.println("Internete_Baglan() -> internet baglantisi basarili bir bicimde kuruldu.");
        }
      }

      if(millis() - zaman > 10000) {
        Serial.println(F("Internete_Baglan() -> Zamaninda OK degeri gelmedi. Muhtemelen internete baglanilamadi!"));
        devam = true;
      }
    }
  }
}

// Serialden gelen verileri kontrol et!
void Serial_Kontrol() {
  if(Serial1.available()) {
    _data = Serial1.readString();
    // Biraz sonra gelen mesajlara cevap buradan verilecek!
    if(_data.indexOf(F("+CMT:")) != -1) {
      // oo mesaj gelmiş hadi ayıklayalım!
      Mesaji_Oku(_data);
    }
    //Serial.println(_data);
  }
}

// Sensör değerlerini internete gönder!
void Sensor_Degerlerini_Internete_Gonder() {
  zaman_SonHTTPIstek = millis();
  String url = "sera.robothane.net/sera.php?T=ERA-BIHO-0001-TR&S=";
  url += String(sicaklik);
  url += "&N=";
  url += String(nem);
  url += "&US=";
  url += String(ustSicaklik);
  url += "&AS=";
  url += String(altSicaklik);
  url += "&D=";
  url += String(seraDurum);
  url += "&ST=1&K=GSM&KID=";
  url += kaynakID;

  Serial1.print(F("AT+HTTPTERM\r"));
  _data = Serial1.readString();

  Serial1.print(F("AT+HTTPINIT\r"));
  //delay(50);
  waitOK();
  Serial1.print(F("AT+HTTPPARA=\"CID\",1\r"));
  waitOK();

  Serial1.print(F("AT+HTTPPARA=\"URL\",\""));
  Serial1.print(url);
  Serial1.print("\"\r");
  waitOK();

  Serial1.print(F("AT+HTTPACTION=0\r"));
  waitOK();

  Serial1.print(F("AT+HTTPTERM\r"));
  _data = Serial1.readString();

  Serial.println("Sensor degerleri internete gonderildi!");
}

bool Mesaj_Gonder(String numara, String mesaj) {
  Ekran_Mesaj_Gonder(true);
  Serial1.flush();
  delay(1000);
  Serial1.print(F("AT+CMGS=\""));
  Serial1.print(numara);
  Serial1.print(F("\"\r"));
  delay(100);
  Serial1.print(mesaj);
  Serial1.print(F("\r"));
  //_data += Serial1.readString();
  Serial1.print((char)26);
  Serial1.print("\r");
  _data += Serial1.readString();

  Ekran_Mesaj_Gonder(false);
  if (((_data.indexOf("+CMGS:")) != -1)) {
    return true;
  }
  else {
    return false;
  }
}

void Mesaji_Oku(String veri) {
  String telno = veri.substring(veri.indexOf(F("\""))+1, veri.indexOf(F("\",\"")));
  Serial.print("Telefon No: ");
  Serial.println(telno);

  String msg = veri.substring(veri.lastIndexOf(F("\""))+1);
  Serial.print("Mesaj: ");
  msg.trim();
  Serial.println(msg);

  // Mesaj aç kapat!
  if(msg.indexOf(F("Mesaj ac")) != -1 || msg.indexOf(F("mesaj ac")) != -1 || msg.indexOf(F("MESAJ AC")) != -1) {
    mesajAlimi = true;
    Mesaj_Gonder(telno, "ONCEDEN BELIRLENEN NUMARAYA MESAJ GONDERIMI ACILDI.");
  }

  if(msg.indexOf(F("Mesaj kapat")) != -1 || msg.indexOf(F("mesaj kapat")) != -1 || msg.indexOf(F("MESAJ KAPAT")) != -1) {
    mesajAlimi = false;
    Mesaj_Gonder(telno, "ONCEDEN GONDERILEN NUMARAYA MESAJ GONDERIMI KAPATILDI.");
  }

  if(msg.indexOf(F("Mesaj durum")) != -1 || msg.indexOf(F("mesaj durum")) != -1 || msg.indexOf(F("MESAJ DURUM")) != -1) {
    if(mesajAlimi) {
      Mesaj_Gonder(telno, "MESAJ GONDERME ACIK");
    } else {
      Mesaj_Gonder(telno, "MESAJ GONDERME KAPALI");
    }
  }

  if(msg.indexOf(F("Ekran kapat")) != -1 || msg.indexOf(F("ekran kapat")) != -1 || msg.indexOf(F("EKRAN KAPAT")) != -1) {
    lcd.noBacklight();
    Mesaj_Gonder(telno, "EKRAN KAPATILDI");
  }

  if(msg.indexOf(F("Ekran ac")) != -1 || msg.indexOf(F("ekran ac")) != -1 || msg.indexOf(F("EKRAN AC")) != -1) {
    lcd.backlight();
    Mesaj_Gonder(telno, "EKRAN ACILDI");
  }

  if(msg.indexOf(F("Sicaklik alt #")) != -1 || msg.indexOf(F("sicaklik alt #")) != -1 || msg.indexOf(F("SICAKLIK ALT #")) != -1) {
    String ifade = msg.substring(msg.indexOf(F("#"))+1, msg.lastIndexOf(F("#")));
    float sicalt = ifade.toFloat();
    Serial.print("Gelen alt sicaklik degeri: ");
    Serial.println(sicalt);

    altSicaklik = sicalt;
    Mesaj_Gonder(telno, "YENI ALT SICAKLIK DEGERI BELIRLENDI");
  }

  if(msg.indexOf(F("Sicaklik ust #")) != -1 || msg.indexOf(F("sicaklik ust #")) != -1 || msg.indexOf(F("SICAKLIK UST #")) != -1) {
    String ifade2 = msg.substring(msg.indexOf(F("#"))+1, msg.lastIndexOf(F("#")));
    float sicust = ifade2.toFloat();
    Serial.print("Gelen ust sicaklik degeri: ");
    Serial.println(sicust);

    ustSicaklik = sicust;
    Mesaj_Gonder(telno, "YENI UST SICAKLIK DEGERI BELIRLENDI");
  }

  if(msg.indexOf(F("Sicaklik degerler")) != -1 || msg.indexOf(F("sicaklik degerler")) != -1 || msg.indexOf(F("SICAKLIK DEGERLER")) != -1) {
    sprintf(mesaj, "UST SICAKLIK DEGERI: %d.%02d *C \nALT SICAKLIK DEGERI: %d.%02d *C",  (int)ustSicaklik, (int)(ustSicaklik*100)%100, (int)altSicaklik, (int)(altSicaklik*100)%100);
    Serial.print("Mesaj: ");
    Serial.println(mesaj);

    Mesaj_Gonder(telno, String(mesaj));
    memset(mesaj, 0, sizeof(mesaj));
  }

  if(msg.indexOf(F("Sera durum")) != -1 || msg.indexOf(F("sera durum")) != -1 || msg.indexOf(F("SERA DURUM")) != -1) {
    Sensor_Oku();
    sprintf(mesaj, "SU ANDA SERANIN DURUMU \nSICAKLIK: %d.%02d *C \nNEM: %%%d.%02d",  (int)sicaklik, (int)(sicaklik*100)%100, (int)nem, (int)(nem*100)%100);
    Serial.print("Mesaj: ");
    Serial.println(mesaj);

    Mesaj_Gonder(telno, String(mesaj));
    memset(mesaj, 0, sizeof(mesaj));
  }


  if(msg.indexOf(F("Telefon ayarla #")) != -1 || msg.indexOf(F("telefon ayarla #")) != -1 || msg.indexOf(F("TELEFON AYARLA #")) != -1) {
    String ifade3 = msg.substring(msg.indexOf(F("#"))+1, msg.lastIndexOf(F("#")));
    Serial.print("Gelen Telefon Degeri: ");
    Serial.println(ifade3);

    TelNo = ifade3;
    Mesaj_Gonder(telno, "VARSAYILAN TELEFON NUMARASI DEGISTIRILDI");
  }

  if(msg.indexOf(F("Telefon sorgula")) != -1 || msg.indexOf(F("telefon sorgula")) != -1 || msg.indexOf(F("TELEFON SORGULA")) != -1) {
    
    Mesaj_Gonder(telno, "KAYITLI TELEFON NUMARASI: " + TelNo);
  }

  if(msg.indexOf(F("Ayar sifirla")) != -1 || msg.indexOf(F("ayar sifirla")) != -1 || msg.indexOf(F("AYAR SIFIRLA")) != -1) {
    ustSicaklik = 35.00;
    altSicaklik = 0.00;
    mesajAlimi = true;
    lcd.backlight();
    
    Mesaj_Gonder(telno, "AYARLAR SIFIRLANDI");
    memset(mesaj, 0, sizeof(mesaj));
  }

  
  
}

