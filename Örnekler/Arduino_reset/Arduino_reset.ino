// Ne işimize yarar. 
// Yazılımsal olarak arduino resetlememize yardımcı olur.
// Arduino yu kontrollü olarak resetlememize olanak sağlar.
// Örn. olarak belli bir millis süresine gelindiğinde veya belli bir tarihe gelindiğinde veya bir sensör birşey algıladığında.
// Amaç. Özellikle delay komutu yerine millis kullanılan kodlarda millis zamanını resetlemek için
// Neden millis zamanı önemli
// Millis fonksiyonu arduino ram belleğini kullanan bir komuttur. düzenli olarka resetlenmediğinde ram şişmesine ve kodların sağlıksız çalışmasına neden olur.
// Global dğeişkenlerin %55 üzerinde kullanıldığında kalan bölüm arduino yerel deişkenleri için kullanılır(millis, serial, delay vs komutlar için). 
// Bu alan bittiğinde arduino kararsız çalışacaktır.
// Örnek olarak %55 üzerindeki global değişkenli bir programda lcd ekranda bağlı ise ve ekrana belli yazılar yazılıyorsa
// millis gibi bir den fazla komut kullanılıyorsa belli bir süre sonra lcd ekranda karakterler bozulmaya bağlar ve program kararsız hale gelir. 
// millis gibi fonksiyonları resetlemek için iki yol vardır. Arduino yeniden başlatmak veya resetlemek.

// Seçim sizin. Sürekli yeniden başlat mı küçük bir kodla yeniden başlat mı ???


void(* resetFunc) (void) = 0; //Resetleme fonksiyonunu çağırmak için

unsigned long zaman1 = 0; // millis zaman1 sıfırlamak için
unsigned long zaman2 = 0; // millis zaman2 sıfırlamak için
  
void setup() {     
  Serial.begin(9600);
  Serial.println("Arduino Yazılımla Resetleme");
  Serial.println("Herhangi bir pin kullanmadan");
  delay(200);
}
 
void loop() 
{
  zaman1 = millis(); //Zaman1 için millis tanımlanıyor
  delay(500); // 500 ms (yarım saniye) bekliyoruz
  zaman2 = millis();//Zaman2 için millis tanımlanıyor
  Serial.print("Zaman1 : "); 
  Serial.println(zaman1); //millis zaman1 zamanını ekrana yazıyoruz
  Serial.print("Zaman2 : ");
  Serial.println(zaman2);//millis zaman2 zamanını ekrana yazıyoruz
  Serial.println(); //Ekrana satır atlattık
  delay(100); //100 ms bekle sonraki koda geç
          
  Serial.println("Arduino Resetleniyor. Eğer resetlenirse Zaman1 ve Zaman2 hep aynı sayılarda başlamalı.");
  Serial.println("Zaman1 ve Zaman2 artıyorsa arduino resetlenmemiş demektir.");
  Serial.println();//Ekrana satır atlattık
  delay(3000); //3 saniye bekleyelim
  resetFunc(); //ARDUINO RESETLEME FONKSIYONUNU ÇAĞIRALIM. ARDUİNO RESETLENİYOR...
  Serial.println("Arduino maalesef resetlenmedi. Zaman artmaya devam ediyor");
 
}
