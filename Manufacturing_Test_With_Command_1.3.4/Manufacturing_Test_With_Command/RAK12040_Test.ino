#ifdef RAK12040_MODULE

#include <Wire.h>
#include <SparkFun_GridEYE_Arduino_Library.h>  //Click here to get the library: http://librarymanager/All#SparkFun_GridEYE_Arduino_Library

GridEYE AMG8833;

void RAK12040_test(unsigned long timeout)
{
  uint8_t DateFlag = 0;
  float Temper = -100;
  int16_t FRRValue = 0;
  Wire.begin();

  AMG8833.begin(0x68 , Wire);
  delay(500);

  AMG8833.setFramerate1FPS();
  FRRValue = AMG8833.getRegister(FRAMERATE_REGISTER, 1);
  if(FRRValue & (1 << 0))
  {
    delay(10);
  }
  else
  {
    Serial.printf("RAK12040 Test Failed\n");
    return;
  }

  // Variables to store temperature values.
  float testPixelValue = -100;
  float hotPixelValue = -100;
  int hotPixelIndex = 0;

  for(unsigned char i = 0; i < 64; i++)
  {
    testPixelValue = AMG8833.getPixelTemperature(i);
    if(testPixelValue > hotPixelValue)
    {
      hotPixelValue = testPixelValue;
      hotPixelIndex = i;
    }
  }

  Serial.print("The hottest pixel is #");
  Serial.print(hotPixelIndex);
  Serial.print(" at ");
  Serial.print(hotPixelValue);
  Serial.println("C");
  
  if(( hotPixelValue < -10 ) || ( hotPixelValue > 60 ))
  {
    Serial.printf("RAK12040 Test Failed\n");
    return;
  }
  else
  {
    Serial.printf("RAK12040 Test OK\n");
    return;
  }
}
#endif
