#ifdef  RAK1905_MODULE

#include <MPU9250_WE.h>     // library: http://librarymanager/All#MPU9250_WE

#define MPU9250_ADDR    0x68

void RAK1905_test(unsigned long time_out)
{
  MPU9250_WE myMPU9250 = MPU9250_WE(MPU9250_ADDR);
  
  Wire.begin();
  
  if (!myMPU9250.init()) 
  {
    Serial.printf("RAK1905 Test Failed!\n");
  }
  else 
  {
    Serial.printf("RAK1905 Test OK!\n");
  }
}

#endif
