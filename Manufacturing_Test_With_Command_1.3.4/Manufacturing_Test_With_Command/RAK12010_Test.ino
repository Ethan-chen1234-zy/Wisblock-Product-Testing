#ifdef RAK12010_MODULE

#include "Light_VEML7700.h"
Light_VEML7700 VMEL = Light_VEML7700();

void RAK12010_test(unsigned long timeout)
{
  if (!VMEL.begin())
  {
    Serial.println("sensor was not found. Please check wiring/power. ");
    return;
   //while (1);
  }
  VMEL.setGain(VEML7700_GAIN_1_8);
  VMEL.setIntegrationTime(VEML7700_IT_25MS);
  Serial.print(F("Gain: "));
  switch (VMEL.getGain())
  {
    case VEML7700_GAIN_1: Serial.println("1"); break;
    case VEML7700_GAIN_2: Serial.println("2"); break;
    case VEML7700_GAIN_1_4: Serial.println("1/4"); break;
    case VEML7700_GAIN_1_8: Serial.println("1/8"); break;
  }
  Serial.print(F("Integration Time (ms): "));
  switch (VMEL.getIntegrationTime())
  {
    case VEML7700_IT_25MS: Serial.println("25"); break;
    case VEML7700_IT_50MS: Serial.println("50"); break;
    case VEML7700_IT_100MS: Serial.println("100"); break;
    case VEML7700_IT_200MS: Serial.println("200"); break;
    case VEML7700_IT_400MS: Serial.println("400"); break;
    case VEML7700_IT_800MS: Serial.println("800"); break;
  }
  unsigned long time_now = millis();
  while ( (millis() - time_now) < timeout)
  {
    delay(100);
    Serial.print("Lux: ");
    Serial.println(VMEL.readLux());
  }
}
#endif
