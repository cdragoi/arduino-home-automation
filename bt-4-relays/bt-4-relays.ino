//*** 1- Documentation

//This program is used to control a robot car using a app that communicates with Arduino trough a bluetooth module
#include <SoftwareSerial.h>
SoftwareSerial mySerial(9,10); // RX, TX
char command;

int in1 = 4;
int in2 = 5;
int in3 = 6;
int in4 = 7;
void setup()
{
Serial.begin(38400); //Set the baud rate to your Bluetooth module.
mySerial.begin(9600);

pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
pinMode(in3, OUTPUT);
pinMode(in4, OUTPUT);
all_off();
}

void loop(){

if (mySerial.available()) {
command = mySerial.read();
Serial.println(command);
switch(command){
    case 'A':
    r1_on();
    break;
  case 'a':
    r1_off();
    break;
  case 'B':
    r2_on();
    break;
  case 'b':
    r2_off();
    break;
  case 'C':
    r3_on();
    break;
  case 'c':
    r3_off();
    break;
  case 'D':
    r4_on();
    break;
  case 'd':
    r4_off();
    break;  
  case '@':
    all_on();
    break;
  case '#':
    all_off();
    break;
}
}
}
void r1_on()
{
    digitalWrite(in1, LOW);
    mySerial.println("A");  
}
void r1_off()
{
    mySerial.println("a");
    digitalWrite(in1, HIGH);  
}
void r2_on()
{
    digitalWrite(in2, LOW);
    mySerial.println("B");  
}
void r2_off()
{
    digitalWrite(in2, HIGH);
    mySerial.println("b");  
}
void r3_on()
{
    digitalWrite(in3, LOW); 
    mySerial.println("C"); 
}
void r3_off()
{
    digitalWrite(in3, HIGH);
    mySerial.println("c");  
}
void r4_on()
{
    digitalWrite(in4, LOW); 
    mySerial.println("D"); 
}
void r4_off()
{
    digitalWrite(in4, HIGH);  
    mySerial.println("d");
}
void all_on()
{
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    mySerial.println("A");  
    mySerial.println("B");
    mySerial.println("C");
    mySerial.println("D");
}
void all_off()
{
    digitalWrite(in1, HIGH);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, HIGH); 
    mySerial.println("a"); 
    mySerial.println("b");  
    mySerial.println("c");
    mySerial.println("d");
}
