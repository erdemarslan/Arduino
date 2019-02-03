// Okeyi Bekler
void waitOK() {
  devam = false;
  zaman = millis();
  while(!devam) {
    if(Serial1.available()) {
      _data = Serial1.readString();
      Serial.println(_data);
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
// interneti kontrol eder!
bool internetVarmi() {
  devam = false;
  Serial1.print(F("AT+SAPBR=2,1\r"));
  //delay(100);
  zaman = millis();
  while(!devam) {
    if(Serial1.available()) {
      _data = Serial1.readString();
      Serial.println(_data);

      if (_data.indexOf("ERR") != -1 || _data.indexOf("\"0.0.0.0\"") != -1) {
        internetDurum = false;
        return false;
      }
      else {
        ip = _data.substring(_data.indexOf(",\"")+2, _data.lastIndexOf("\""));
        internetDurum = true;
        return true;
      }
    }

    if(millis() - zaman > 10000) {
      Serial.println(F("OK donmedi, internetVarmi dan cikiliyor!"));
      devam = true;
    }
  }
}
// Operatörü okur!
void operatorAdi() {
  String isim = "BAGLANTI YOK!";
  Serial1.print(F("AT+CSPN?\r"));
  devam = false;
  zaman = millis();
  while(!devam) {
    _data = Serial1.readString();
    if(_data.indexOf("+CSPN:") != -1) {
      isim = _data.substring(_data.indexOf("\"") +1, _data.lastIndexOf("\","));
      devam = true;
    }

    if(millis() - zaman > 10000) {
      Serial.println(F("OK donmedi, waitOK dan cikiliyor!"));
      devam = true;
    }
  }
  
  operator_adi = isim;
}

bool mesajGonder(String numara, String mesaj) {
  Serial1.flush();
  delay(2000);
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

  if (((_data.indexOf("+CMGS:")) != -1)) {
    return true;
  }
  else {
    return false;
  }
}

bool Sensor_Degerlerini_Internete_Gonder() {
  zaman_SonHTTPIstek = millis();
  String url = "iot.robothane.net/sera.php?T=ERA17WQ8FCK78N1TR&S=";
  url += String(sicaklik);
  url += "&N=";
  url += String(nem);
  url +="&B=";
  url += String(basinc);
  url += "&ST=1&K=GSM&KID=";
  url += kaynakid;

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
}

