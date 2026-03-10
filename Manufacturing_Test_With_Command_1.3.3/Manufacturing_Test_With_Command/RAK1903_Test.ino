#ifdef RAK1903_MODULE

#include "Production_test_configure.h"
#include <ClosedCube_OPT3001.h> // Click here to get the library: http://librarymanager/All#OPT3001

/*****************************OPT3001****RAK1903**test***start*************************************/
ClosedCube_OPT3001 opt3001;
#define OPT3001_ADDRESS 0x44

void printError(String text, OPT3001_ErrorCode error) {
  Serial.print(text);
  Serial.print(": [ERROR] Code #");
  Serial.println(error);
}

void printResult(String text, OPT3001 result) {
  if (result.error == NO_ERROR) {
    Serial.print(text);
    Serial.print(": ");
    Serial.print(result.lux);
    Serial.println(" lux");
  }
  else {
    printError(text, result.error);
  }
}
void opt3001_get() {
  OPT3001 result = opt3001.readResult();
  if (result.error == NO_ERROR) {
    Serial.print("OPT3001");
    Serial.print(": ");
    Serial.print(result.lux);
    Serial.println(" lux");

    uint16_t luminosity = result.lux;
  }
  else {
    printError("OPT3001", result.error);
  }
}

void configureSensor() {
  OPT3001_Config newConfig;

  newConfig.RangeNumber = B1100;
  newConfig.ConvertionTime = B0;
  newConfig.Latch = B1;
  newConfig.ModeOfConversionOperation = B11;

  OPT3001_ErrorCode errorConfig = opt3001.writeConfig(newConfig);
  if (errorConfig != NO_ERROR)
    //printError("OPT3001 configuration", errorConfig);
    Serial.printf("-----------OPT3001 Configuration Failed!-----------\n");
  else
    OPT3001_Config sensorConfig = opt3001.readConfig();
}
void OPT3001_test(unsigned long timeout)
{
  opt3001.begin(OPT3001_ADDRESS);
  //if(opt3001.readManufacturerID() == && opt3001.readDeviceID() == )
  configureSensor();
  if (opt3001.readDeviceID() == 0x3001)
  {
    Serial.printf("\n-----------RAK1903 Test OK!-----------\n");
    opt3001_get();
    Serial.printf("-----------RAK1903 Test OK!-----------\n");
  }
  else
  {
    Serial.printf("-----------RAK1903 Test Failed!-----------\n");
  }
}
/*****************************OPT3001****RAK1903**test***end*************************************/

#endif
