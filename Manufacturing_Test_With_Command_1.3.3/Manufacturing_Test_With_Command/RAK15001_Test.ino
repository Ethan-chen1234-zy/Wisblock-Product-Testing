#ifdef RAK15001_MODULE

#include <SPI.h>

void RAK15001_test(unsigned long timeout)
{
  pinMode(SS, OUTPUT);
  digitalWrite(SS, HIGH);
  
  uint8_t RDID[3];
 
  SPI.begin();

  digitalWrite(SS, LOW);
  SPI.transfer(0x9f);

  for(uint8_t i=0 ; i < 3 ; i++)
  {
    RDID[i] = SPI.transfer(0x00);
    //Serial.printf("RDID[%d] = 0X%x\r\n",i,RDID[i]);
    delay(10);
  }
  digitalWrite(SS, HIGH);

  if( RDID[0] == 0xC8 && RDID[1] == 0x40 && RDID[2] == 0x15)
  {
    Serial.printf("RAK15001 Test OK!\r\n");
  }
  else 
  {
    Serial.printf("RAK15001 Test Failed!\r\n");
  }
}

#endif
