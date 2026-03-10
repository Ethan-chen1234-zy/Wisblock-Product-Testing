#ifdef  RAK12033_MODULE

#include "RAK12033-IIM42652.h"  //Click here to get the library: http://librarymanager/All#RAKwireless-RAK12033-library

IIM42652 IMU;

void RAK12033_test(unsigned long time_out)
{
  Wire.begin();
  if(IMU.begin() == true) 
  {
    Serial.printf("RAK12033 Test OK!\n");
  }
  else
  {
    Serial.printf("RAK12033 Test Failed!\n"); 
  }
}

#endif
