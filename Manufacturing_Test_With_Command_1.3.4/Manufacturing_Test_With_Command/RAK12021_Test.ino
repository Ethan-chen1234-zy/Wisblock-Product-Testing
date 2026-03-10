#ifdef RAK12021_MODULE

#include "Production_test_configure.h"
#include "TCS3772.h"    // Click to install library: http://librarymanager/All#RAKwireless-RAK12021-TCS37725

void RAK12021_test(unsigned long timeout)
{
  TCS3772 tcs3772;
  Wire.begin();
  unsigned long time_now = millis();
  while ( (millis() - time_now) < timeout)
  {
    if (tcs3772.begin() == true)
    {
      Serial.printf("RAK12021 Test OK!\n");
      break;
    }
    else
    {
      Serial.printf("RAK12021 Test Failed!\n");
      break;
    }
  }
}
#endif
