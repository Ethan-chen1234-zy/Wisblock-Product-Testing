#ifdef RAK13003_MODULE

#include "Production_test_configure.h"
#include <Wire.h>
//#include "Adafruit_MCP23017.h"  //http://librarymanager/All#Adafruit_MCP23017    2026.1.20  版本2.3.2 头文件名称变更 Adafruit_MCP23X17.h 
#include "Adafruit_MCP23X17.h"



void RAK13003_test(unsigned long timeout)
{
  //Adafruit_MCP23017 mcp;
  //change class 2026.1.21
  Adafruit_MCP23X17 mcp;
  uint16_t Status=0xFFFF;
  pinMode(WB_IO2, OUTPUT);
  digitalWrite(WB_IO2, 1);
  
  pinMode(WB_IO4, OUTPUT);
  digitalWrite(WB_IO4, 1);
  delay(10);
  digitalWrite(WB_IO4, 0);
  delay(10);
  digitalWrite(WB_IO4, 1);
  delay(10);
  
  //mcp.begin(); // use default address 0.
  mcp.begin_I2C();  // 2026.1.21

  for(int i=0 ;i < 16 ;i+=2)
  {
    //mcp.pinMode(i, INPUT);    // PA0\PA2\PA4\PA6\PB0\PB2\PB4\PB6 input.
    //mcp.pullUp(i, HIGH);  //2.3.2版本，中已移除此方法
    mcp.pinMode(i, INPUT_PULLUP);    // configure pin for input with pull up
  }
  
  for(int i=1 ;i < 16 ;i+=2)
  {
    mcp.pinMode(i, OUTPUT);   // PA1\PA3\PA5\PA7\PB1\PB3\PB5\PB7 output.
  }

  for(int i=1 ;i < 16 ;i+=2)
  {
    mcp.digitalWrite(i, LOW);//PA1\PA3\PA5\PA7\PB1\PB3\PB5\PB7 output High.
  }

  Status = mcp.readGPIOAB(); // Read GPIO status.
  Serial.printf("IO Status = 0X%X\n",Status);

  if(Status == 0x00)
  {
    Serial.printf("RAK13003 Test OK\n");
    return;  
  } 
  else
  {
    Serial.printf("RAK13003 Test Failed\n");
    return;  
  }
  digitalWrite(WB_IO4, 0);
}
#endif
