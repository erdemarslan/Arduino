/*
 * Bağlantı Şekli
 * Ekran      | Arduino
 * VCC          5V
 * GND          GND
 * SDA          A4
 * SCL          A5
 * 
 * 
 * Para Makinesi  | Arduino
 * COIN             D2
 * GND              GND
 * 
 * 
 * Para Makinesi 12V ile beslenir. Arduinoya RAW yada VIN girişinden 12V verilebilir ancak uzun sürede zarar verebiliyor.
 * Para Makinesi ile arduinonun GND leri birleştirilir.
 * Loop içinde istenilen komutlar çalıştırılabilir. Para geldiğinde çalışan komut durur, para sayılır, daha sonra loop kaldığı yerden devam eder.
 * Eğer motor, röle vb. gibi reaktif akım çeken ürünler kullanılacaksa, motor veya röle çalışırken para makinesinin enerjisini bir röle ile kesmek ve para sayımını durdurmak iyi oluyor.
 * Çünkü bu tür elemanlar parazit yapıp arduinonun para gelmiş gibi davranmasına neden oluyor.
 * 
 * Para makinesinden gelen verilerin arduinoya alınması
 *                                    
 *                                    
 *                                    
 *                                                          5V   
 *                                                           |      
 *                                                        10 K Direnç (Pullup Direnç)
 *                                                           |      
 *       COIN(Beyaz Kablo)---- 1N4148 Diyot (varsa)     ------------------- Arduino D2 Pini
 *                                                           |
 *                                                        100 nF Kondansatör
 *                                                           |
 *                                                          GND
 *                                                          
 * Not: 1N4148 Diyot yok ise bağlanmasa da olur. Amacı para makinesini arduinodan gelebilecek ters akımdan korumak.
 * Not2: 100nF kutupsuz (seramik) kondansatör gelen dalganın daha net olmasını sağlar. Olmasa da tanıyor mu evet tanıyor. Sadece dalgalanmanın önüne geçiyor.
 * Elinizde 100nF (kodu 104) kondansatör yoksa bağlamasanız da olur. Bağlarsanız daha kararlı çalışır.
 * 10K Pullup direnç olmazsa olmazımız. Arduinodan INPUT_PULLUP ile tanıttığımda bazen kaçtığını gördüm. O yüzden şiddetle tavsiye ediyorum.
 * 
 */

// Ekran Kütüphanesini Ekleyelim
// I2C LCD 16x2 Ekran Kullanacağız
#include <LiquidCrystal_I2C.h>

// Ekranı tanımlayalım. Adress 0x3F - Kendinize göre değiştirin
LiquidCrystal_I2C lcd(0x3F, 16, 2);

// Para pinini tanımlayalım. Interrupt(Kesme) kullanacağımız için UNO ve NANO'da dijital 2 veya 3 kullanılabilir.
// Biz Dijital 2 pinini kullanacağız
// Bu program içinde bir daha değişmeyeceği için const sabitiyle tanımlıyoruz.
// Yine bu değişkende 256dan küçük sayı saklayacağımız için byte (hafızada 1 bayt yer kaplar, int 2 bayt yer kaplar) olarak tanımlıyoruz.
const byte paraPin = 2;

// Eğer tek para tanıyan makine kullanılacaksa bunu 1.0 yapın, altı lira tanıyanlarda tanıttığınız değere göre verin. 1 pulse kaç liraya denk geliyor onun değişkeni.
// Ben 3 para tanıtıyorum. 25 kuruş, 50 kuruş ve bir lira. 25 kuruş 1 pulse, 50 kuruş 2 pulse, 1 lira 4 pulse.
const double pulseKacLira = 0.25;

// Buradaki değişkenler interrupt içinde de kullanılacağı için volatile olarak tanıtılmak zorunda. Arduinonun referanslarına bakın.
volatile double lira = 0.00;
volatile bool paraGeldimi = false; // bu değişkeni true yaptığımızda ekranı güncelleyeceğiz. Diğer durumlarda ekran güncellenmeyecek!


void setup() {

  pinMode(paraPin, INPUT); // Biz kendimiz pullup yapacağımız için ben belirtmemiştim.

  // Ekranı tanımlayalım ve açalım
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.home();
  lcd.print("LUTFEN PARA ATIN");
  lcd.setCursor(0,1);
  lcd.print("Bakiye: 0.00 TL");

  // interrupt tanımlıyoruz
  attachInterrupt( digitalPinToInterrupt(paraPin), paraGeldi, RISING); // 2.ci pine kesme tanımlıyoruz. 2pin tetiklendiğinde paraGeldi fonksiyonu çalışsın, pin 0V dan 5V ya çıktığında bu fonksiyon çalışsın.
}

// kesme oluştuğunda bu fonksiyon çalışacak.
void paraGeldi() {

  lira = lira + pulseKacLira;
  
  if( !paraGeldimi ) {
    paraGeldimi= true;
  }
  
}

void loop() {

  // Bu kısım sadece para geldiğinde çalışacak. Böylece ekran her seferinde yenilenmeyecek!
  if( paraGeldimi ) {
    lcd.setCursor(8, 1); // 2. Satırdaki "Bakiye:" kısmından sonrasını silelim.
    lcd.print("        ");
    lcd.setCursor(8, 1); // Tekrar "Bakiye:" kısmına geri dönüp para bilgisini yazalım
    String yazi = String(lira) + " TL";
    lcd.print(yazi);
    paraGeldimi = false;
  }
}
