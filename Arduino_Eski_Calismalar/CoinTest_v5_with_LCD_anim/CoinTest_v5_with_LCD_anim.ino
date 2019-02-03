/*
 * CH926 coin acceptor decoder
 * This is a somehow more elaborate version to **accurately** count the coins entered
 * Fixed from http://timewitharduino.blogspot.be/2014/01/isr-based-sketch-for-adafruit-coin.html
 *
 * Note that coin type cannot be determined 100% because there is no pause between coins in the pulse train.
 * So for example, inserting two "50 cents" coins rapidly will lead to the same pulse train as a "1 EUR" coin. 
 * That does not really matter, as long as the number of pulses is PROPORTIONAL to the coin value
 * 
*/

#include <LiquidCrystal_I2C.h>

#define COIN_PIN         2 // Only some pins can be used. Refer to https://www.arduino.cc/en/Reference/attachInterrupt
#define PULSE_TIMEOUT_MS 200 // In fast mode, each pulse is 20ms, with an interval of 100ms

const byte motorPin = 7;
const byte butonPin = 3;
volatile bool motorCalissinmi = false;


void butonaBastilar() {
  if(!motorCalissinmi) {
    motorCalissinmi = true;
  }
}

// initialize the library with the numbers of the interface pins
LiquidCrystal_I2C lcd(0x3F, 16, 2);

volatile double creditInCents = 0.0f;
volatile long lastCreditChangeTime = 0;

byte anim1[8] = {
  B00000,
  B00000,
  B00000,
  B11111,
  B00000,
  B00000,
  B00000,
};
byte anim2[8] = {
  B00000,
  B00000,
  B11111,
  B11111,
  B11111,
  B00000,
  B00000,
};
byte anim3[8] = {
  B00000,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B00000,
};
byte anim4[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};
byte anim5[8] = {
  B11111,
  B11111,
  B11111,
  B00000,
  B11111,
  B11111,
  B11111,
};


  
void setup() {
  // Debugging output
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();

  Serial.print("Initializing... ");
  lcd.print("Initializing... ");
  // COIN is just a NO or NC switch to GND according to the switch on the back 
  // so it requires a pull-up 
  pinMode(COIN_PIN, INPUT_PULLUP);
  pinMode(butonPin, INPUT_PULLUP);
  pinMode(motorPin, OUTPUT);
  // I configured it as NO to reduce power consumption through the pull-up when idle
  // so we trigger the interrupt on falling edge
  attachInterrupt(digitalPinToInterrupt(COIN_PIN), onCoinPulse, FALLING);
  attachInterrupt(digitalPinToInterrupt(butonPin), butonaBastilar, RISING);

  lcd.createChar(1, anim1);
  lcd.createChar(2, anim2);
  lcd.createChar(3, anim3);
  lcd.createChar(4, anim4);
  lcd.createChar(5, anim5);
  resetAnimation();

  // Print a message to the LCD.
  lcd.clear();
  lcd.print("Come and play!");
  displayCredit();
  Serial.println("Ready.");
}


// total amount of money collected, in cents
// Note that using an int instead of float makes sure we have no decimal issues in comparison



// executed for every pulse;
void onCoinPulse() {
  // Make sure this is a real pulse and not a spurious glitch
  delay(1);
  if(digitalRead(COIN_PIN)==LOW) {
    creditInCents += 0.25;
    lastCreditChangeTime = millis();
  }
  else{
    Serial.println("glitch");
  }
}

double previousCreditInCents = 0.0f;

void loop() {
  if (previousCreditInCents != creditInCents) {
    long now = millis();
    if (now - lastCreditChangeTime > PULSE_TIMEOUT_MS) {
      displayCredit();
      previousCreditInCents = creditInCents;
    }
    else {
      displayCountingAnimation();
    }
  }

  if(motorCalissinmi) {
    delay(100);
    digitalWrite(motorPin, HIGH);
    delay(5000);
    digitalWrite(motorPin, LOW);
    delay(100);
    motorCalissinmi = false;
  }
}

void displayCredit() {
  resetAnimation();
  String creditInfo = String("Credit: ") + (creditInCents) + "TL  ";
  
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the credit:
  lcd.print(creditInfo);
  
  Serial.println(creditInfo);
}

byte animation[16];

void resetAnimation() {
  animation[0]=1;
  animation[1]=1;
  animation[2]=1;
  animation[3]=1;
  animation[4]=1;
  animation[5]=1;
  animation[6]=1;
  animation[7]=1;
  animation[8]=2;
  animation[9]=3;
  animation[10]=4;
  animation[11]=5;
  animation[12]=5;
  animation[13]=4;
  animation[14]=3;
  animation[15]=2;
}
void displayCountingAnimation() {
  Serial.print(".");
  
  // print an animation on LCD
  lcd.setCursor(0, 1);
  byte firstChar = animation[0];
  for (int i = 0; i < 15; i++) {
    animation[i] = animation[i+1];
    lcd.write(animation[i]);
  }
  animation[15] = firstChar;
  lcd.write(animation[15]);
  delay(200);
}
