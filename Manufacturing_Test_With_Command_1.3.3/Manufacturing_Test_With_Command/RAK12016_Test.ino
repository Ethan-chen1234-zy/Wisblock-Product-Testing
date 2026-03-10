#ifdef RAK12015_MODULE

#include <Wire.h>
#include "ADC121C021.h"               // Click here to get the library: http://librarymanager/All#RAKwireless_MQx_library

#define  ReferenceVoltage1  3.30
#define  FLEX_ADDRESS      0x54       //the device i2c address
ADC121C021 Flex;

// Measure the voltage at 3.3V and the actual resistance of your// 10k resistor, and enter them below:
const float VCC = 3.3;                       //Module supply voltage, ADC reference voltage is 3.3V
const float R_DIV = 10000.0;                 // The partial voltage resistance is 10KΩ

// Upload the code, then try to adjust these values to more// accurately calculate bend degree.
const float STRAIGHT_RESISTANCE = 10000.0;   // The flat Resistance
const float BEND_RESISTANCE = 20000.0;      //Resistance at 90 degree bending


void RAK12016_test(unsigned long time_out)
{
  if ((Flex.begin(FLEX_ADDRESS, Wire)))
  {
    Flex.setVoltageResolution(ReferenceVoltage1);
    float flexRef=Flex.getVoltageResolution();
    uint8_t flexflag =abs(flexRef-ReferenceVoltage1);
    if (!flexflag)
    {
      float flexVoltage = Flex.getSensorVoltage();
      float flexR = R_DIV * (VCC / flexVoltage - 1.0);
      Serial.println("Voltage: " + String(flexVoltage) + " V");
      Serial.println("Resistance: " + String(flexR) + " ohms");
      float angle = map(flexR, STRAIGHT_RESISTANCE, BEND_RESISTANCE, 0, 90.0);
      Serial.println("Bend: " + String(angle) + " degrees");
      Serial.println();
    }
    else
    {
      Serial.println("please check the Reference Voltage!!!");
    }
  }
  else
  {
    Serial.println("please check device!!!");
  }
}
#endif
