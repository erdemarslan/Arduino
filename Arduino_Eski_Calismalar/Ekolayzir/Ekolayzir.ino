int led_pinleri[9] = { 3, 4, 5, 6, 7, 8, 9, 10, 11}; 
int analog_deger, i;

void setup()
{
for (i = 0; i < 9; i++)
  pinMode(led_pinleri[i], OUTPUT);
 Serial.begin(9600); 
}

void loop()
{
analog_deger = analogRead(A0);  
Serial.print(analog_deger);
Serial.print("   ");
analog_deger = analog_deger / 5;     
Serial.println(analog_deger); 


  if (analog_deger == 0)  
   {
   for(i = 0; i < 9; i++)
     {
     digitalWrite(led_pinleri[i], LOW);
     }
  }
  
  else
  {
   for (i = 0; i < analog_deger; i++) 
    {
     digitalWrite(led_pinleri[i], HIGH);
    }
    
    for(i = i; i < 9; i++)  
     {
      digitalWrite(led_pinleri[i], LOW);
     }
  }
}
