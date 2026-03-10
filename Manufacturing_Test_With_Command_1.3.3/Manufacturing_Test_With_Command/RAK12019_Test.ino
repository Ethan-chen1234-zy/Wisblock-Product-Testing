#ifdef RAK12019_MODULE

#include "Wire.h"
#include "UVlight_LTR390.h"           //Click here to get the library:  Not updated yet, add link after update. 

#define   I2C_ADDRESS 0x53
UVlight_LTR390 ltr(I2C_ADDRESS);

void RAK12019_test(unsigned long timeout)
{
    //Sensor power switch
  pinMode(WB_IO2, OUTPUT);
  digitalWrite(WB_IO2, HIGH);
  delay(300);
  
  Wire.begin();
  if ( ltr.init() == false ) 
  {
    Serial.printf("RAK12019 Test Failed!\n");
    return ;
  }
  ltr.setMode(LTR390_MODE_ALS); //  LTR390_MODE_ALS
  ltr.setGain(LTR390_GAIN_3);
  ltr.setResolution(LTR390_RESOLUTION_18BIT);

  unsigned long time_now = millis();
  while ( (millis() - time_now) < timeout)
  {
    if (ltr.newDataAvailable())
    {
      if (ltr.getMode() == LTR390_MODE_ALS)
      {
        Serial.printf("Ambient Light Lux:%0.2f\r\n", ltr.getLUX()); //calculate the lux
        Serial.printf("RAK12019 Test OK!\n");
        return ;
      }
      else
      {
        Serial.printf("UV Index:%0.2f\r\n", ltr.getUVI());
        Serial.printf("RAK12019 Test OK!\n");
        return ;
      }
    }
  }
  Serial.printf("RAK12019 Test Failed!\n");
}
#endif
