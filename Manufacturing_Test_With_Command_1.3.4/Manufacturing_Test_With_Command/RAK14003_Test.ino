#ifdef RAK14003_MODULE

#include <Wire.h>
//#include "Adafruit_MCP23017.h"  //http://librarymanager/All#Adafruit_MCP23017  同 RAK13003_Test.ino ,版本2.3.2 头文件名称变更 Adafruit_MCP23X17.h 
#include "Adafruit_MCP23X17.h"

#define IIC_ADDRESS 0X04

//Adafruit_MCP23017 mcp;
Adafruit_MCP23X17 mcp;  // 更正 2026.1.21

void RAK14003_test(unsigned long timeout)
{
  // Reset device
  pinMode(WB_IO4, OUTPUT);
  digitalWrite(WB_IO4, 1);
  delay(10);
  digitalWrite(WB_IO4, 0);
  delay(10);
  digitalWrite(WB_IO4, 1);
  delay(10);
  //mcp.begin(IIC_ADDRESS, &Wire); // use default address 0.
  mcp.begin_I2C(IIC_ADDRESS, &Wire);    //2026.1.21

  for (int i = 0 ; i < 16 ; i++)
  {
    mcp.pinMode(i, OUTPUT);     // Set pins as output.
    mcp.digitalWrite(i, LOW);  // Turn on all LEDs.
  }
  delay(1000);
  for (int i = 0 ; i < 16 ; i++)
  {
    mcp.digitalWrite(i, HIGH);  // Turn off all LEDs.
  }
  delay(1000);
  for (int i = 0 ; i < 16 ; i++)
  {
    mcp.digitalWrite(i, LOW);  // Turn on all LEDs.
  }
  delay(1000);
  for (int i = 0 ; i < 16 ; i++)
  {
    mcp.digitalWrite(i, HIGH);  // Turn off all LEDs.
  }
}
#endif
