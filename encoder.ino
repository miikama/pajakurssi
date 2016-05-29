#include "Time.h"
#include "math.h"


/* Rotary encoder read example */
#define ENC_A 14
#define ENC_B 15
#define ENC_PORT PINC
 
void setup()
{
  /* Setup encoder pins as inputs */
  pinMode(ENC_A, INPUT);
  digitalWrite(ENC_A, HIGH);
  pinMode(ENC_B, INPUT);
  digitalWrite(ENC_B, HIGH);
  Serial.begin (115200);
  Serial.println("Start");
}
 
time_t time_start = micros();
time_t time_end = 0; 
 
void loop()
{
 static uint16_t counter = 0;      //this variable will be changed by encoder input
 int16_t tmpdata;
 const float pi = 3.141593;
 /**/
  tmpdata = read_encoder();
  
  float omega = (2*pi * pow(10,6)) / (time_end - time_start);   //angular velocity rad/mus

  
  
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
