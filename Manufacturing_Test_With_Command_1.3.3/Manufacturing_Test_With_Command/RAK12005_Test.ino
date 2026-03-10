#ifdef RAK12005_MODULE

#define RAK12005_SENSOR_PIN  WB_IO6   // Attach Water sensor to Arduino Digital Pin WB_IO6

volatile uint8_t gRAK12005ReadCount = 0;

void RAK12005_change_interrupt()
{
  gRAK12005ReadCount++;
//  Serial.printf("gRAK12005ReadCount is %d\n",gRAK12005ReadCount);
}
int test12005_task(unsigned long time_out)
{
  gRAK12005ReadCount = 0;
  pinMode(RAK12005_SENSOR_PIN, INPUT);   // The Water Sensor is an Input
//LOW 当引脚为低电平时，触发中断
//CHANGE 当引脚电平发生改变时，触发中断
//RISING 当引脚由低电平变为高电平时，触发中断
//FALLING 当引脚由高电平变为低电平时，触发中断
  attachInterrupt( digitalPinToInterrupt(RAK12005_SENSOR_PIN), RAK12005_change_interrupt,CHANGE );   
  unsigned long time_now = millis();
  while ( (millis() - time_now) < time_out)
  {
    if(gRAK12005ReadCount>=1)
    {      
      Serial.printf("RAK12005 Test OK\n");
      return 1;
    }    
  }
  Serial.printf("RAK12005 Test Failed\n");
  return -1;   
}
void RAK12005_test(unsigned long time_out)
{
  unsigned long temp;
  temp = time_out;
  test12005_task(temp);
  detachInterrupt (digitalPinToInterrupt(RAK12005_SENSOR_PIN)); //noInterrupts();
}
#endif
