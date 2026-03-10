#ifdef RAK12011_MODULE

#include "Production_test_configure.h"
#include <Adafruit_LPS2X.h>
#include <Adafruit_Sensor.h>  // Click here to get the library: http://librarymanager/All#Adafruit_LPS2X

Adafruit_LPS22 g_lps22hb;

void RAK12011_get() {
  // read the sensor value
  g_lps22hb.setDataRate(LPS22_RATE_10_HZ);
  sensors_event_t temp;
  sensors_event_t pressure;
  delay(100);
  g_lps22hb.getEvent(&pressure, &temp);
  Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.println(" degrees C");
  Serial.print("Pressure: "); Serial.print(pressure.pressure); Serial.println(" hPa");
  Serial.println("");
}
void RAK12011_test(unsigned long timeout)
{
  /* LPS22HB init */
  if (!g_lps22hb.begin_I2C(0x5d))
  {
    Serial.printf("-----------RAK12011 Test Failed!-----------\n");
  }
  else
  {
    Serial.printf("\n-----------RAK12011 Test OK!-----------\n");
    RAK12011_get();
    Serial.printf("-----------RAK12011 Test OK!-----------\n");
  }
}

#endif
