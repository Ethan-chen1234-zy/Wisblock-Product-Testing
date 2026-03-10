#ifdef RAK12025_MODULE

#include <Wire.h>
#include "I3G4250D.h"  // Click here to get the library: http://librarymanager/All#I3G4250D   2026.1.20 V1.0.0  RAKwireless I3G4250D Gyroscope library

I3G4250D i3g4240d;
I3G4250D_DataScaled i3g4240d_data = {0};

void RAK12025_test(unsigned long timeout)
{
  //Sensor power switch
  pinMode(WB_IO2, OUTPUT);
  digitalWrite(WB_IO2, HIGH);
  delay(1000);
  
  Wire.begin();
  //if(false == i3g4240d.I3G4250D_Init(Wire,I3G4250D_I2C_ADDR))  // 2026.1.20 v1.0.0 版本函数方法已变更
  if(false == i3g4240d.I3G4250D_Init(0x0F,0x00,0x00,0x00,0x00,I3G4250D_SCALE_500))
  {
    Serial.printf("RAK12025 Test Failed!\n");
    return ;
  }
  //i3g4240d.I3G4250D_SetScale(I3G4250D_SCALE_500);   // 新版本没有此方法，在初始化I3G4250D_Init中设置
  i3g4240d_data = i3g4240d.I3G4250D_GetScaledData();
  Serial.println();
  Serial.print("Gyroscope X(dps) = ");
  Serial.print(i3g4240d_data.x);  
  Serial.print("Gyroscope Y(dps) = ");
  Serial.print(i3g4240d_data.y);  
  Serial.print("Gyroscope Z(dps) = ");
  Serial.println(i3g4240d_data.z); 
  Serial.printf("RAK12025 Test OK!\n");
}

#endif
