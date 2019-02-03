#include <Wire.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <BME280I2C.h>
#include <Wire.h>

// GSM Modülü Tanımlama

// Sıcaklık Nem ve Basınç Sensörünü Tanımlama
BME280I2C Sensor;

// LCD Ekranı Tanımlama
LiquidCrystal_I2C lcd(0x3F, 20, 4);

bool internet, devam, mesajVar, internetDurum;
float ustSicaklik, altSicaklik, tempSicaklik, sicaklik, nem, basinc;
int mesajNo, gosterilenEkran;
String _data, ip, operator_adi;
unsigned long zaman_SonSensorOkuma, zaman_SonEkranGuncelleme, zaman_SonHTTPIstek, zaman_SonIslem, zaman;
char mesaj[160];

const String TelNo PROGMEM = "+905321130193";

String kaynakid = "asda1";

byte santigrad[8] = {
  0b01000,
  0b10100,
  0b01000,
  0b00011,
  0b00100,
  0b00100,
  0b00011,
  0b00000
};
byte okey[8] = {
  0b00000,
  0b00000,
  0b00001,
  0b00010,
  0b10100,
  0b01000,
  0b00000,
  0b00000
};
byte hata[8] = {
  0b00000,
  0b10001,
  0b01010,
  0b00100,
  0b01010,
  0b10001,
  0b00000,
  0b00000
};
byte sinir[8] = {
  0b00001,
  0b00001,
  0b00001,
  0b00001,
  0b00001,
  0b00001,
  0b00001,
  0b00001
};
void setup() {
  _data.reserve(500);
  devam = false;
  mesajVar = false;
  mesajNo = 0;
  internet = true;
  internetDurum = false;
  gosterilenEkran = 0;
  
  Serial.begin(9600);
  Serial.println(F("ERA SERA v.0.1"));
  
  // Ekranı Başlat!
  
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, santigrad);
  lcd.createChar(2, okey);
  lcd.createChar(3, hata);
  lcd.createChar(4, sinir);
  
  Ekran_Aydinlatma(true);
  
  // Sonra belki logo eklenebilir
  Ekran_Baslangic_Bilgi_Yaz("Sistem", "Baslatiliyor", 1000);
  Serial.println(F("Sistem Basliyor..."));
  
  /**/
  // Ayarlar aliniyor!
  Ekran_Baslangic_Bilgi_Yaz("Ayarlar", "Aliniyor", 1000);
  ustSicaklik = 50.00;
  altSicaklik = 0.00;

  // Sıcaklık Nem Basınç Sensörü başlatılıyor!
  Ekran_Baslangic_Bilgi_Yaz("Sensor", "Baslatiliyor", 1000);
  Sensor.begin();
  Serial.println(F("Sensor basladi..."));

  // Sensor ayarlanıyor
  Ekran_Baslangic_Bilgi_Yaz("Sensor", "Ayarlaniyor", 1000);
  //Sensor.setTempCal(tempSicaklik);
  Serial.println(F("Sensor ayarlandi..."));
  
  // GSM aliniyor!
  Ekran_Baslangic_Bilgi_Yaz("GSM Modulu", "Baslatiliyor", 1000);
  Serial1.begin(57600);
  Serial.println(F("GSM Basladi..."));
  // GSM Ayarları yapılıyor!
  Ekran_Baslangic_Bilgi_Yaz("GSM Ayarlari", "Yapiliyor", 1000);
  Serial1.print(F("AT+CFUN=1\r"));
  waitOK();
  Serial1.print(F("AT+CMGF=1\r"));
  waitOK();
  Serial1.print(F("AT+CREG=1\r"));
  waitOK();

  //exit(0);

  // GSM Operatöre bağlanılıyor!
  Ekran_Baslangic_Bilgi_Yaz("Operatore", "Baglaniliyor", 1000);
  Serial.println(F("Operatore baglaniliyor..."));
  Serial1.print("AT+CREG?\r");
  //delay(100);
  while(!devam) {
    if(Serial1.available()) {
      _data = Serial1.readString();

      Serial.println(_data);

      if(_data.indexOf("+CREG: 1") != -1 || _data.indexOf("+CREG: 5") != -1) {
        devam = true;
      }
      Ekran_Baslangic_Bilgi_Yaz("Operatore", "Baglaniliyor", 1000);
    }
  }

  Serial1.flush();
  delay(2000);

  devam = false;

  internetDurum = false;

  if(internet && !internetDurum) {
    Serial.println(F("Internete baglaniliyor..."));
    Ekran_Baslangic_Bilgi_Yaz("Internete", "Baglaniliyor", 1000);
    
    Serial1.print(F("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"\r"));
    waitOK();
    Serial1.print(F("AT+SAPBR=3,1,\"APN\",\"internet\"\r"));
    waitOK();

    Serial1.print(F("AT+SAPBR=1,1\r"));
    delay(100);
    waitOK();

    Serial1.print(F("AT+SAPBR=2,1\r"));
    //delay(100);

    zaman = millis();
    while(!devam) {
      if(Serial1.available()) {
        _data = Serial1.readString();

        if(_data.indexOf("OK") != -1 && _data.indexOf("0.0.0.0") == -1) {
          ip = _data.substring(_data.indexOf(",\"")+2, _data.lastIndexOf("\""));
          //ip.trim();

          internetDurum = true;

          devam = true;
        }
      }

      if(millis() - zaman > 10000) {
        Serial.println(F("OK donmedi, waitOK dan cikiliyor!"));
        devam = true;
      }
    }
  }

  
  // Sensör Okunuyor
  Ekran_Baslangic_Bilgi_Yaz("Sensorler", "Okunuyor", 1000);
  Sensor_Oku();
  Serial.println(F("Sensor okundu..."));
  Serial.print("Sicaklik: ");
  Serial.println(sicaklik);
  Serial.print("Nem: ");
  Serial.println(nem);
  Serial.print("Basinc: ");
  Serial.println(basinc);

  // Operatörü oku
  operatorAdi();
  Serial.println(F("Operator okundu..."));
  Serial.println(operator_adi);
  
  Ekran_Baslangic_Temizle();
  Serial.println(F("Loop a giriliyor..."));

  zaman_SonIslem = millis() - 32000;
  zaman_SonHTTPIstek = millis() - 62000;
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(Serial1.available()) {
    _data = Serial1.readString();
    // Gelen bir mesaj ise ona göre işlem yap!
    // Mesaj gelince index numarasını al ve oku de!
    Serial.println(_data);
  }

  // 1 dakikada bir yapılacaklar
  if(millis() > zaman_SonIslem + 30000) {
    operatorAdi();
    zaman_SonIslem = millis();
    Serial.println("Operator adi kontrol edildi!");
    internetDurum = internetVarmi();
    Serial.println("Internet kontrol edildi!");
  }

  // 2 Dakikada bir sensörü oku!
  if(millis() > zaman_SonSensorOkuma + 60000) {
    Sensor_Oku();
    Serial.println("Sensor okundu");
    Serial.print("Sicaklik: ");
    Serial.println(sicaklik);
    Serial.print("Nem: ");
    Serial.println(nem);
    Serial.print("Basinc: ");
    Serial.println(basinc);
  }

  // 5 dakikada bir verileri internete gönder!
  if(millis() > zaman_SonHTTPIstek + 300000) {
    //internetDurum = internetVarmi();
    Sensor_Degerlerini_Internete_Gonder();
    Serial.println("Internete veri gitti!");
  }
  
  if(millis() > zaman_SonEkranGuncelleme + 15000) {
    gosterilenEkran++;

    int ekran = gosterilenEkran % 5;
    
    Ekran_Goster(ekran);
    Serial.println("Ekran gosterildi!");

    if(gosterilenEkran > 999) {
      gosterilenEkran = 0;
    }
  }
}

