#ifdef RAK12047_MODULE

#include <SensirionI2CSgp40.h> // Click here to get the library: http://librarymanager/All#SensirionI2CSgp40
#include <Wire.h>

SensirionI2CSgp40 sgp40;

void RAK12047_test(unsigned long timeout)
{
  uint16_t error;
  uint16_t serialNumber[3];
  uint8_t serialNumberSize = 3;
  
  Wire.begin();
  sgp40.begin(Wire);

  error = sgp40.getSerialNumber(serialNumber, serialNumberSize);
  if (error) 
  {
    Serial.printf("RAK12047 Test Failed\n");
    return;
  } 
  else 
  {
    Serial.print("Serial Number:");
    Serial.print("0x");
    for (size_t i = 0; i < serialNumberSize; i++) 
    {
      uint16_t value = serialNumber[i];
      Serial.print(value < 4096 ? "0" : "");
      Serial.print(value < 256 ? "0" : "");
      Serial.print(value < 16 ? "0" : "");
      Serial.print(value, HEX);
    }
    Serial.println();
    Serial.printf("RAK12047 Test OK\n");
    return;
  }
}
#endif
