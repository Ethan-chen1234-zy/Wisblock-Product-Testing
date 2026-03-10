#ifdef RAK14012_MODULE

#include "Production_test_configure.h"

#define DOUT  WB_IO5
#define EN    WB_IO6

void RAK14012_init(void)
{
  //Sensor power switch
  pinMode(DOUT,OUTPUT); 
  digitalWrite(DOUT,HIGH);
  pinMode(EN, OUTPUT);
  digitalWrite(EN, HIGH); 
}
void RAK14012_test(unsigned long timeout)
{ 
  RAK14012_init();
  time_t time_stamp = millis();
  while ((millis() - time_stamp) < timeout)
  {
  }
  Serial.println("Test time out.");
  
  digitalWrite(DOUT,LOW);
  digitalWrite(EN,LOW);
}
#endif
