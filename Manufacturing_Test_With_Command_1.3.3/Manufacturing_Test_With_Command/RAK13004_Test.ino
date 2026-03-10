#ifdef RAK13004_MODULE

#include "Production_test_configure.h"
#include <Arduino.h>
#include "PCA9685.h"  //http://librarymanager/All#PCA9685

void RAK13004_test(unsigned long time_out)
{
  PCA9685 PCA9685;

  pinMode(WB_IO2, OUTPUT);
  digitalWrite(WB_IO2, 1);

  PCA9685.setupSingleDevice(Wire,0x40);// Library using 0x40(0100 0000) i2c address, and default Wire @400kHz.

  PCA9685.setupOutputEnablePin(WB_IO6);// WB_IO6 active LOW output enable.
  PCA9685.enableOutputs(WB_IO6);

  PCA9685.setOutputsNotInverted();

  PCA9685.setToFrequency(500); // Set PWM freq to 500Hz (supports 24Hz to 1526Hz)

  for(uint8_t i=1 ;i < 16; i+=2)
  {
    PCA9685.setChannelDutyCycle(i ,0 ,0);
  }
  
  unsigned long time_now = millis();
  while ( (millis() - time_now) < time_out)
  {
    for(uint8_t j=0 ;j < 100; j+=2)
    {
      for(uint8_t i=0 ;i < 16; i+=2)
      {
        PCA9685.setChannelDutyCycle(i, j,0);
      }
      delay(20);
    }
  }
}
#endif
