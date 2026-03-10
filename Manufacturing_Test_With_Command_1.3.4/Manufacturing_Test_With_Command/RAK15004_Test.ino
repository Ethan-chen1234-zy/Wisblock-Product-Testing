#ifdef RAK15004_MODULE

#include "RAK1500x_MB85RC.h"  // Click here to get the library: http://librarymanager/All#RAK1500x_MB85RC

#define DEV_ADDR    MB85RC512_DEV_ADDRESS   // Uncomment if using RAK15004.

/*
 * @note If installed in SlotB.
 *       Since IO2 is the power supply enable pin level is high.
 *       Only read operation can be performed on this slot.
 */
#define WP_PING   WB_IO1 // SlotA installation.
//#define WP_PING   WB_IO3 // SlotC installation.
//#define WP_PING   WB_IO5 // SlotD installation.

RAK_MB85RC SENSOR;

void RAK15004_init(void)
{
  pinMode(WB_IO2, OUTPUT);
  digitalWrite(WB_IO2, HIGH);
  
  pinMode(WP_PING, OUTPUT);
  digitalWrite(WP_PING, LOW);
}

void RAK15004_test(unsigned long timeout)
{
  RAK15004_init();
  Wire.begin();
  if(SENSOR.begin(Wire , DEV_ADDR) == false) 
  {
    Serial.printf("RAK15004 Test Failed\n");
  }
  else
  {
    Serial.printf("RAK15004 Test OK\n");
  }
}
#endif
