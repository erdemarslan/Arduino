/*
 * Biga İmam Hatip Ortaaokulu
 * Çan Truva Robot Yarışması
 * 
 * Sera Takip Projesi
 * 
 * Öğrenciler:
 *  İsmail Eray Karaman
 *  Musa Soner
 *  
 * Danışman Öğretmen:
 *  Erdem Arslan
 * 
 * 
 * BAĞLANTI ŞEMASI
 * 
 * LCD EKRAN - ARDUINO
 * GND - GND
 * VCC - 5V
 * SDA - SDA
 * SCL - SCL
 * 
 * BME280 SICAKLIK NEM SENSORU - ARDUINO
 * VCC - 3.3V
 * GND - GND
 * SDA - SDA
 * SCL - SCL
 * 
 * GSM MODULU - ARDUINO
 * VCC - 5V
 * GND - GND
 * RX - SERIAL1_TX
 * TX - SERIAL1_RX
 *  
 */

#include <Wire.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTTYPE DHT22

// Sıcaklık Nem ve Basınç Sensörünü Tanımlama
DHT Sensor(7, DHTTYPE);
// LCD Ekranı Tanımlama
LiquidCrystal_I2C lcd(0x3F, 20, 4);


bool internet, devam, internetDurum, mesajAlimi;
float ustSicaklik, altSicaklik, sicaklik, nem;
byte seraDurum;
String _data, ip, operator_adi, kaynakID, sonSicaklikDurumu;
unsigned long zaman_SonSensorOkuma, zaman_SonEkranGuncelleme, zaman_SonHTTPIstek, zaman_SonIslem, zaman;
char mesaj[160];

