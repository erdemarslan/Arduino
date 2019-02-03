// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTPIN 2     // what digital pin we're connected to
// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16,2);


void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");

  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.clear();

  lcd.home();
  lcd.print("DIJITAL");
  lcd.setCursor(0,1);
  lcd.print("TERMOMETRE");
  delay(3000);
  lcd.clear();
  lcd.home();
  lcd.print("SICAKLIK:");
  lcd.setCursor(0,1);
  lcd.print("NEM:% ");
}

void loop() {
  // Wait a few seconds between measurements.
  

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  int h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  int t = dht.readTemperature();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  lcd.setCursor(9,0);
  lcd.print("       ");
  lcd.setCursor(9,0);
  lcd.print(t);
  lcd.setCursor(12,0);
  lcd.print("C");
  lcd.setCursor(6,1);
  lcd.print("       ");
  lcd.setCursor(6,1);
  lcd.print(h);
  

  
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
 
  delay(2000);
}
