unsigned char i;
unsigned char j;
int Max7219_pinCLK = 11;
int Max7219_pinCS = 12;
int Max7219_pinDIN = 13;
 
unsigned char disp1[22][8]={ //Eğer 22 den farklı sayıda ekran olan bir şey yapacaksanız 22 yi değişmeniz gerekir
{0x7E,0x81,0xA5,0x81,0xA5,0x99,0x81,0x7E},//Gülen Yüz
{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,},//KARANLIK
{0x0,0x1E,0x20,0x20,0x3E,0x2,0x2,0x3C},//S
{0x7C,0x40,0x40,0x7C,0x40,0x40,0x40,0x7C},//E
{0x0,0x42,0x62,0x52,0x4A,0x46,0x42,0x0},//N
{0x7C,0x10,0x10,0x10,0x10,0x10,0x10,0x7C},//I
{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,},//KARANLIK
{0x0,0x1E,0x20,0x20,0x3E,0x2,0x2,0x3C},//S
{0x7C,0x40,0x40,0x7C,0x40,0x40,0x40,0x7C},//E
{0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18},//V
{0x7C,0x10,0x10,0x10,0x10,0x10,0x10,0x7C},//I
{0x41,0x22,0x14,0x8,0x8,0x8,0x8,0x8},//Y
{0x3C,0x42,0x42,0x42,0x42,0x42,0x42,0x3C},//O
{0x3C,0x22,0x22,0x22,0x3C,0x24,0x22,0x21},//R
{0x42,0x42,0x42,0x42,0x42,0x42,0x22,0x1C},//U
{0x81,0xC3,0xA5,0x99,0x81,0x81,0x81,0x81},//M
{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,},//KARANLIK
{0x0,0x66,0xFF,0xFF,0x7E,0x3C,0x18,0x0},//Kalp
{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,},//KARANLIK
{0x0,0x66,0xFF,0xFF,0x7E,0x3C,0x18,0x0},//Kalp
{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,},//KARANLIK
{0x0,0x66,0xFF,0xFF,0x7E,0x3C,0x18,0x0},//Kalp
};
 
void Write_Max7219_byte(unsigned char DATA)
{
unsigned char i;
digitalWrite(Max7219_pinCS,LOW);
for(i=8;i>=1;i--)
{
digitalWrite(Max7219_pinCLK,LOW);
digitalWrite(Max7219_pinDIN,DATA&0x80);
DATA = DATA<<1;
digitalWrite(Max7219_pinCLK,HIGH);
}
}
 
void Write_Max7219(unsigned char address,unsigned char dat){
digitalWrite(Max7219_pinCS,LOW);
Write_Max7219_byte(address);
Write_Max7219_byte(dat);
digitalWrite(Max7219_pinCS,HIGH);
}
 
void Init_MAX7219(void){
Write_Max7219(0x09, 0x00);
Write_Max7219(0x0a, 0x03);
Write_Max7219(0x0b, 0x07);
Write_Max7219(0x0c, 0x01);
Write_Max7219(0x0f, 0x00);
}
 
void setup(){
pinMode(Max7219_pinCLK,OUTPUT);
pinMode(Max7219_pinCS,OUTPUT);
pinMode(Max7219_pinDIN,OUTPUT);
delay(50);
Init_MAX7219();
}
 
void loop(){
for(j=0;j<22;j++)
{
 for(i=1;i<9;i++)
 Write_Max7219(i,disp1[j][i-1]);
delay(500);
}
}
