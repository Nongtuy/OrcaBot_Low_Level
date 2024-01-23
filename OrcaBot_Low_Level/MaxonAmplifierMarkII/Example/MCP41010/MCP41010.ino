#include <SPI.h>
int CS = 10 ; // initialising variable CS pin as pin 10 of arduino
int x ; // initialising variable x
float Voltage ; // initialising variable voltage
int I ; // this is the variable which changes in steps and hence changes resistance accordingly.
void setup()
{
pinMode (CS , OUTPUT) ; // initialising 10 pin as output pin
pinMode (A0, INPUT) ; // initialising pin A0 as input pin
SPI.begin() ; // this begins Serial peripheral interfece
Serial.begin(9600) ; // this begins serial communications between arduino and ic.
}
void loop()
{
for (int i = 0; i <= 255; i++)// this run loops from 0 to 255 step with 10 ms delay between each step
{
digitalPotWrite(i) ; // this writes level i to ic which determines resistance of ic
delay(10);
x = analogRead(A0) ; // read analog values from pin A0
Voltage = (x * 5.0 )/ 1024.0;// this converts the analog value to corresponding voltage level
Serial.print("Level i = " ) ; // these serial commands print value of i or level and voltage across wiper
Serial.print(i) ; // and gnd on Serial monitor of arduino IDE
Serial.print("\t Voltage = ") ;
Serial.println(Voltage,3) ;
}
delay(500);
for (int i = 255; i >= 0; i--) // this run loops from 255 to 0 step with 10 ms delay between each step
{
digitalPotWrite(i) ;
delay(10) ;
x = analogRead(A0) ;
Voltage = (x * 5.0 )/ 1024.0 ; // this converts the analog value to corresponding voltage level
Serial.print("Level i = " ) ; // these serial commands print value of i or level and voltage across wiper
Serial.print(i); // and gnd on Serial monitor of arduino IDE
Serial.print("\t Voltage = ");
Serial.println(Voltage,3);
}
}
int digitalPotWrite(int value) // this block is explained in coding section
{
digitalWrite(CS, LOW);
SPI.transfer(B00010001);
SPI.transfer(value);
digitalWrite(CS, HIGH);
}