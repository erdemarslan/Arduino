#include <SoftwareSerial.h>


#define ssid "cekemeyen anten taktirsin =)"
#define sifre "erdem61638489"

boolean devam = false;
long zaman;
String _data;

SoftwareSerial wifi(4,5);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  
  Serial.begin(9600);
  wifi.begin(9600);

  wifi.println(F("AT"));
  waitOK();

  wifi.println(F("ATE1"));
  waitOK();

  wifi.println(F("AT+CWMODE=1"));
  waitOK();

  String cmd = "AT+CWJAP=\"";
  cmd += ssid;
  cmd += "\",\"";
  cmd += sifre;
  cmd += "\"";

  wifi.println(cmd);
  waitOK();

  delay(1000);
  
  wifi.println(F("AT+CIPMUX=1"));
  waitOK();

  wifi.println(F("AT+CIPSERVER=1,80"));
  waitOK();

  wifi.println(F("AT+CIPSTA_CUR?"));
  waitOK();
  
}


void loop() {
  if(wifi.available()) {
    _data = wifi.readString();

    Serial.println(_data);
    if(_data.indexOf(F("+IPD")) != -1) {

      Led(_data);
      
      String metin = "<head>Ledimi yakiyorum, dalgama bakiyorum =)</head>";
      metin += "<br><a href=\"?pin=on\"><button type='button'>Acik</button></a>"; 
      metin += "<br><a href=\"?pin=off\"><button type='button'>Kapali</button></a>";      
      String cipsend = "AT+CIPSEND=";
      cipsend += "0,";
      cipsend += String(metin.length());

      wifi.println(cipsend);
      delay(500);
      wifi.println(metin);
      waitOK();

      wifi.println("AT+CIPCLOSE=0");
      waitOK();
    }
  }

  if(Serial.available()) {
    wifi.write(Serial.read());
  }
}

void Led(String data) {
  if(data.indexOf(F(":GET /?pin=on")) != -1) {
    Serial.println("LED Yandi");
    digitalWrite(LED_BUILTIN,HIGH);
  }

  if(data.indexOf(F(":GET /?pin=off")) != -1) {
    Serial.println("LED Sondu");
    digitalWrite(LED_BUILTIN,LOW);
  }
}

 // Okeyi Bekler
void waitOK() {
  devam = false;
  zaman = millis();
  while(!devam) {
    if(wifi.available()) {
      _data = wifi.readString();
      Serial.println(_data);
      if(_data.indexOf("OK") != -1) {
        devam = true;
      }
    }

    if(millis() - zaman > 10000) {
      Serial.println(F("OK donmedi, waitOK dan cikiliyor!"));
      devam = true;
    }
  }
}
