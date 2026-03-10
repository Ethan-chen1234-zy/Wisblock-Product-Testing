#ifdef RAK12004_MODULE
#include <math.h>
#include <Wire.h>
#include "ADC121C021.h"   // http://librarymanager/All#RAKwireless_MQx_library

#define EN_PIN        WB_IO6  //Logic high enables the device. Logic low disables the device
#define ALERT_PIN     WB_IO5  //a high indicates that the respective limit has been violated.
#define MQ2_ADDRESS   0x51    //the device i2c address

ADC121C021 MQ2;

void RAK12004_test(unsigned long timeout)
{
  float sum = 0;
  float readVoltage = 0;
  uint8_t i;

  pinMode(ALERT_PIN, INPUT);
  pinMode(EN_PIN, OUTPUT);
  digitalWrite(EN_PIN, HIGH); //power on RAK12004
  delay(100);

  //  unsigned long time_now = millis();
  //  while ( (millis() - time_now) < time_out)
  //  {
  if (MQ2.begin(MQ2_ADDRESS, Wire))
  {
    //*******config ADC121C021 *******************************************
    MQ2.configCycleTime(CYCLE_TIME_32); //set ADC121C021 Conversion Cycle Time
    MQ2.configAlertHold(Disable); //set ADC121C021 alerts  self-clear
    MQ2.configAlertFlag(Disable); //Disables ADC121C021 alert status bit [D15] in the Conversion Result register.
    MQ2.configAlertPin(Enable); //Enables the ALERT output pin of ADC121C021
    MQ2.configPolarity(High); //Sets ADC121C021 ALERT pin to active high
    MQ2.setAlertLowThreshold(1);  //set ADC121C021 Alert low Limit
    MQ2.setAlertHighThreshold(4095); //set ADC121C021 Alert high Limit
    MQ2.setVoltageResolution(5.0);
    for (i = 0; i < 5; i++)
    {
      sum = sum + MQ2.getSensorVoltage(); //getAdcValue()
      delay(10);
    }
    readVoltage = sum / 5.0;
    Serial.printf("MQ2 sensor voltage %3.2f V \n", readVoltage);
    /*float delt = readVoltage-1.8;
      if(abs(delt) < 0.5) //如果偏差电压小于允许偏差
      {
      Serial.printf("RAK12004 Test OK\n");
      }
      else
      {
      Serial.printf("RAK12004 Test Failed\n");
      }
    */
  }
  else
  {
    Serial.println("sensor was not found. Please check wiring/power. ");
  }
  Wire.end();
}
#endif
