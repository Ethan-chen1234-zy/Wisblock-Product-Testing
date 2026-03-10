#ifdef RAK12006_MODULE

#if 1
#define RAK12006_SENSOR_PIN  WB_IO6   // Attach AM312 sensor to Arduino Digital Pin WB_IO6
int gCurrentStatus = 0;         // variable for reading the pin current status
int gLastStatus = 0;            // variable for reading the pin last status
void RAK12006_test(unsigned long timeout)
{
  pinMode(RAK12006_SENSOR_PIN, INPUT);
  delay(100);
  unsigned long time_now = millis();
  while ( (millis() - time_now) < timeout)
  {
    gCurrentStatus = !(digitalRead(RAK12006_SENSOR_PIN));
    Serial.printf("the sensor pin current status is:%d\r\n", gCurrentStatus);
    if (gLastStatus != gCurrentStatus)
    {
      if (gCurrentStatus == 1)
      {
        Serial.println("IR detected ...");
      }
      gLastStatus = gCurrentStatus;
    }
    else
    {
      delay(100);
    }
  }
}
#endif

#if 0
#define RAK12006_SENSOR_PIN  WB_IO6   // Attach AM312 sensor to Arduino Digital Pin WB_IO6

volatile uint8_t gRAK12006ReadCount = 0;

void RAK12006_change_interrupt()
{
  gRAK12006ReadCount++;
  //  Serial.printf("gRAK12006ReadCount is %d\n",gRAK12006ReadCount);
}
int test12006_task(unsigned long time_out)
{
  gRAK12006ReadCount = 0;
  pinMode(RAK12006_SENSOR_PIN, INPUT);   // The Water Sensor is an Input
  //LOW 当引脚为低电平时，触发中断
  //CHANGE 当引脚电平发生改变时，触发中断
  //RISING 当引脚由低电平变为高电平时，触发中断
  //FALLING 当引脚由高电平变为低电平时，触发中断
  attachInterrupt( digitalPinToInterrupt(RAK12006_SENSOR_PIN), RAK12006_change_interrupt, CHANGE );
  unsigned long time_now = millis();
  while ( (millis() - time_now) < time_out)
  {
    if (gRAK12006ReadCount >= 1)
    {
      Serial.printf("RAK12006 Test OK\n");
      return 1;
    }
  }
  Serial.printf("RAK12006 Test Failed\n");
  return -1;
}
void RAK12006_test(unsigned long time_out)
{
  unsigned long temp;
  temp = time_out;
  test12006_task(temp);
  detachInterrupt (digitalPinToInterrupt(RAK12006_SENSOR_PIN)); //noInterrupts();
}
#endif

#endif
