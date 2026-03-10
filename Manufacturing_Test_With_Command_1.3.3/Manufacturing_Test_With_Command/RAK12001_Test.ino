#ifdef RAK12001_MODULE

#include "Production_test_configure.h"

#define R307_TOUCH  WB_IO1

void RAK12001_init(void)
{
  //Sensor power switch
  pinMode(WB_IO2,OUTPUT); 
  digitalWrite(WB_IO2,HIGH);
  pinMode(R307_TOUCH,OUTPUT); 
  digitalWrite(R307_TOUCH,HIGH);
}
void RAK12001_test(unsigned long timeout)
{
  String command = "";

  uint8_t timecount = 0;
  bool loopback = false;
  
  RAK12001_init();
  time_t time_stamp = millis();
  Serial1.begin(9600);
  delay(500);
  
  time_stamp = millis();
  while ((millis() - time_stamp) < timeout)
  {
    if( loopback == false)
    {
    
      while (!Serial1.available()) 
      {
        Serial1.printf("TX");
        delay(200);
        timecount++;
        if(timecount>25)
        {
          Serial.println("Serial1 RX Time out.");
          break;
        }
      }
    
      while (Serial1.available() > 0) 
      {
        command += char(Serial1.read());
        delay(10);
      }
    
      if(String("TX") == command)
      {
        loopback = true;
        Serial.printf("RAK12001 Test OK!\n");
      }
      else
      {
        loopback = true;
        Serial.printf("RAK12001 Test Failed!\n");
      }
    }
    delay(10);
  }
  Serial.println("Test time out.");

  // 释放
  Serial1.end();
  digitalWrite(R307_TOUCH , LOW);
}
#endif
