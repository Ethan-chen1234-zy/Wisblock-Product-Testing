#ifdef RAK13010_MODULE
#include "Adafruit_TinyUSB.h"
#include "RAK13010_SDI12.h"  // Click to install library: http://librarymanager/All#RAK12033-SDI12   2026.1.20 标注库有误： http://librarymanager/All#RAKwireless_SDI-12  

#define TX_PIN    WB_IO6   // The pin of the SDI-12 data bus.
#define RX_PIN    WB_IO5   // The pin of the SDI-12 data bus.
#define OE        WB_IO4   // Output enable pin, active low.

#define SENSOR_ADDRESS 'A'

RAK_SDI12 mySDI12(RX_PIN,TX_PIN,OE);

String sdiResponse = "";
String myCommand   = "";

void RAK13010_init(void)
{
  pinMode(WB_IO2, OUTPUT);
  digitalWrite(WB_IO2, HIGH); //Turn on the power switch
  delay(300);
  
  Serial.println("Opening SDI-12 bus.");
  mySDI12.begin();
  delay(500);
  mySDI12.forceListen();
}

void RAK13010_test(unsigned long timeout)
{
  String  sdiMsgStr;
  boolean sdiMsgReady = false;
  
  RAK13010_init();

  time_t time_now = millis();
  time_t time_send = millis()-1000;
  while ((millis() - time_now) < 5000)
  {
    if((millis() - time_send) > 1000)
    {
      time_send = millis();
      mySDI12.sendCommand(String(SENSOR_ADDRESS) + "M!");
      Serial.println("T: "+ String(SENSOR_ADDRESS) + "M!");
    }

    int avail = mySDI12.available();
    if (avail < 0) 
    {
      mySDI12.clearBuffer();  // Buffer is full,clear.
    }  
    else if (avail > 0) 
    {
      for (int a = 0; a < avail; a++) 
      {
        char inByte2 = mySDI12.read();
        if (inByte2 == '\n') 
        {
          sdiMsgReady = true;
        } 
        else 
        {
          sdiMsgStr += String(inByte2);
        }
      }
    }
    if (sdiMsgReady)
    {
      sdiMsgReady = false;
      Serial.println("R: "+ sdiMsgStr);
      if(sdiMsgStr.indexOf("A0219") != -1)
      {
        Serial.printf("RAK13010 Test OK\n");
        return; 
      }
      else
      {
        Serial.printf("RAK13010 Test Failed\n");
        return; 
      }
    }
  }
  Serial.printf("RAK13010 Test Failed\n");  
}
#endif
