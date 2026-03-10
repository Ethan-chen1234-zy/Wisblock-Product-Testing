#ifdef RAK13012_MODULE

#include "Arduino.h"
#include <Wire.h>

TwoWire *wi = &Wire;

void RAK13012_test(unsigned long timeout)
{
//  put your setup code here, to run once:
//  pinMode(WB_IO2, OUTPUT);
//  digitalWrite(WB_IO2, HIGH);

  wi->begin();        // join i2c bus (address optional for main)

  wi->beginTransmission(0x17);
  if ( 0 == wi->endTransmission() )
  {
    Serial.printf("RAK13012 Test OK\n");
  }
  else
  {
    Serial.printf("RAK13012 Test Failed\n");   
  }
}
#endif





/*#define SWITCH_PIN   WB_IO1 //SlotA installation, please do not use it on SLOTB and SLOTD
//#define SWITCH_PIN WB_IO3 //SlotC installation.

void RAK13011_test(unsigned long timeout)
{
  pinMode(SWITCH_PIN, INPUT_PULLDOWN);

  time_t time_now = millis();
  
  while ((millis() - time_now) < 5000)
  {
    if (digitalRead(SWITCH_PIN) == LOW)
    {
      Serial.printf("RAK13011 Test OK\n");
      return; 
    }
    delay(10);
  }
  Serial.printf("RAK13011 Test Failed\n");  
  return;
}

#endif*/
