#ifdef RAK12017_MODULE

uint8_t RAK12017_Flag = 0;
void blink() {
  if (digitalRead(WB_IO4) == 1)
    RAK12017_Flag = 1;
  else
    RAK12017_Flag = 2;
}

void RAK12017_test(unsigned long timeout)
{
  pinMode(WB_IO4, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(WB_IO4), blink, CHANGE);
  //LOW 当引脚为低电平时，触发中断
  //CHANGE 当引脚电平发生改变时，触发中断
  //RISING 当引脚由低电平变为高电平时，触发中断
  //FALLING 当引脚由高电平变为低电平时，触发中断
  if (RAK12017_Flag == 1)
  {
    RAK12017_Flag == 0;
    Serial.printf("RAK12017 Test Failed!\n");
  }
  else if (RAK12017_Flag == 2)
  {
    RAK12017_Flag == 0;
    Serial.printf("RAK12017 Test OK!\n");
  }
}
#endif
