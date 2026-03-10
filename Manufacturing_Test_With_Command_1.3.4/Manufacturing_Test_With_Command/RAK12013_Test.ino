#ifdef RAK12013_MODULE

#include "Production_test_configure.h"
#include <Arduino.h>

#define SENSOR_OUT    WB_IO3
#define SENSOR_EN     WB_IO4
#define BLUE_LED      LED_BLUE


void RAK12013_test(unsigned long timeout)
{
  pinMode (SENSOR_EN, OUTPUT);
  digitalWrite(SENSOR_EN, HIGH); // Sensor disable input (low = disable)

  pinMode (SENSOR_OUT, INPUT_PULLDOWN);
  pinMode (BLUE_LED, OUTPUT);
  digitalWrite(BLUE_LED, LOW);

  unsigned long time_now = millis();
  while ( (millis() - time_now) < timeout)
  {
    if ((digitalRead(SENSOR_OUT) == HIGH) )
    {
      digitalWrite(BLUE_LED, HIGH);
      Serial.printf("RAK12013 Test OK!\n");
      return;
    }
//    if ((digitalRead(SENSOR_OUT) == LOW))
//    {
//      digitalWrite(BLUE_LED, LOW);
//      Serial.printf("RAK12013 Test Failed!\n");
//      break;
//    }
  }
  Serial.printf("RAK12013 Test Failed!\n");
}
#endif
