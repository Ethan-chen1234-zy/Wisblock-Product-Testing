#ifdef  RAK12044_MODULE

#include "ADC121C021.h"

#define DRV5056_ADDRESS   0x56    // The device i2c address

void RAK12044_init()
{
  pinMode(WB_IO2,OUTPUT);
  digitalWrite(WB_IO2,HIGH);  //power on RAK12044.
}
void RAK12044_test(unsigned long time_out)
{
  float Vout;
  ADC121C021 DRV5056;
  
  RAK12044_init();

  if(DRV5056.begin(DRV5056_ADDRESS, Wire) == false)
  {
    Serial.printf("RAK12044 Test Failed!\n"); 
    return ;
  }
  DRV5056.configCycleTime(CYCLE_TIME_2048); //set ADC121C021 Conversion Cycle Time
  DRV5056.setVoltageResolution(3.3);

  Vout = DRV5056.getSensorVoltage() * 1000;
  delay(100);
  Vout = DRV5056.getSensorVoltage() * 1000;
  delay(100);
  Vout = DRV5056.getSensorVoltage() * 1000; // 多读几次，避免第一次读取为0.0V的情况。
  Serial.printf("Sensor analog output  : %5.1f mV\r\n", Vout);

  if((Vout<700) && (Vout>500))
  {
    Serial.printf("RAK12044 Test OK!\n");
  }
  else
  {
    Serial.printf("RAK12044 Test Failed!\n"); 
  }
}

#endif
