#ifdef RAK1901_MODULE

#include "Production_test_configure.h"
#include "SparkFun_SHTC3.h" // Click here to get the library: http://librarymanager/All#SparkFun_SHTC3

/************************************SHTC3***RAK1901****test***start*********************************/
SHTC3 mySHTC3;              // Declare an instance of the SHTC3 class

void shtc3_get(void)
{
  float Temperature, Humidity;
  mySHTC3.update();
  if (mySHTC3.lastStatus == SHTC3_Status_Nominal)             // You can also assess the status of the last command by checking the ".lastStatus" member of the object
  {

    Temperature = mySHTC3.toDegC();
    Humidity = mySHTC3.toPercent();
    Serial.print("RH = ");
    Serial.print(Humidity);                        // "toPercent" returns the percent humidity as a floating point number
    Serial.print("%, T = ");
    Serial.print(Temperature);                           // "toDegF" and "toDegC" return the temperature as a flaoting point number in deg F and deg C respectively
    Serial.println(" deg C");
  }
}
void SHTC3_test(unsigned long timeout)
{
  Wire.begin();
  Wire.setClock(400000);
  mySHTC3.begin();
  if (mySHTC3.passIDcrc)
  {
    Serial.printf("\n-----------RAK1901 Test OK!-----------\n");
    shtc3_get();
    Serial.printf("-----------RAK1901 Test OK!-----------\n");
  }
  else
  {
    Serial.printf("-----------RAK1901 Test Failed!-----------\n");
  }
}
/************************************SHTC3***RAK1901****test***end*********************************/

#endif
