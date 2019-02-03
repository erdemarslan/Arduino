#include <Wire.h>
#include <BME280_I2C.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

// Sıcaklık Nem ve Basınç Sensörü - BME280 Bosch
BME280_I2C sensor;

// LCD Ekran
LiquidCrystal_I2C lcd(0x3F, 16,2);

// Gsm Modülü
SoftwareSerial gsm(7,8);

bool DEBUG = true;
int LED_OPERATOR = 4;
int LED_GPRS = 5;
int LED_ISLEM = 6;
int GSM_RESET_PIN = 9;


// Değişkenler
float Sicaklik, Nem, Basinc, Sicaklik_Ust_Limit, Sicaklik_Alt_Limit, Sensor_Kalibre_Degeri;
bool _devam, Internet_Aktifmi, Internet_Baglimi, Mesaj_Gonderimi;
int _sonuc, Mesaj_No, Gosterilen_Ekran, Sinyal;
char Mesaj[160];
String _data, Operator;
unsigned long Son_Sensor_Okuma, Son_Ekran_Guncelleme, Son_HTTP_Istek, Son_Islem, _zaman;

// Sabitler
const String TelNo PROGMEM = "+905321130193";
const String API_TOKEN PROGMEM = "ERA17WQ8FCK78N1TR";
const String API_ID PROGMEM = "351504008191195"; // Cihazın imei ve ya mac numarası yazılabilir! Önceden alınırsa programa ek yük bindirmez

// Grafikler
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
  0b00100,
  0b11110,
  0b10101,
  0b10001,
  0b10001,
  0b10101,
  0b01111,
  0b00100
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
byte sinyal[8] = {
  0b00000,
  0b01000,
  0b01100,
  0b01110,
  0b00111,
  0b01110,
  0b01100,
  0b01000
};

void (*softReset) (void) = 0;

void setup() {
  pinMode(LED_OPERATOR, OUTPUT);
  pinMode(LED_GPRS, OUTPUT);
  pinMode(LED_ISLEM, OUTPUT);
  pinMode(GSM_RESET_PIN, OUTPUT);

  // Reset pinlerini high a çekmek lazım!
  digitalWrite(GSM_RESET_PIN, HIGH);
  
  LED(LED_ISLEM, HIGH, 50);
  
  // Kodlar çalışmaya buradan başlar!
  _data.reserve(255);
  _devam = false;
  Internet_Aktifmi = true;
  Internet_Baglimi = false;
  Gosterilen_Ekran = 0;
  Sicaklik_Ust_Limit = 50.00;
  Sicaklik_Alt_Limit = -4.00;
  Sensor_Kalibre_Degeri = -2.00;
  Mesaj_Gonderimi = true;
  Sinyal = 0;
  _sonuc = 0;

  // DEBUG Varsa seriali aç!
  if(DEBUG) {
    Serial.begin(57600);
    Serial.println(F("ERA SERA v.0.2 BASLIYOR...."));
  }

  // Ekrani başlat
  Ekran_Baslat();
  Log("Ekran baslatildi!");

  // Bi bilgi at ekrana
  Ekran_Baslangic_Yaz(F("Sistem"), F("Baslatiliyor"), 1000);
  Log(F("Sistem basliyor..."));

  // Bilgi ver ve sensoru baslat!
  Ekran_Baslangic_Yaz(F("Sensor"), F("Basliyor"), 1000);
  Log(F("Sensor baslatiliyor..."));
  sensor.begin();

  // Sensor ayarlanıyor!
  Ekran_Baslangic_Yaz(F("Sensor"), F("Kal. Ediliyor"), 1000);
  Log(F("Sensor kalibre ediliyor!"));
  sensor.setTempCal(Sensor_Kalibre_Degeri);

  // Gsm Başlatiliyor
  Ekran_Baslangic_Yaz(F("GSM Modulu"), F("Baslatiliyor"), 1000);
  Log(F("Gsm baslatiliyor..."));
  gsm.begin(57600);


  // Gsm Ayarlaniyor
  Ekran_Baslangic_Yaz(F("GSM Modulu"), F("Ayarlaniyor"), 1000);
  Log(F("Gsm ayarlaniyor!..."));
  
  gsm.println(F("AT+CFUN=1"));
  bekle(F("OK"), F("ERROR"), 5000);
  
  gsm.println(F("AT+CMGF=1"));
  bekle(F("OK"), F("ERROR"), 5000);
  
  // Operatöre bağlanmayı dene! Bağlanılamaz ise, bağlanana kadar dön!
  _sonuc = 0;
  do {
    Ekran_Baslangic_Yaz(F("Operatore"), F("Baglaniyor"), 1000);
    Log(F("Operatore baglaniyor!..."));
    
    gsm.println(F("AT+CREG?"));
    _sonuc = bekle(F("+CREG: 0,1"), F("+CREG: 0,5"), 5000);

    delay(1000);
  } while(_sonuc < 1 || _sonuc > 2);  

  LED(LED_OPERATOR, HIGH, 50);

  // İnternet Bağlantısını kontrol et!
  Ekran_Baslangic_Yaz(F("Sinyal"), F("Olculuyor"), 1000);
  Log(F("Sinyal kalitesi olculuyor!..."));
  Sinyal_Kalitesi();


  // İnternet Bağlantısını kontrol et!
  Ekran_Baslangic_Yaz(F("Internet"), F("Kontrol Ediliyor"), 1000);
  Log(F("Internet Kontrol Ediliyor!..."));
  gsm.println(F("AT+SAPBR=2,1"));
  _sonuc = bekle(F("+SAPBR: 1,1,"), F("0.0.0.0"), 8000);

  if(_sonuc == 1) {
    Internet_Baglimi = true;
  } else {
    Internet_Baglimi = false;
  }

  delay(500);

  if(Internet_Aktifmi && !Internet_Baglimi) {
    // İnternete Bağlanmayı dene! Bağlanılamaz ise, bağlanana kadar dön bakalım
    Ekran_Baslangic_Yaz(F("Internete"), F("Baglaniyor"), 1000);
    Log(F("Internete baglaniyor!..."));

    Internete_Baglan();
  }

  // İnternet bağlı ise ledi yak!
  if(Internet_Baglimi) {
    LED(LED_GPRS, HIGH, 50);
  }


  // Sensör okunuyor!
  Ekran_Baslangic_Yaz(F("Sensor"), F("Okunuyor"), 1000);
  Log(F("Sensor okunuyor!"));
  Sensor_Oku();
  
  // Operator adi okunuyor!
  Ekran_Baslangic_Yaz(F("Son"), F("Kontroller"), 1000);
  Log(F("Operator adi okunup, son kontroller yapiliyor!"));
  Operator_Oku();

  Son_HTTP_Istek = millis();
  Son_Islem = millis();
  lcd.clear();
  
  LED(LED_ISLEM, LOW, 50);
  Ekran_Islem(false);
}

