#ifdef RAK14001_MODULE

#include <Wire.h>
#include <NCP5623.h>     //library: http://librarymanager/All#RAKwireless-NCP5623-RGB-LED-Library

NCP5623 rgb;

void RAK14001_init(void)
{
  // enable RAK14001
  pinMode(WB_IO6, OUTPUT);
  digitalWrite(WB_IO6, HIGH);

  // If using Native I2C
  Wire.begin();
  Wire.setClock(100000);

  Serial.println("RAK14001 RGB LED Test");
}

void RAK14001_test(unsigned long timeout)
{
  RAK14001_init();
  if (!rgb.begin())
  {
    Serial.printf("RAK14001 Test Failed\n");
    return;
  }
  rgb.setCurrent(26);
  for(int i=0;i<5;i++)// 5s circle change.
  {
    rgb.setColor(255,0,0);    // RED
    delay(330);
    rgb.setColor(0,255,0);    // GREEN
    delay(330);
    rgb.setColor(0,0,255);    // BLUE
    delay(330);
  }
  rgb.setColor(0,0,0);        // OFF
}


#endif
