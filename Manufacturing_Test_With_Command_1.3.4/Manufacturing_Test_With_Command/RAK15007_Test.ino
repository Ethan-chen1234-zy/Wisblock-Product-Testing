#ifdef RAK15007_MODULE

#include "RAK15007_CY15B108QN.h"  //http://librarymanager/All#RAK15007_CY15B108QN v1.0.0
/*
* @note 由于库与库之间宏定义名有冲突， 修改RAK_SPI.h/RAK_SPI.cpp/RAK15007_CY15B108QN.cpp 中定义  
* 修改SPIClock ==> RAK15007_RAK15007_SPIClock,修改 SPI_USER ==> RAK15007_SPI_USER ,修改 RAK_SPI => RAK_SPI_15007
*/


#define FRAM_WP_PIN WB_IO1   //SlotA installation, please do not use it on SLOTB
//#define FRAM_WP_PIN WB_IO3 //SlotC installation.
//#define FRAM_WP_PIN WB_IO5 //SlotD installation.

#define FRAM_8M_SIZE  0x100000
uint8_t fram_cy15b108_CS = SS;
RAK_FRAM_CY15B108QN fram_cy15b108 = RAK_FRAM_CY15B108QN(fram_cy15b108_CS);

void RAK15007_init(void)
{
  pinMode(WB_IO2, OUTPUT);
  digitalWrite(WB_IO2, HIGH); // Enable power supply.
  delay(300);
  pinMode(FRAM_WP_PIN, OUTPUT);
  digitalWrite(FRAM_WP_PIN, HIGH);
}

void RAK15007_test(unsigned long timeout)
{
  RAK15007_init();
  if (fram_cy15b108.begin()) 
  {
    Serial.printf("RAK15007 Test OK!\n");
  } 
  else 
  {
    Serial.printf("RAK15007 Test Failed!\n");
  }
}
#endif
