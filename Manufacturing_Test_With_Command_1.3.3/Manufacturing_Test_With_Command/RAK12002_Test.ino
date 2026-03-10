#ifdef RAK12002_MODULE

#include "Melopero_RV3028.h" //http://librarymanager/All#Melopero_RV3028   2026.1.21 版本1.2.0

Melopero_RV3028 rtc;

void RAK12002_init(void)
{
  //rtc.initDevice(); // First initialize and create the rtc device     1.2.0版本没有此方法 
  rtc.initI2C();  // 1.2.0 版本初始化i2c地址方法
  
  rtc.set24HourMode();  // Set the device to use the 24hour format (default) instead of the 12 hour format

  // Set the date and time
  // year, month, weekday, date, hour, minute, second
  // Note: time is always set in 24h format
  // Note: month value ranges from 1 (Jan) to 12 (Dec)
  // Note: date value ranges from 1 to 31
  rtc.setTime(2021, 4, 6, 30, 11, 12, 13);
}

void RAK12002_test(unsigned long timeout)
{
  RAK12002_init();
  delay(1000);
  Serial.printf("%d:%d:%d %d/%d/%d \n",rtc.getHour(),rtc.getMinute(),rtc.getSecond(),rtc.getYear(),rtc.getMonth(),rtc.getDate());
  if((rtc.getHour() == 11) && (rtc.getMinute() == 12) && (rtc.getSecond() == 14))
  {
    Serial.printf("RAK12002 Test OK\n");
  }
  else
  {
    Serial.printf("RAK12002 Test Failed\n");
  }
}
#endif
