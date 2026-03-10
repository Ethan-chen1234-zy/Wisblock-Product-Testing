#ifdef RAK12031_MODULE

#include "Production_test_configure.h"
#define SINGAL_PIN            WB_IO1  // Connect with TBF out put pin.  Mount in SLOT A.
uint8_t g_pulse_flag = 0;
void RAK12031_test(unsigned long timeout)
{
  pinMode(SINGAL_PIN, INPUT); // Connect with TBF out put pin.
  attachInterrupt(digitalPinToInterrupt(SINGAL_PIN) , pulse_INT_call_back , FALLING); // Enable interrupts.FALLING CHANGE
  delay(100);
  unsigned long time_now = millis();
  while ( (millis() - time_now) < timeout)
  {
    //    if (g_pulse_flag > 0 )
    //    {
    //      Serial.println("RAK12031 Test OK!");
    //      g_pulse_flag = 0;
    //      return;
    //    }
    if ( digitalRead(SINGAL_PIN) == LOW )
    {
      Serial.println("RAK12031 Test OK!");
      return;
    }
  }
  Serial.println("RAK12031 Test Failed!");
}
void pulse_INT_call_back()
{
  g_pulse_flag ++;
}


#endif