void loop() {
  // Tekrarlar burada!

  // GSM den Gelen birşey var mı?
  if(gsm.available()) {
    _data = gsm.readString();

    Log(_data);

    Islem(true);

    if(_data.indexOf(F("+CMTI:")) != -1) {
      //Mesaj_Varmi 
      Mesaj_No = (_data.substring(_data.indexOf(",")+1)).toInt();

      Log(F("Mesaj Geldi. Numarasi:"));
      Log(String(Mesaj_No));

      gsm.print(F("AT+CMGR="));
      gsm.println(Mesaj_No);
      
      Mesaj_Oku();

      Log(F("Mesaj Okundu!"));
    }

    if(_data.indexOf(F("+CUSD:")) != -1 && _data.indexOf(F("+CUSD: 2")) == -1) {

      String mesaj;
      if(Operator.indexOf(F("Turk Telekom")) != -1) {
        mesaj = _data.substring(_data.indexOf(F(",\""))+2, _data.lastIndexOf(F("1-KALAN KULLANIM")));
      } else {
        mesaj = _data.substring(10, 80);
      }
      mesaj.trim();
      Mesaj_Gonder(TelNo, mesaj);
    }
    Islem(false);
  }

  // Operatör ve Internet Okuma İşlemleri!
  if(millis() - Son_Islem > 30000) {
    Islem(true);
    
    // Operatoru Oku
    Operator_Oku();
    Log(F("Operator Okundu: "));
    Log(Operator);

    if(Operator == "BAGLANTI YOK") {
      LED(LED_OPERATOR, LOW, 50);
    } else {
      LED(LED_OPERATOR, HIGH, 50);
    }

    Islem(false);
    delay(250);

    Islem(true);
    _sonuc = 0;
    gsm.println(F("AT+SAPBR=2,1"));
    _sonuc = bekle(F("+SAPBR: 1,1,"), F("0.0.0.0"), 8000);

    if(_sonuc == 1) {
      Internet_Baglimi = true;
      LED(LED_GPRS, HIGH, 50);
    } else {
      Internet_Baglimi = false;
      LED(LED_GPRS, LOW, 50);
    }

    Islem(false);
    delay(250);
    Islem(true);
    // Sinyal kalitesini ölç!
    Sinyal_Kalitesi();

    // Internet bağlantısı yoksa ve internet aktif ise yeniden bağlanmayı dene!
    if(Internet_Aktifmi && !Internet_Baglimi) {
      Log(F("Internet baglantisi yokmus, aciliyor..."));
      Internete_Baglan();
      
      if(Internet_Baglimi) {
        LED(LED_GPRS, HIGH, 50);
      } else {
        LED(LED_GPRS, LOW, 50);
      }
    }

    Son_Islem = millis();
    
    Islem(false);
  }

  // Sensörü oku
  if(millis() - Son_Sensor_Okuma > 60000) {
    Islem(true);
    
    Sensor_Oku();
    Log(F("Sicaklik: "));
    Log(String(Sicaklik));
    Log(F("Nem:"));
    Log(String(Nem));
    Log(F("Basinc:"));
    Log(String(Basinc));

    Islem(false);
  }

  // İnternete bilgi gönderme!
  if(millis() - Son_HTTP_Istek > 300000) {
    Islem(true);
    
    Internete_Veri_Gonder();
    
    Islem(false);
  }
  
  // Ekran Güncelleme
  if(millis() - Son_Ekran_Guncelleme > 5000) {
    LED(LED_ISLEM, HIGH, 50);
    
    int ekran = Gosterilen_Ekran % 4;
    Ekran_Goster(ekran);
    Log(F("Ekran Gosterildi:"));
    Log(String(ekran));

    Gosterilen_Ekran++;
    if(Gosterilen_Ekran > 999) {
      Gosterilen_Ekran = 0;
    }

    LED(LED_ISLEM, LOW, 50);
  }

}
