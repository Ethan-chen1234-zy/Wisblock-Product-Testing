#ifdef RAK12034_MODULE

#include "Rak_BMX160.h" //  library:  http://librarymanager/All#RAK12034_BMX160

RAK_BMX160 bmx160;

void RAK12034_test(unsigned long timeout)
{
  if (bmx160.begin() != true) 
  {
    Serial.printf("RAK12034 Test Failed\n");
    return;
  }
  else
  {
    Serial.printf("RAK12034 Test OK\n");
    return;
  }
}
#endif