String TelNo = "+905060271774";

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
byte veri[8] = {
  0b00100,
  0b01110,
  0b11111,
  0b00100,
  0b00100,
  0b11111,
  0b01110,
  0b00100
};
byte bagla[8] = {
  0b00000,
  0b11111,
  0b01111,
  0b00111,
  0b00011,
  0b00001,
  0b00001,
  0b00001
};
byte mesajicon[8] = {
  0b00000,
  0b00000,
  0b11111,
  0b11111,
  0b10101,
  0b10001,
  0b11111,
  0b00000
};
void setup() {
  // Başlangıç kodları
  _data.reserve(512);
  devam = false;
  mesajAlimi = true;
  internet = true;
  internetDurum = false;
  sonSicaklikDurumu = "Hersey Normal";
  seraDurum = 0;
  

  Serial.begin(9600);
  Serial.println("BIGA IMAM HATIP ORTAOKULU");
  Serial.println("OGRENCILER: ISMAIL ERAY KARAMAN - MUSA SONER");
  Serial.println("DANISMAN OGRETMEN: ERDEM ARSLAN");
  Serial.println("SERA TAKIP PROJESI");

  // Ekranı başlat
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, santigrad);
  lcd.createChar(1, mesajicon);
  lcd.createChar(2, okey);
  lcd.createChar(3, hata);
  lcd.createChar(4, sinir);
  lcd.createChar(5, veri);
  lcd.createChar(6, bagla);
  
  Ekran_Aydinlatma(true);

  // Sonra belki logo eklenebilir
  Ekran_Baslangic_Bilgi_Yaz("", "", "", "Sistem Baslatiliyor", 1000);
  Serial.println(F("Sistem Basliyor..."));

  // Ayarlar alınıyor!
  Ekran_Baslangic_Bilgi_Yaz("", "", "Sistem Baslatiliyor", "Ayarlar Aliniyor", 1000);
  ustSicaklik = 50.00;
  altSicaklik = 0.00;
  Serial.println(F("Ayarlar alindi..."));

  // Sensor Başlatılıyor
  Ekran_Baslangic_Bilgi_Yaz("", "Sistem Baslatiliyor", "Ayarlar Aliniyor", "Sensor Baslatiliyor", 1000);
  Sensor.begin();
  Serial.println(F("Sensor baslatildi..."));

  Ekran_Baslangic_Bilgi_Yaz("Sistem Baslatiliyor", "Ayarlar Aliniyor", "Sensor Baslatiliyor", "GSM Baslatiliyor", 1000);
  Serial1.begin(57600);
  Serial.println(F("GSM Baslatildi!"));

  Ekran_Baslangic_Bilgi_Yaz("Ayarlar Aliniyor", "Sensor Baslatiliyor", "GSM Baslatiliyor", "GSM Ayarlaniyor", 1000);
  Serial1.print(F("AT+CFUN=1\r")); // Tam fonksiyonda çalışma
  waitOK();
  Serial1.print(F("AT+CMGF=1\r")); // Mesajlar text modunda gelsin
  waitOK();
  Serial1.print(F("AT+CREG=1\r")); // Operatöre bağlan
  waitOK();
  Serial1.print("AT+COPS=0,2\r"); // Numerik operatör ismi dönsün
  waitOK();
  
  IMEI_Oku();
  Serial.println(F("GSM Ayarlandi!"));

  
  Ekran_Baslangic_Bilgi_Yaz("Sensor Baslatiliyor", "GSM Baslatiliyor", "GSM Ayarlaniyor", "Operatore Baglaniyor", 1000);
  Serial.println(F("Operatore baglaniliyor..."));
  Serial1.print("AT+CREG?\r");
  while(!devam) {
    if(Serial1.available()) {
      _data = Serial1.readString();

      Serial.println(_data);

      if(_data.indexOf("+CREG: 1") != -1 || _data.indexOf("+CREG: 5") != -1) {
        devam = true;
      }
      //Ekran_Baslangic_Bilgi_Yaz("Operatore", "Baglaniliyor", 1000);
    }
  }
  //Serial1.flush();
  //delay(2000);

  devam = false;

  Ekran_Baslangic_Bilgi_Yaz("GSM Baslatiliyor", "GSM Ayarlaniyor", "Operatore Baglaniyor", "Operator Okunuyor", 1000);
  Operator_Oku();

  
  Ekran_Baslangic_Bilgi_Yaz("GSM Ayarlaniyor", "Operatore Baglaniyor", "Operator Okunuyor", "Internet K. Ediliyor", 1000);
  byte ic = 0;
  internetDurum = Internet_Varmi();

  if(internet && !internetDurum) {
    Serial.println(F("Internete baglaniliyor..."));
    Ekran_Baslangic_Bilgi_Yaz("Operatore Baglaniyor", "Operator Okunuyor", "Internet K. Ediliyor", "Internete Baglaniyor", 1000);
    ic = 1;
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

  internetDurum = Internet_Varmi();
  
  if(ic == 0) {
    Ekran_Baslangic_Bilgi_Yaz("Operatore Baglaniyor", "Operator Okunuyor", "Internet K. Ediliyor", "Sensor Okunuyor", 1000);
  } else {
    Ekran_Baslangic_Bilgi_Yaz("Operator Okunuyor", "Internet K. Ediliyor", "Internete Baglaniyor", "Sensor Okunuyor", 1000);
  }

  Sensor_Oku();
  
  Serial.println(F("Sensor okundu..."));
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print(operator_adi);
  
  lcd.setCursor(0,1);
  lcd.print("SICAKLIK(");
  lcd.write((uint8_t)0);
  lcd.print(") ");
  lcd.print(sicaklik);

  lcd.setCursor(0,2);
  lcd.print("NEM (%) ");
  lcd.print(nem);

  lcd.setCursor(0,3);
  lcd.print("Hersey Normal");

  lcd.setCursor(18,0);
  lcd.write((uint8_t)4);
  lcd.setCursor(18,1);
  lcd.write((uint8_t)4);
  lcd.setCursor(18,2);
  lcd.write((uint8_t)4);
  lcd.setCursor(18,3);
  lcd.write((uint8_t)4);

  Ekran_Yan();
  zaman_SonSensorOkuma = millis();
}

void loop() {
  // Sürekli dönen kodlarımız!
  Serial_Kontrol();
  Yarim_Dakikada_Kontrol();
  Dakikada_Kontrol();
  Bes_Dakikada_Kontrol();
}

void Yarim_Dakikada_Kontrol() {
  if(millis() > zaman_SonSensorOkuma + 30000) {
    Sensor_Oku(); 
  }
}

void Dakikada_Kontrol() {
  if(millis() > zaman_SonIslem + 60000) {
    Internet_Varmi();
    String sonOperatorAdi = operator_adi;
    Operator_Oku();
    if(sonOperatorAdi != operator_adi) {
      Ekran_Operator_Guncelle();
    }
    Ekran_Yan();
    zaman_SonIslem = millis();
  }
}

void Bes_Dakikada_Kontrol() {
  if(millis() > zaman_SonHTTPIstek + 300000) {
    Internet_Varmi();  
    Ekran_Gonderim(true);
    if(internetDurum) {
      Sensor_Degerlerini_Internete_Gonder();
    } else {
      Internete_Baglan();
      Sensor_Degerlerini_Internete_Gonder();
    }
    Ekran_Gonderim(false);
  }
}



