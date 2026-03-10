#ifdef RAK13006_MODULE
/*
 * @note 由于库与库之间宏定义名有冲突，故需要修改 Rak_CAN.cpp 中 SPI_USER 的宏名称为 CAN_SPI_USER .
 */
#include "Rak_CAN.h"   //library: http://librarymanager/All#RAK13006-MCP2518-library

/*
 * 实现 CAN Slaver 代码.
 */
void RAK13006_test(unsigned long timeout)
{
  pinMode(WB_IO2, OUTPUT);
  digitalWrite(WB_IO2, HIGH); // Enable power supply.
  delay(300);

  Rak_Can.init();

  RAK_CAN_Settings settings (RAK_CAN_Settings::OSC_40MHz, 125 * 1000) ; // CAN bit rate 125 kb/s
  settings.mRequestedMode = RAK_CAN_Settings::Normal20B ;
  const uint32_t errorCode = Rak_Can.begin (settings, [] { Rak_Can.isr () ; }) ;
  if (errorCode == 0) {
    Serial.print ("Bit Rate prescaler: ") ;
    Serial.println (settings.mBitRatePrescaler) ;
    Serial.print ("Phase segment 1: ") ;
    Serial.println (settings.mPhaseSegment1) ;
    Serial.print ("Phase segment 2: ") ;
    Serial.println (settings.mPhaseSegment2) ;
    Serial.print ("SJW:") ;
    Serial.println (settings.mSJW) ;
    Serial.print ("Actual bit rate: ") ;
    Serial.print (settings.actualBitRate ()) ;
    Serial.println (" bit/s") ;
    Serial.print ("Exact bit rate ? ") ;
    Serial.println (settings.exactBitRate () ? "yes" : "no") ;
    Serial.print ("Sample point: ") ;
    Serial.print (settings.samplePointFromBitStart ()) ;
    Serial.println ("%") ;
    Serial.println() ;
  } else {
    Serial.print ("Configuration error 0x") ;
    Serial.println (errorCode, HEX) ;
  }
  delay(100);
  
  unsigned long time_now = millis();
  while ( (millis() - time_now) < timeout)
  {
    CANMessage frame ;
#if BOARDFLAG
  if (Rak_Can.IntrruptFlag == 1)
#endif
    {
      Rak_Can.isr_core();
      if (Rak_Can.receive (frame)) 
      {
        if (!frame.rtr && (!frame.ext) && (frame.id == 0x05)) 
        {
//          Serial.print ("Received: ") ;
//          for (int i = 0; i < 8; i++)
//          {
//            Serial.print(frame.data[i]);
//          }
//          Serial.printf("\r\nframe.id = %d\r\n",frame.id);
          Serial.printf("RAK13006 Test OK!\n");
          return;
        }
      }
    }
#if BOARDFLAG
    Rak_Can.IntrruptFlag = 0;
#endif
  }
  Serial.printf("RAK13006 Test Failed!\n");
}

#endif
