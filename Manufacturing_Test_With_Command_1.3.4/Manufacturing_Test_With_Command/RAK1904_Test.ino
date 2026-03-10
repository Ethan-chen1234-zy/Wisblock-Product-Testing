#ifdef RAK1904_MODULE

#include "Production_test_configure.h"
#include "SparkFunLIS3DH.h" // Click here to get the library: http://librarymanager/All#SparkFun_LIS3DH_Arduino_Library

/************************************LIS3DH** RAK1904**test**start*********************************/
LIS3DH SensorTwo( I2C_MODE, 0x18 );

void lis3dh_get() {
  // read the sensor value
  uint8_t cnt = 0;

  Serial.print(" X(g) = ");
  Serial.println(SensorTwo.readFloatAccelX(), 4);
  Serial.print(" Y(g) = ");
  Serial.println(SensorTwo.readFloatAccelY(), 4);
  Serial.print(" Z(g)= ");
  Serial.println(SensorTwo.readFloatAccelZ(), 4);
}
void LIS3DH_test(unsigned long timeout)
{
  if ( SensorTwo.begin() != 0 )
  {
    //Serial.println("Problem starting the sensor at 0x18.");
    Serial.printf("-----------RAK1904 Test Failed!-----------\n");
  }
  else
  {
    //Serial.println("Sensor at 0x18 started.");
    Serial.printf("\n-----------RAK1904 Test OK!-----------\n");
    lis3dh_get();
    Serial.printf("-----------RAK1904 Test OK!-----------\n");
  }
}
/************************************LIS3DH**RAK1904***end*********************************/

#endif
