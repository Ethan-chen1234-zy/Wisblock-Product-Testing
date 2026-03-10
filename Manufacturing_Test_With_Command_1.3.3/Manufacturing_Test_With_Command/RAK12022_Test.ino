#ifdef  RAK12022_MODULE
//#include "RAK_MAX31865.h"
#include "RAK12022_MAX31865.h"  //  库 library: http://librarymanager/All#RAK12022-MAX31865，新版本1.0.1 ； 头文件更名为：RAK_MAX31865.h ==》 RAK12022_MAX31865.h ，2026.1.20更正
/*
* @note 由于库与库之间宏定义名有冲突， 修改RAK_SPI.h/RAK_SPI.cpp/RAK12022_MAX31865.cpp 中的  修改SPI_Clock ==> RAK12022_SPIClock, 修改 SPI_USER ==》 RAK12022_SPI_USER ,修改 RAK_SPI => RAK_SPI_12022
*/

const int Max_CS = SS;
MAX31865 maxTemp;

void RAK12022_init()
{
  pinMode(WB_IO2,OUTPUT);
  digitalWrite(WB_IO2,HIGH);  //power on RAK12022.
  delay(300);
}
void RAK12022_test(unsigned long time_out)
{
  float mTemp, mResistance;
  uint8_t mStatus = 0;
  
  RAK12022_init();
  maxTemp.begin(Max_CS, MAX31865_4WIRE, MAX31865_PT100);//if use 2-wire,choose MAX31865_2WIRE (MAX31865_2WIRE,MAX31865_3WIRE，MAX31865_4WIRE)
  maxTemp.MAX31865_SetLowFaultThreshold(29);  // Set the low fault threshold to 30 degrees C
  maxTemp.MAX31865_SetHighFaultThreshold(34); // Set the high fault threshold to 70 degrees C
  
  delay(500);
  maxTemp.MAX31865_GetTemperatureAndStatus(mTemp, mResistance, mStatus);

  Serial.print("Resistance = ");
  Serial.print(mResistance);
  Serial.print(" Ohms,   ");

  Serial.print("Temperature = ");
  Serial.print(mTemp);
  Serial.println(" C,   ");

  if(mTemp > -10 && mTemp < 60)
  {
    Serial.printf("RAK12022 Test OK!\n");      
  }
  else
  {
    Serial.printf("RAK12022 Test Failed!\n"); 
  }
}

#endif
