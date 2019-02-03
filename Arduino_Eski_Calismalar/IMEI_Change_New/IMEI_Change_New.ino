#include <SoftwareSerial.h>

const String ORIGINAL_IMEI PROGMEM  = "865472030900919";
const String NEW_IMEI PROGMEM       = "353183069434659";

unsigned long _zaman = 0;
bool _devam = false;
String _data, IMEI;
int islemSonuc, Menu = 0;


SoftwareSerial sim(7,8);


void setup() {
  // put your setup code here, to run once:
  _data.reserve(255);
  Serial.begin(9600);
  sim.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  while( !Serial ) {
    ; // Wait for serial open!
  }
  Serial.println(F("IMEI REPAIR TOOL v.0.1"));
  Serial.println(F("Waiting for GSM Module ready..."));

  while( !sim ) {
    ; // wait for sim ready
  }
  
  sim.println(F("AT"));
  
  waitFor("OK", "ERROR", 10000, false);

  if(islemSonuc == 1) {
    Serial.println(F("GSM Module is OK."));
    Serial.println(F(""));
    Serial.println(F("Waiting for user request..."));
    ShowMenu(false);
    
  } else {
    Serial.println(F("We do not connect GSM Module!..."));
    Serial.println(F("Please connect GSM Module and reboot your Arduino..."));
  }
}

void loop() {
  // Eğer Menu 0 ise ve serialden giriş varsa göster! Yoksa öyle boş boş dön!
  if(Menu == 0) {
    if(Serial.available() > 0) {
      String sorgu = Serial.readString();
      sorgu.toLowerCase();
      sorgu.trim();

      if(sorgu == "show") {
        Menu = 1;
      }

      else if(sorgu == "change") {
        Menu = 2;
      }

      else if(sorgu == "reset") {
        Menu = 3;
      }

      else if(sorgu == "help") {
        ShowMenu(true);
        Menu = 0;
      }
      
      else {
        Serial.println(F("Unknown request! Please try again."));
        //ShowMenu(true);
        Menu = 0;
      }
    }
  }

  // Eğer Menu 1 ise; IMEI Goster!
  if(Menu == 1) {

    ShowIMEI();
    
    Menu = 0;
    ShowMenu(true);
    return;
  }

  // Eğer Menu 2 ise IMIE Değiştir
  if(Menu == 2) {

    ShowIMEI();
    Serial.print(F("Licensed IMEI: "));
    Serial.println(ORIGINAL_IMEI);
    Serial.print(F("New IMEI: "));
    Serial.println(NEW_IMEI);
    Serial.println(F(""));

    Serial.println(F("Checking License. Please wait..."));
    delay(500);
    if( IMEI == ORIGINAL_IMEI) {

      sim.print(F("AT+SIMEI=\""));
      sim.print(NEW_IMEI);
      sim.println(F("\""));

      waitFor("OK", "ERROR", 20000, false);
      
      if(islemSonuc == 1) {
        Serial.println(F("Your IMEI changed succesfuly."));
        delay(1000);
        ShowIMEI();
        
      } else {
        Serial.println(F("An error occured while changing IMEI. Plase try again!"));
      }
      
    } else {
      Serial.println("CRC not correct for this device. Please use correct device. Exiting changing IMEI!");
    }

    Menu = 0;
    ShowMenu(true);
    return;
  }

  // Eğer Menu 3 ise IMEI Resetle
  if(Menu == 3) {
    ShowIMEI();
    Serial.print(F("Licensed IMEI: "));
    Serial.println(NEW_IMEI);
    Serial.print(F("New IMEI: "));
    Serial.println(ORIGINAL_IMEI);
    Serial.println(F(""));

    Serial.println(F("Checking CRC. Please wait..."));
    delay(500);
    if( IMEI == NEW_IMEI) {

      sim.print(F("AT+SIMEI=\""));
      sim.print(ORIGINAL_IMEI);
      sim.println(F("\""));

      waitFor("OK", "ERROR", 20000, false);
      
      if(islemSonuc == 1) {
        Serial.println(F("Your IMEI changed succesfuly."));
        delay(1000);
        ShowIMEI();
        
      } else {
        Serial.println(F("An error occured while changing IMEI. Plase try again!"));
      }
      
    } else {
      Serial.println("CRC not correct for this device. Please use correct device. Exiting changing IMEI!");
    }

    Menu = 0;
    ShowMenu(true);
    return;
  }
  
}
