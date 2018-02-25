//*** 1- Documentation

//This program is used to control a robot car using a app that communicates with Arduino trough a bluetooth module
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
SoftwareSerial mySerial(9,10); // RX, TX
#define PIN 8
#define NUM_PIXELS  20
Adafruit_NeoPixel strip = Adafruit_NeoPixel(20, PIN, NEO_GRB + NEO_KHZ800);

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
strip.begin();
clearStrip();
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
  case 'G':
    knightRider(5, 40, 2, 0xFF0000); // Cycles, Speed, Width, RGB Color (red)
    clearStrip();
    break;
  case 'g':
    clearStrip();
    break;
  case 'H':
    WigWag2(strip.Color(0, 0, 255), strip.Color(255, 0, 0), 150); // Blue and Red
    WigWag2(strip.Color(0, 0, 255), strip.Color(255, 0, 0), 200); // Blue and Red
    WigWag2(strip.Color(0, 0, 255), strip.Color(255, 0, 0), 150); // Blue and Red
    clearStrip();
    break;
  case 'h':
    clearStrip();
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
void knightRider(uint16_t cycles, uint16_t speed, uint8_t width, uint32_t color) {
  uint32_t old_val[NUM_PIXELS]; // up to 256 lights!
  // Larson time baby!
  for(int i = 0; i < cycles; i++){
    for (int count = 1; count<NUM_PIXELS; count++) {
      strip.setPixelColor(count, color);
      old_val[count] = color;
      for(int x = count; x>0; x--) {
        old_val[x-1] = dimColor(old_val[x-1], width);
        strip.setPixelColor(x-1, old_val[x-1]); 
      }
      strip.show();
      delay(speed);
    }
    for (int count = NUM_PIXELS-1; count>=0; count--) {
      strip.setPixelColor(count, color);
      old_val[count] = color;
      for(int x = count; x<=NUM_PIXELS ;x++) {
        old_val[x-1] = dimColor(old_val[x-1], width);
        strip.setPixelColor(x+1, old_val[x+1]);
      }
      strip.show();
      delay(speed);
    }
  }
}
void clearStrip() {
  for( int i = 0; i<NUM_PIXELS; i++){
    strip.setPixelColor(i, 0x000000); strip.show();
  }
}
uint32_t dimColor(uint32_t color, uint8_t width) {
   return (((color&0xFF0000)/width)&0xFF0000) + (((color&0x00FF00)/width)&0x00FF00) + (((color&0x0000FF)/width)&0x0000FF);
}
uint32_t colorWheel(byte WheelPos) {
  byte state = WheelPos / 21;
}
void WigWag2(uint32_t c, uint32_t c2, uint8_t wait) {
  for (int j = 0; j < 20; j++) { // The j<# determines how many cycles
    for (int i = 0; i < strip.numPixels(); i = i + 1) {
      strip.setPixelColor(i, c);
    }
    for (int i = (strip.numPixels() / 2); i < strip.numPixels(); i = i + 1) {
      strip.setPixelColor(i, 0);
    }
    strip.show();
    delay(wait);

    for (int i = 0; i < strip.numPixels(); i = i + 1) {
      strip.setPixelColor(i, 0);
    }
    for (int i = (strip.numPixels() / 2); i < strip.numPixels(); i = i + 1) {
      strip.setPixelColor(i, c2);
    }
    strip.show();
    delay(wait);
  }
}
