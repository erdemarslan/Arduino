#include <Servo.h>

// Değişkenleri tanımlayalım
int solA, solB, sagA, sagB, servoPin, trigPin, echoPin, onAci, solAci, sagAci;
Servo motor;
boolean debug = true;

void setup() {
  // Serial ekranı açıyoruz!
  if(debug) {
    Serial.begin(9600);
  }
  // Değişkenleri tanımlıyoruz
  solA = 2;
  solB = 3;
  sagA = 5;
  sagB = 4;
  trigPin = 6;
  echoPin = 7;
  servoPin = 8;
  onAci = 90;
  solAci = 180;
  sagAci = 0;

  // yaz fonksiyonu, seri ekrana yazılıp yazılmayacağını belirliyor.
  yaz("Degiskenler tanimlandi...");
  
  // Pin Modlarını belirle
  pinMode(solA, OUTPUT);
  pinMode(solB, OUTPUT);
  pinMode(sagA, OUTPUT);
  pinMode(sagB, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  yaz("Pinler ayarlandi...");

  // Tekerlekleri Durdur!
  dur();
  yaz("Tekerlekler durduruldu...");

  // Servo Motoru Bağla
  motor.attach(servoPin);
  motor.write(onAci);
  yaz("Servo baglandi ve baslangica alindi...");
}

void loop() {
  // Ön mesafeyi ölç
  int on_mesafe = mesafe_olc(onAci);

  // mesafe 30 dan büyükse ya da 5 veya daha küçükse ileri git!
  // 5ten küçükse, mesafe ölçülemeyecek kadar çok demektir.
  if(on_mesafe > 30 || on_mesafe <= 5) {
    ileri();
    yaz("Araba ileri gidiyor. Mesafe " + String(on_mesafe) + " olarak olculdu.");
    delay(300);
  } else {

    // önde engel var. önce dur sonra sağa sola bak
    dur();
    yaz("Engel goruldugunden araba durdu!");

    int sol_mesafe = mesafe_olc(solAci);
    delay(300);
    int sag_mesafe = mesafe_olc(sagAci);
    delay(300);

    yaz("Sag ve sol mesafeler olculdu. Sag = " + String(sag_mesafe) + " Sol = " + String(sol_mesafe));

    // eğer sol mesafe sağ mesafeden büyükse sola dön. Değilse sağa dön
    if(sol_mesafe > sag_mesafe) {
      yaz("Sol mesafe buyuk oldugundan once geri cikilip sonra sola donuluyor.");
      geri();
      delay(300);
      sol();
      delay(300);
      dur();
      delay(100);
    } else {
      yaz("Sag mesafe buyuk oldugundan once geri cikilip sonra saga donuluyor.");
      geri();
      delay(300);
      sag();
      delay(300);
      dur();
      delay(100);
    }
  }
}

int mesafe_olc(int servo_aci) {
  motor.write(servo_aci);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  int sure = pulseIn(echoPin, HIGH);
  int mesafe = sure / 2 / 29.1;
  
  return mesafe;
}

void ileri() {
  digitalWrite(solA, HIGH);
  digitalWrite(solB, LOW);
  digitalWrite(sagA, HIGH);
  digitalWrite(sagB, LOW);
  yaz("ileri gidiliyor...");
}

void geri() {
  digitalWrite(solA, LOW);
  digitalWrite(solB, HIGH);
  digitalWrite(sagA, LOW);
  digitalWrite(sagB, HIGH);
  yaz("geri gidiliyor...");
}

void sol() {
  digitalWrite(solA, LOW);
  digitalWrite(solB, HIGH);
  digitalWrite(sagA, HIGH);
  digitalWrite(sagB, LOW);
  yaz("sola donuluyor...");
}

void sag() {
  digitalWrite(solA, HIGH);
  digitalWrite(solB, LOW);
  digitalWrite(sagA, LOW);
  digitalWrite(sagB, HIGH);
  yaz("saga donuluyor...");
}

void dur() {
  digitalWrite(solA, LOW);
  digitalWrite(solB, LOW);
  digitalWrite(sagA, LOW);
  digitalWrite(sagB, LOW);
}

void yaz(String metin) {
  if(debug) {
    Serial.println(metin);
  }
}

