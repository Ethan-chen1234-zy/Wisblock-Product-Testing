#ifdef RAK12037_MODULE

#include <Wire.h>
#include "SparkFun_SCD30_Arduino_Library.h" // Click here to get the library: http://librarymanager/All#SparkFun_SCD30

SCD30 airSensor;

void RAK12037_test(unsigned long timeout)
{
  uint8_t DateFlag = 0;
  float Temper = -100;
  Wire.begin();

  if (airSensor.begin() == false)
  {
    Serial.printf("RAK12037 Test Failed\n");
    return;
  }

  time_t time_stamp = millis();
  while ((millis() - time_stamp) < timeout)
  {
    delay(1000);
    if ((airSensor.dataAvailable()) && (DateFlag == 0))
    {
      DateFlag = 1;
      Serial.print("co2(ppm):");
      Serial.print(airSensor.getCO2());

      Temper = airSensor.getTemperature();
      Serial.print(" temp(C):");
      Serial.print(Temper, 1);
      
  
      Serial.print(" humidity(%):");
      Serial.print(airSensor.getHumidity(), 1);
  
      Serial.println();
      
      if(( Temper < -10 ) || ( Temper > 60 ))
      {
        Serial.printf("RAK12037 Test Failed\n");
        return;
      }
      else
      {
        Serial.printf("RAK12037 Test OK\n");
        return;
      }
    }
  }
  Serial.printf("RAK12037 Test Failed\n");
  return;
}
#endif
