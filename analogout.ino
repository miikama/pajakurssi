/*
  Analog input, analog output, serial output
 
 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin.
 Also prints the results to the serial monitor.
 
 The circuit:
 * potentiometer connected to analog pin 0.
   Center pin of the potentiometer goes to the analog pin.
   side pins of the potentiometer go to +5V and ground
 * LED connected from digital pin 9 to ground
 
 created 29 Dec. 2008
 modified 9 Apr 2012
 by Tom Igoe
 
 This example code is in the public domain.
 
 */

// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPin = A4;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int outputValue = 255;        // value output to the PWM (analog out)
char intBuffer[12];
String intData = "";
int delimiter = (int) '\n';
int i = 150; 

void setup() {
  // initialize serial communications at 9600 bps:
  pinMode(analogOutPin, OUTPUT);
  Serial.begin(115200); 
}

void loop() {

  analogWrite(analogOutPin, i);
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
  i = atoi(intBuffer);
  
  Serial.print("voltage out: ");
  Serial.println(analogOutPin, DEC);
  
  // change the analog out value:
  analogWrite(analogOutPin, i);           
     
    

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(2);                     
}


