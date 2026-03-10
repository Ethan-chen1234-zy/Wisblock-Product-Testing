#ifdef  RAK12020_MODULE

#include <Adafruit_Sensor.h>
#include "Adafruit_TSL2591.h" // Click to install library: http://librarymanager/All#Adafruit_TSL2591

void RAK12020_test(unsigned long time_out)
{
  Adafruit_TSL2591 TSL2591 = Adafruit_TSL2591(2591);
  
  pinMode(WB_IO2, OUTPUT);
  digitalWrite(WB_IO2, HIGH); 

  if (TSL2591.begin() == false)
  {
    Serial.printf("RAK12020 Test Failed!\n"); 
  }
  else
  {
    Serial.printf("RAK12020 Test OK!\n");
  }
}

#endif
