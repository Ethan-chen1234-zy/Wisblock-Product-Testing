#ifdef RAK12039_MODULE

#include "RAK12039_PMSA003I.h"   // Click here to get the library: http://librarymanager/All#RAK12039_PM_Sensor

RAK_PMSA003I PMSA003I;

#define SET_PIN   WB_IO6

void RAK12039_test(unsigned long timeout)
{
  pinMode(WB_IO2, OUTPUT);
  digitalWrite(WB_IO2, HIGH); 

  pinMode(SET_PIN, OUTPUT);
  digitalWrite(SET_PIN, HIGH);  

  Wire.begin();
  if(!PMSA003I.begin()) 
  {
    Serial.printf("RAK12039 Test Failed\n");
    return;
  }
  delay(200);
  PMSA_Data_t data;
  
  if (PMSA003I.readDate(&data)) 
  {
    Serial.println("Atmospheric environment:");
    Serial.print("PM2.5: "); 
    Serial.print(data.pm25_env);
    Serial.println(" [µg/𝑚3]"); 
    if((data.pm25_env < 0) || (data.pm25_env > 400))
    {
      Serial.printf("RAK12039 Test Failed\n");
      return;
    }
    else 
    {
      Serial.printf("RAK12039 Test OK\n");
      return;
    }
  }
  else
  {
    Serial.println("PMSA003I read failed!");
    Serial.printf("RAK12039 Test Failed\n");
    return;
  }
}
#endif
