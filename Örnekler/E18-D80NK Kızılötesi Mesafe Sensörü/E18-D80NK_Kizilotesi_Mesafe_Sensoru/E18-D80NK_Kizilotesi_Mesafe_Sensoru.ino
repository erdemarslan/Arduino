/*
 * E18-D80NK Kızılötesi Mesafe Sensörü Kullanımı
 * 
 * Sensör Özellikleri
 * * 5V DC
 * * Akım < 25mA
 * * Yük Altında Akım 100 mA
 * * Cevap Süresi < 2ms
 * * İşaretleme Açısı <= 15, 3-80 cm aralığı ölçüm
 * * Transparent ve opak cisimleri ölçer
 * * -25 +55 C derece çalışma aralığı
 * 
 * Bağlantı Şeması
 * Sensör                   Arduino
 * Kahverengi (kırmızı)     +5 Vcc
 * Mavi (Siyah)             GND
 * Siyah (Sarı)             Sinyal (D4)
 * 
 * Mesafe ayarı, sensörün arkasındaki potansiyometreden yapılır.
 * İstenilen mesafeye geldiğinde veya istenilen mesafenin altına düştüğünde pini LOW a çeker, diğer durumlarda HIGH dır.
 */

int Sinyal = 4;


void setup() {
  // Tek seferlik çalışacak kodlar
  Serial.begin(9600);
  pinMode(Sinyal, INPUT);
}

void loop() {
  // sürekli tekrar edecek kodlar
  delay(500);
  if(digitalRead(Sinyal) == LOW) {
    Serial.println("Engel Var");
  } else {
    Serial.println("Engel Yok");
  }
}
