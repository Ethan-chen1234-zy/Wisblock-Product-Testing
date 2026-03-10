#ifdef RAK16002_MODULE

#include "Production_test_configure.h"
#include "LTC2941.h"  //Click here to get the library: http://librarymanager/All#GROVE-Coulomb_Counter

void RAK16002_init(void)
{
  pinMode(WB_IO2, OUTPUT);
  digitalWrite(WB_IO2, HIGH); // Enable power supply.
  Wire.begin();
}

void RAK16002_test(unsigned long timeout)
{
  uint8_t id = 0;
  RAK16002_init();
  id = ltc2941.getStatus();
  if ((id & 0x80 ) == 0x80)
  {
    Serial.printf("RAK16002 Test OK\n");
  }
  else
  {
    Serial.printf("RAK16002 Test Failed!\n");
  }  
}

#endif
