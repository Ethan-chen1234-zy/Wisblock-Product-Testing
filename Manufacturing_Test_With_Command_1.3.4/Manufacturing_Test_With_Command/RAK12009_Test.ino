#ifdef RAK12009_MODULE
#include <Wire.h>
#include "ADC121C021.h"

#include <math.h>
#include <Wire.h>
#include "ADC121C021.h"

#define EN_PIN        WB_IO6  //Logic high enables the device. Logic low disables the device
#define ALERT_PIN     WB_IO5  //a high indicates that the respective limit has been violated.
#define MQ3_ADDRESS   0x55    //the device i2c address

ADC121C021 MQ3;

void RAK12009_test(unsigned long time_out)
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
  if (MQ3.begin(MQ3_ADDRESS, Wire))
  {
    //*******config ADC121C021 *******************************************
    MQ3.configCycleTime(CYCLE_TIME_32); //set ADC121C021 Conversion Cycle Time
    MQ3.configAlertHold(Disable); //set ADC121C021 alerts  self-clear
    MQ3.configAlertFlag(Disable); //Disables ADC121C021 alert status bit [D15] in the Conversion Result register.
    MQ3.configAlertPin(Enable); //Enables the ALERT output pin of ADC121C021
    MQ3.configPolarity(High); //Sets ADC121C021 ALERT pin to active high
    MQ3.setAlertLowThreshold(1);  //set ADC121C021 Alert low Limit
    MQ3.setAlertHighThreshold(4095); //set ADC121C021 Alert high Limit
    MQ3.setVoltageResolution(5.0);
    for (i = 0; i < 5; i++)
    {
      sum = sum + MQ3.getSensorVoltage(); //getAdcValue()
      delay(10);
    }
    readVoltage = sum / 5.0;
    Serial.printf("MQ3 sensor voltage %3.2f V \n", readVoltage);
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
}

#endif
