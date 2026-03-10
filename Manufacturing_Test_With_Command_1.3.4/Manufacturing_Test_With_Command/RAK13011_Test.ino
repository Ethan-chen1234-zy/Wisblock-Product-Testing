#ifdef RAK13011_MODULE

#include "Arduino.h"
#define SWITCH_PIN   WB_IO1 //SlotA installation, please do not use it on SLOTB and SLOTD
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

#endif
