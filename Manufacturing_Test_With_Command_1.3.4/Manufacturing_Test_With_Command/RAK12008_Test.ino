#ifdef  RAK12008_MODULE

#include "SparkFun_STC3x_Arduino_Library.h" // Click here to get the library: http://librarymanager/All#SparkFun_STC3x
#define STC31_ADDRESS     0x2C

void RAK12008_init()
{
  pinMode(WB_IO2,OUTPUT);
  digitalWrite(WB_IO2,HIGH);  //power on RAK12008.
  Wire.begin();
}
void RAK12008_test(unsigned long time_out)
{
  STC3x mySensor;
  RAK12008_init();
  if (mySensor.begin(STC31_ADDRESS,Wire) == false)
  {
    Serial.printf("RAK12008 Test Failed!\n"); 
    return ;
  }
  Serial.printf("RAK12008 Test OK!\n");
}

#endif
