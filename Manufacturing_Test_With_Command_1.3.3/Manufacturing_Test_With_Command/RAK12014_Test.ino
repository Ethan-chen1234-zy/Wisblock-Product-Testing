#ifdef RAK12014_MODULE

#include <Wire.h>
#include <vl53l0x_class.h>      // Click to install library: http://librarymanager/All#stm32duino_vl53l0x

VL53L0X sensor_vl53l0x(&Wire, WB_IO2); 

void VL53L0X_I2CRead(uint8_t DeviceAddr, uint8_t RegisterAddr, uint8_t* pBuffer, uint16_t NumByteToRead)
{
   Wire.beginTransmission(((uint8_t)(((DeviceAddr) >> 1) & 0x7F)));
   Wire.write(RegisterAddr);
   Wire.endTransmission(false);

   Wire.requestFrom(((uint8_t)(((DeviceAddr) >> 1) & 0x7F)), (byte) NumByteToRead);

   int i=0;
   while (Wire.available())
   {
     pBuffer[i] = Wire.read();
     i++;
   }

   return ;
}

void RAK12014_test(unsigned long timeout)
{
  pinMode(WB_IO2, OUTPUT);

  digitalWrite(WB_IO2, HIGH);

  int status1;
  
  Wire.begin();

  sensor_vl53l0x.begin();

  sensor_vl53l0x.VL53L0X_Off();

/*
 * @bref 使用原本库自带的初始化Sensor会报错说无效的ID或者直接初始化不通过。
 */
//  status1 = sensor_vl53l0x.InitSensor(0x52);
//  if(status1)
//  {
//    Serial.printf("RAK12014 Test Failed!\n");
//    return ;
//  }

/*
 * @bref 改为直接通过读取ID来判断是否通信成功。
 */
  sensor_vl53l0x.VL53L0X_On();

  uint16_t  ID = 0;
  uint8_t   Buf[2]={0};
  VL53L0X_I2CRead(VL53L0x_DEFAULT_DEVICE_ADDRESS, VL53L0X_REG_IDENTIFICATION_MODEL_ID, Buf, 2);
  ID = (Buf[0] << 8) + Buf[1];

  if(ID == 0xEEAA)  //  传感器默认ID为 0xEEAA .
  {
    Serial.printf("RAK12014 Test OK!\n");
  }
  else
  {
    Serial.printf("RAK12014 Test Failed!\n");
  }

//  uint32_t distance;
//  unsigned long time_now = millis();
//  while ( (millis() - time_now) < timeout)
//  {
//    status1 = sensor_vl53l0x.GetDistance(&distance);
//    if (status1 == VL53L0X_ERROR_NONE)
//    {
//      // Output data.
//      char report[64];
//      snprintf(report, sizeof(report), "| Distance [mm]: %ld |", distance);
//      Serial.println(report);
//      Serial.printf("RAK12014 Test OK!\n");
//      return ;
//    }
//    delay(300);
//  }
//  Serial.printf("RAK12014 Test Failed!\n");
}
#endif
