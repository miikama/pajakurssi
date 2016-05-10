#include "Time.h"
#include "math.h"


/* Rotary encoder read example */
#define ENC_A 2
#define ENC_PORT PINC
#define DC_MOTOR 9


time_t time_start = micros();
time_t time_end = 0; 

time_t from_last_speedup = 0;
time_t speeduptime = millis();

const float pi = 3.141593;
float target_w = 0; 
float omega = (2*pi * pow(10,6)) / (time_end - time_start);   //angular velocity rad/s

volatile int encoderValue = 0;

//void count(void); // code for counting the increasing values of encoder ticks 

 
void setup()
{
 
  
  Serial.begin (9600);  
  Serial.println("Start");
  Serial.println("give the target angular velocity (voltage between 0 and 255)");
  target_w = read_serial();
  
  //starting motor and waiting for a bit
  analogWrite(DC_MOTOR, target_w);
  delay(10); 
 
  /* Setup encoder pins as inputs */
  pinMode(ENC_A, INPUT);
  //digitalWrite(ENC_A, LOW);
  attachInterrupt(0,count,CHANGE);
 
}
 
void loop()
{
    int rounds = 50;
    
    if( (encoderValue % rounds) == 0 ) {
      Serial.print("encodervalue ");
      Serial.println(encoderValue);
      time_end = micros(); 
      omega = (rounds * 2*pi * pow(10,6)) / (time_end - time_start);
      Serial.print("angular velocity: ");
      Serial.println(omega, 5);
      time_start = micros();
      
    
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
 
 
//used for the pin interrupt
void count()
{
    encoderValue++;
}
