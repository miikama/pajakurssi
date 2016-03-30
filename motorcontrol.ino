#include "Time.h"
#include "math.h"


/* Rotary encoder read example */
#define ENC_A 14
#define ENC_B 15
#define ENC_PORT PINC
#define DC_MOTOR 9


time_t time_start = micros();
time_t time_end = 0; 

time_t from_last_speedup = 0;
time_t speeduptime = millis();

const float pi = 3.141593;
float target_w = 0; 
float omega = (2*pi * pow(10,6)) / (time_end - time_start);   //angular velocity rad/s




 
void setup()
{
  /* Setup encoder pins as inputs */
  pinMode(ENC_A, INPUT);
  digitalWrite(ENC_A, HIGH);
  pinMode(ENC_B, INPUT);
  digitalWrite(ENC_B, HIGH);
  pinMode(DC_MOTOR, OUTPUT);
  
  Serial.begin (115200);
  Serial.println("Start");
  Serial.println("give the target angular velocity (int)");
  target_w = read_serial();
  //starting motor and waiting for a bit
  analogWrite(DC_MOTOR, 255);
  delay(100);  
}
 
void loop()
{
  static uint16_t counter = 0;      //this variable will be changed by encoder input
  int16_t tmpdata;  
  
  /**/
  tmpdata = read_encoder();
  
  //if enough time has passed since the last speed change -> check if wanted speed
  /*
  from_last_speedup = millis() - speeduptime;
  if( from_last_speedup > 100){
      analogWrite(DC_MOTOR, map(target_w, 0, 1000, 0, 255); 
  }*/
  
  
  if( tmpdata ) {
    if( !(counter % 50)){
      Serial.print("Counter value: ");
      Serial.println(counter, DEC);
    }
    counter += tmpdata;
    counter = counter % 4092;
    
    if( !(counter) ) {
      time_end = micros(); 
      omega = (2*pi * pow(10,6)) / (time_end - time_start);
      Serial.print("angular velocity: ");
      Serial.println(omega, 5);
      time_start = micros();
      
    
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
 
/* returns change in encoder state (-1,0,1) */
int16_t read_encoder()
{
  static int16_t enc_states[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};
  static uint16_t old_AB = 0;
  /**/
  old_AB <<= 2;                   //remember previous state
  old_AB |= ( ENC_PORT & 0x03 );  //add current state
  return ( enc_states[( old_AB & 0x0f )]);
}
