#ifdef RAK5802_MODULE

#include "Production_test_configure.h"
//#include <ArduinoModbus.h>    // Click here to get the library: http://librarymanager/All#ArduinoModbus

/***************************************RAK5802K1904**test**start*********************************/
#include <Wire.h>
 
#include <ArduinoRS485.h> //Click here to get the library: http://librarymanager/All#ArduinoRS485
/*void RS485test(unsigned long timeout)
{
  short id;

  if (!ModbusRTUClient.begin(9600)) {
    Serial.println("Failed to start Modbus RTU Client!");
    return;
  }


  pinMode(34, OUTPUT);
  digitalWrite(34, HIGH);

  delay(300);

  if (!ModbusRTUClient.requestFrom(1, HOLDING_REGISTERS, 0x0100, 1)) {
    //Serial.print("failed to read registers! ");
    //Serial.println(ModbusRTUClient.lastError());
  } else {
    // If the request succeeds, the sensor sends the readings, that are
    // stored in the holding registers. The read() method can be used to
    // get the raw temperature and the humidity values.
    id = ModbusRTUClient.read();
  }
  if ( 1 == id )
  {
    Serial.printf("\n-----------RAK5802 Test OK!-----------\n");
  }
  else
  {
    Serial.printf("-----------RAK5802 Test Failed!-----------\n");
  }
}*/
/***************************************RAK5802K1904**test**end*********************************/
void RS485test(unsigned long timeout)
{
  RS485.begin(9600);
  
  /* IO2 HIGH  3V3_S ON */
  pinMode(WB_IO2, OUTPUT);
  digitalWrite(WB_IO2, HIGH);
  delay(500);
  /* IO2 HIGH  3V3_S ON */
  
  // enable reception, can be disabled with: RS485.noReceive();
  RS485.receive();
  RS485.flush();
  time_t time_stamp = millis();

  /*
   * 开始测试前先读取清空串口缓存区的数据。
   */
  while (RS485.available() > 0) 
  {
    char t = RS485.read();
  }
  
  while ((millis() - time_stamp) < 5000)
  {
    if (RS485.available())
    {
      if( RS485.read() == 0xAA)
      {
        Serial.printf("\n-----------RAK5802 Test OK!-----------\n");

        
        return;
      }
  
      else
      {
        Serial.printf("-----------RAK5802 Test Failed!-----------\n");

        
        return;
      }
    }
    delay(500);
  }
  Serial.printf("-----------RAK5802 Test Failed!-----------\n");

  
}
#endif
