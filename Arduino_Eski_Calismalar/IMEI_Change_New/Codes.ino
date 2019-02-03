void waitFor(String correct, String wrong, int waitTime, boolean readIMEI) {
  _devam = false;
  _zaman = millis();

  islemSonuc = 0;

  while(!_devam) {
    if(sim.available()) {
      _data = sim.readString();

      
      if(_data.indexOf(correct) != -1) {

        if(readIMEI) {
          IMEI = _data.substring(8, _data.indexOf("OK"));
          IMEI.trim();
        }
        
        islemSonuc = 1;
        _devam = true;
      } else if(_data.indexOf(wrong) != -1) {
        islemSonuc = 2;
        _devam = true;
      } else {
        islemSonuc = 3;
        _devam = true;
      }
    }

    if(millis() - _zaman > waitTime && _devam == false) {
      _devam = true;
    }
  }
}

void ShowMenu(boolean addSpace) {
  if(addSpace) {
    Serial.println(F(""));
    Serial.println(F(""));
  }
  Serial.println(F("============================================="));
  Serial.println(F("show - Show current IMEI"));
  Serial.println(F("change - Change current IMEI"));
  Serial.println(F("reset - Reset IMEI to Default"));
  Serial.println(F("help - Show Menu"));
  delay(1000);
}


void ShowIMEI() {
  Serial.println(F("============================================="));
  Serial.println(F(""));
  Serial.println(F(""));
  Serial.println(F("Reading Module IMEI. Please wait..."));
  delay(500);
  sim.println(F("AT+CGSN"));
  waitFor("OK", "ERROR", 10000, true);

  Serial.print("Your IMEI: ");
  Serial.println(IMEI);

  delay(1000);
}



