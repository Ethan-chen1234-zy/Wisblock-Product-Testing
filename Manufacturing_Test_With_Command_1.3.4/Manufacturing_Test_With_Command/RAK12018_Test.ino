#ifdef RAK12018_MODULE
#include "Wire.h"
void RAK12018_test(unsigned long timeout)
{
  Serial1.begin(9600);
  int time = 1000;
  String rsp = "";
  while (time--)
  {
    if (Serial1.available() > 0)
    {
      rsp += char(Serial1.read());
    }
    delay(1);
  }
  if (rsp.length() > 0)
  {
    Serial.printf("RAK12018 Test OK!\n");
    Serial.println(rsp);
  }
  else
  {
    Serial.printf("RAK12018 Test Failed!\n");
  }
  rsp = "";

}
#endif
