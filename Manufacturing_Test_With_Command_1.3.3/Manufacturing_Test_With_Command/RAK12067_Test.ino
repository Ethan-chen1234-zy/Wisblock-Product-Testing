#ifdef RAK12067_MODULE

#include "Arduino.h"

void RAK12067_test(unsigned long timeout)
{
  // put your setup code here, to run once:
  pinMode(WB_IO2, OUTPUT);
  digitalWrite(WB_IO2, HIGH);

  Serial.printf("RAK12067 Start Testing\n");
  delay(5000);
  Serial.printf("RAK12067 End Test\n");

  digitalWrite(WB_IO2, LOW);
//  sgm58031.begin();
//  if (sgm58031.getChipID() != DEVICE_ID)
//  {
//    Serial.printf("RAK12059 Test Failed\n"); 
//    return;
//  }
//  else
//  {
//    sgm58031.setAlertLowThreshold(0x0000);  // Write  0x0000  to Lo_Thresh
//    sgm58031.setAlertHighThreshold(0x7FFF); // Write 0x7FFF to Hi_Thresh
//    sgm58031.setConfig(0xC2E0);             // Write config, OS=1, AIN0 to GND, G=(+/-4.096V input range)
//    sgm58031.setVoltageResolution(SGM58031_FS_4_096);
//  }  
//  float gVoltage = sgm58031.getVoltage();
//  Serial.print(F("gVoltage="));
//  Serial.print(gVoltage);
//  Serial.println("V");
//  if((gVoltage> 3.2) && (gVoltage < 3.4))
//  {
//    Serial.printf("RAK12059 Test OK\n");
//    return;
//  }
//  else 
//  {
//    Serial.printf("RAK12059 Test Failed\n");   
//    return;
//  }
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
