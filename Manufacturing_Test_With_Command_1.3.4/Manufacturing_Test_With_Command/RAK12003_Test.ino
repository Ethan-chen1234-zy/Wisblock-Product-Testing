#ifdef RAK12003_MODULE

#include "Production_test_configure.h"
#include "SparkFun_MLX90632_Arduino_Library.h"   // Click here to get the library: http://librarymanager/AllSparkFun_MLX90632_Arduino_Library

#define MLX90632_ADDRESS 0x3A
MLX90632 RAK_TempSensor;

void RAK12003_test(unsigned long time_out)
{
  float sensor_temp = 0;
  unsigned long time_now = millis();
  while ( (millis() - time_now) < time_out)
  {
    TwoWire &wirePort = Wire;
    MLX90632::status returnError;
    Wire.begin(); //I2C init
    if (RAK_TempSensor.begin(MLX90632_ADDRESS, wirePort, returnError) == true) //MLX90632 init
    {
      sensor_temp = RAK_TempSensor.getObjectTemp(returnError); //Get the temperature of the sensor
      if (returnError == MLX90632::SENSOR_SUCCESS)
      {
        sensor_temp = RAK_TempSensor.getSensorTemp(); //Get the temperature of the sensor
        Serial.print("Sensor temperature: ");
        Serial.print(sensor_temp, 2);
        Serial.printf(" C\n");
        Serial.printf("RAK12003 Test OK\n");
        break;
      }
      else
      {
        Serial.printf("RAK12003 Test Failed\n");
        break;
      }
    }
    else
    {
      Serial.printf("RAK12003 Test Failed\n");
      break;
    }
  }
}

#endif
