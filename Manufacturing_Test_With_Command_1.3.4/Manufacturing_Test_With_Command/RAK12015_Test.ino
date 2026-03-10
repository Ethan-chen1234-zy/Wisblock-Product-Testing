#ifdef RAK12015_MODULE
#include <Arduino.h>
#include "Wire.h"
#define RAK12015_SENSOR_PIN   WB_A1

volatile uint8_t gRAK12015ReadCount = 0;

void RAK12015_change_interrupt()
{
  gRAK12015ReadCount++;
}
int test12015_task(unsigned long time_out)
{
  gRAK12015ReadCount = 0;
  pinMode(RAK12015_SENSOR_PIN, INPUT);
  //LOW 当引脚为低电平时，触发中断
  //CHANGE 当引脚电平发生改变时，触发中断
  //RISING 当引脚由低电平变为高电平时，触发中断
  //FALLING 当引脚由高电平变为低电平时，触发中断
  attachInterrupt(RAK12015_SENSOR_PIN, RAK12015_change_interrupt, RISING);
  unsigned long time_now = millis();
  while ((millis() - time_now) < time_out)
  {
    if (gRAK12015ReadCount >= 1)
    {
      Serial.printf("RAK12015 Test OK!\n");
      return 1;
    }
  }
  Serial.printf("RAK12015 Test Failed!\n");
  return -1;
}

void RAK12015_test(unsigned long time_out)
{
  unsigned long temp;
  temp = time_out;
  test12015_task(temp);
  detachInterrupt(RAK12015_SENSOR_PIN); //noInterrupts();
}
#endif
