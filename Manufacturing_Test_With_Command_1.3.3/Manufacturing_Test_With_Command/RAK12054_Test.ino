#ifdef RAK12054_MODULE

//#include "RAK_AS5600.h"   //2026.1.20 找不到RAK_AS5600的库， 类似的库中 AS5600 有同名的方法detectMagnet()  磁铁检测 状态位（true/false） 
#include "AS5600.h"   // Click here to get the library: http://librarymanager/All#AS5600

//RAK_AS5600 ams5600;
AS5600 ams5600;

void RAK12054_test(unsigned long timeout)
{
  pinMode(WB_IO2, OUTPUT);
  digitalWrite(WB_IO2, HIGH); //Turn on the power switch
  delay(300);
  Wire.begin();

  if (ams5600.detectMagnet() == 1)
  {
    Serial.printf("RAK12054 Test OK!\n");
  }
  else
  {
    Serial.printf("RAK12054 Test Failed!\n");
  }
}
#endif
