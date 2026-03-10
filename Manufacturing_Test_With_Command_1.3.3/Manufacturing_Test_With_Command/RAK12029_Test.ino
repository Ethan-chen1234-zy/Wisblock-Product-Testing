#ifdef RAK12029_MODULE

#include "Production_test_configure.h"
#include "RAK12029_LDC1614.h"      // Click to install library: http://librarymanager/All#RAK12029_LDC1614

RAK12029_LDC1614_Inductive ldc;

#define INDUCTANCE   13.000
#define CAPATANCE    100.0

bool RAK12029_init(void)
{
  //Sensor power switch
  pinMode(WB_IO2, OUTPUT);
  digitalWrite(WB_IO2, HIGH);
  delay(300);

  //control chip switch
  pinMode(WB_IO5, OUTPUT);
  digitalWrite(WB_IO5, LOW);
  
  // Initialize Serial for debug output
  delay(1000);
  ldc.LDC1614_init();

  /*multiple channel use case configuration.*/
//  if (ldc.LDC1614_mutiple_channel_config(INDUCTANCE, CAPATANCE) != 0)
//  {
//    Serial.printf("RAK12029 Test Failed!\n");
//    return false;
//  }
  return true;
}
void RAK12029_test(unsigned long timeout)
{
  u16 value = 0;

  if(false == RAK12029_init())
  {
    return;  
  }
  
  ldc.IIC_read_16bit(LDC1614_READ_DEVICE_ID, &value);
  if (value == 0x3055)
  {
    Serial.printf("RAK12029 Test OK!\n");
    return;
  }
  else
  {
    Serial.printf("RAK12029 Test Failed!\n");
    return;
  }
}
#endif
