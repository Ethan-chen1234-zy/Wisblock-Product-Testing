#ifdef RAK13001_MODULE
#include "Arduino.h"
#include <Wire.h>

#define OC_PIN    WB_IO3
#define RELAY_PIN WB_IO4

void RAK13001_init(void)
{
  pinMode(WB_IO2, OUTPUT);
  digitalWrite(WB_IO2, HIGH);
  
  pinMode(RELAY_PIN,OUTPUT);
  pinMode(OC_PIN,INPUT_PULLUP);  
}

void RAK13001_test(unsigned long timeout)
{
  RAK13001_init();
  digitalWrite( RELAY_PIN , HIGH);
  delay(500);
  if(digitalRead(OC_PIN) == LOW)
  {
    Serial.printf("RAK13001 Test OK\n");
  }
  else
  {
    Serial.printf("RAK13001 Test Failed\n");
  }
}
#endif
