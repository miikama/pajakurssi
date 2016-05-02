
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN, NEO_GRB + NEO_KHZ800);

  int array[2][8][3] = {
    {{124, 109, 39},{124, 109, 39},{124, 109, 39},{124, 109, 39},{124, 109, 39},{124, 109, 39},{124, 109, 39},{124, 109, 39}},
    {{45, 83, 199}, {45, 83, 199}, {45, 83, 199}, {45, 83, 199}, {45, 83, 199}, {45, 83, 199}, {45, 83, 199}, {45, 83, 199}}
  };

void setup() {

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  fromArray(5000);  // Käy läpi yllä annettua arraytä ja vaihtaa valoja siinä annettujen pikselien mukaisesti. 
                    // Parametrinä aika, joka odetataan värien vaihdon välillä. 
}

void fromArray(uint8_t wait){
  for(int i=0; i<2; i++){
    for (int j=0; j<8; j++){
      strip.setPixelColor(j, strip.Color(array[i][j][0],array[i][j][1],array[i][j][2]));
    }
    strip.show();
    delay(wait);
  } 
} 
