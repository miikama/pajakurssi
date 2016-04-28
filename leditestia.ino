#include <Adafruit_NeoPixel.h>
#include "Time.h"






#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);
    
void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
  Serial.println("alkaa");
  
}

int i = 0;
int p = 0;

void loop() {
   //i = (i +1) % 4;
   //strip.setPixelColor(i, 255, 0, 255);
   strip.show();
   
   //Serial.println("mika ledi");
   //int led_nro = read_serial();
   //Serial.println("anna rgb arvoja");
   //int r = read_serial();
   //int g = read_serial();
   //int b = read_serial();
   while(true) {
     
     unsigned long startt = micros();
     unsigned long endt = micros();
     
     strip.setPixelColor(0, 255, 255, 255);
     //strip.setPixelColor((i-1)%8, 0, 0, 0);
     strip.show();
     strip.setPixelColor(0,0,0,0);
     strip.show();
     i = (i+1)%100;
     if (i == 0) {
       if (p==1) {
         startt = millis();
         Serial.print("alku:");
         Serial.println(startt);
         strip.setPixelColor(1,255,0,0);
         strip.show();
         p = 0;
       } else {
         endt = millis();
         Serial.print("loppu: ");
         Serial.println(endt);
         Serial.print("aikaa menee: ");
         unsigned long diff = endt-startt;
         Serial.println(diff); 
         strip.setPixelColor(1,0,0,0);
         strip.show();
         p = 1;        
   }
     }
   }
}


/* reads the serial for user inputted numbers*/
int read_serial() 
{
  char intBuffer[12];
  String intData = "";
  int delimiter = (int) '\n';
  
  while(!Serial.available());
    while(1){
      int ch = Serial.read();
      if(ch == -1) {}
      else if (ch == delimiter) {
        break;
      }
      else {
        intData += (char) ch;
    }
  }
  int intLength = intData.length() +1;
  intData.toCharArray(intBuffer, intLength);
  intData = "";
  int i = atoi(intBuffer);
  return i;
}

