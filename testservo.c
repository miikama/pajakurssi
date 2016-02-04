/* Sweep
 by BARRAGAN <http://barraganstudio.com> 
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/ 

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards
 
int pos = 0;   // variable to store the servo position 
char intBuffer[12];
String intData = "";
int delimiter = (int) '\n';
 
void setup() 
{ 
  Serial.begin(9600);
  Serial.println("Begin!");
  myservo.attach(9);// attaches the servo on pin 9 to the servo object 
} 
 
void loop() 
{ 
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
    
    Serial.println("Moving to: ");
    Serial.println(i);  
    myservo.write(i);              // tell servo to go to position in variable 'pos' 
    
    
    
    delay(500);         //waits for the servo to reach a position
    
} 
