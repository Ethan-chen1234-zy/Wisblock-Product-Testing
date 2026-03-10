#ifdef RAK1902_MODULE

#include "Production_test_configure.h"
#include <Arduino_LPS22HB.h>  // Click here to get the library: http://librarymanager/All#Arduino_LPS22HB

/***********************************LPS22HB****RAK1902***test***start****************************/
void lps22hb_get() {
  // read the sensor value
  float pressure = BARO.readPressure();

  // print the sensor value
  Serial.print("Pressure = ");
  Serial.print(pressure);
  Serial.println(" kPa");
}
void LPS22HB_test(unsigned long timeout)
{
  /* LPS22HB init */
  if (!BARO.begin()) {
    //Serial.println("Failed to initialize pressure sensor!");
    Serial.printf("-----------RAK1902 Test Failed!-----------\n");
  }
  else
  {
    Serial.printf("\n-----------RAK1902 Test OK!-----------\n");
    lps22hb_get();
    Serial.printf("-----------RAK1902 Test OK!-----------\n");
  }
}
/***********************************LPS22HB****RAK1902****test****end**************************/

#endif
