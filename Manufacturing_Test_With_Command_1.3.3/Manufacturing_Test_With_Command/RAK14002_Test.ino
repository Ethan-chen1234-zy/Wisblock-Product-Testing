#ifdef RAK14002_MODULE

#include "Production_test_configure.h"
#include <Wire.h>
#include "CAP1293.h" // Click here to get the library: http://librarymanager/All#RAK14002-CAP1293-Library

void RAK14002_test(unsigned long time_out)
{
  CAP1293 sensor; // Initialize sensor
  bool LeftTouched    = 0;
  bool MiddleTouched  = 0;
  bool RightTouched   = 0;
  
  Wire.begin();   // Join I2C bus

  // Setup sensor
  if (sensor.begin() == false)
  {
    Serial.printf("RAK14002 Test Failed\n");
    delay(100);
    return;
  }
  else
  {
    Serial.printf("RAK14002 connected.\n");
    Serial.println("Please press the three touch buttons separately within 15s.");
  }
  
  unsigned long time_now = millis();
  while ( (millis() - time_now) < time_out)
  {
    if ((sensor.isLeftTouched() == true) && (LeftTouched == 0))
    {
      Serial.println("Left");
      LeftTouched=1;
    }
  
    if ((sensor.isMiddleTouched() == true) && (MiddleTouched == 0))
    {
      Serial.println("Middle");
      MiddleTouched=1;
    }
  
    if ((sensor.isRightTouched() == true) && (RightTouched == 0))
    {
      Serial.println("Right");
      RightTouched=1;
    }
    if((LeftTouched==1) && (MiddleTouched==1) && (RightTouched == 1))
    {
      Serial.println("RAK14002 Test OK\n");
      return;
    }
    delay(200);
  }
  Serial.printf("Test 15s Time out.\n");
  Serial.printf("RAK14002 Test Failed\n");
}
#endif
