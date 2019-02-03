// Serial monitör tanımlanmış ise oraya bilgi yazar!
void Log(String metin) {
  if(DEBUG) {
    Serial.println(metin);
  }
}

void LED(int led, int islem, int bekleme) {
  digitalWrite(led, islem);
  delay(bekleme);
}

void Islem(bool durum) {
  if(durum) {
    LED(LED_ISLEM, HIGH, 50);
    Ekran_Islem(true);
  } else {
    LED(LED_ISLEM, LOW, 50);
    Ekran_Islem(false);
  }
}

