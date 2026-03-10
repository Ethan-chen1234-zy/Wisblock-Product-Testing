#ifdef RAK12032_MODULE

#include <Wire.h>
#include <SparkFunADXL313.h> //Click here to get the library: http://librarymanager/All#SparkFun_ADXL313

ADXL313 myAdxl;

void RAK12032_test(unsigned long timeout)
{
  Wire.begin();
  delay(100);
  myAdxl.begin(); // 防止第一次上电测试时测试失败的现象。
  delay(100);
  if (myAdxl.begin() == false) //Begin communication over I2C
  {
    Serial.printf("RAK12032 Test Failed\n");
    return;
  }
  Serial.printf("RAK12032 Test OK\n");
}
#endif
