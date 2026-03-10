#ifdef  RAK12027_MODULE

#include "RAK12027_D7S.h" // Click here to get the library: http://librarymanager/All#RAK12027_D7S

boolean RAK12027isConnected()
{
  Wire.beginTransmission((uint8_t)D7S_DEV_ADDRESS);
  if (Wire.endTransmission() != 0)
  {
    return (false); //Sensor did not ACK
  }
  else
  {
    return (true);
  }
}

void RAK12027_test(unsigned long time_out)
{
  pinMode(WB_IO2, OUTPUT);
  digitalWrite(WB_IO2, HIGH); // Power up the D7S.  
  
  Wire.begin();
  if(RAK12027isConnected())
  {
    Serial.printf("RAK12027 Test OK!\n");
  }
  else
  {
    Serial.printf("RAK12027 Test Failed!\n");
  }
}

#endif
