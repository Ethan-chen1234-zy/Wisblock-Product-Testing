#ifdef RAK14008_MODULE

#include "Production_test_configure.h"
#include "RevEng_PAJ7620.h" //Click here to get the library: http://librarymanager/All#Gesture_PAJ7620      版本1.0.0 名头文件 PAJ7620.h
//2026.1.20  注释链接为 Gesture_PAJ7620  ，但使用头文件是 RevEng_PAJ7620.h ，  此处使用RevEng_PAJ7620 库 http://librarymanager/All#RevEng_PAJ7620

RevEng_PAJ7620 sensor = RevEng_PAJ7620();   // Create gesture sensor Object.


void RAK14008_init(void)
{
  pinMode(WB_IO2, OUTPUT);
  digitalWrite(WB_IO2, HIGH); // �����ڵ�Ƭ����λʱ���Ŵ�������������������������λ�����µĿ�����
}
void RAK14008_test(unsigned long timeout)
{
  RAK14008_init();
  
  if(sensor.begin() == 0 ) // Returns 0 if sensor connect fail
  {
    Serial.println(F("RAK14008 Test Failed!"));
    return;
  }
  Serial.println(F("RAK14008 Test OK."));
  return;
}
#endif
