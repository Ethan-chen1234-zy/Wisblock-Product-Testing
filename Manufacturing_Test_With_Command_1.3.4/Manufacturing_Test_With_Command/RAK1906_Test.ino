#ifdef RAK1906_MODULE

#include "Production_test_configure.h"

/*
#include <ClosedCube_BME680.h>  // Click here to get the library: http://librarymanager/All#ClosedCube_BME680_Arduino

ClosedCube_BME680 bme680;

void bme680_get() {
  double temp = bme680.readTemperature();
  double pres = bme680.readPressure();
  double hum = bme680.readHumidity();

  Serial.print("T=");
  Serial.print(temp);
  Serial.print("C, RH=");
  Serial.print(hum);
  Serial.print("%, P=");
  Serial.print(pres);
  Serial.print("hPa");

  uint32_t gas = bme680.readGasResistance();

  Serial.print(", G=");
  Serial.print(gas);
  Serial.print(" Ohms");
  Serial.println();

  bme680.setForcedMode();
}
void bme680_test(unsigned long timeout) {
  Wire.begin();
  bme680.init(0x76); // I2C address: 0x76
  bme680.reset();

  if (bme680.getChipID() == 0x61) //BME680 Chip_ID 0x61
  {
    // oversampling: humidity = x1, temperature = x2, pressure = x16
    bme680.setOversampling(BME680_OVERSAMPLING_X1, BME680_OVERSAMPLING_X2, BME680_OVERSAMPLING_X16);
    bme680.setIIRFilter(BME680_FILTER_3);
    bme680.setGasOn(300, 100); // 300 degree Celsius and 100 milliseconds

    bme680.setForcedMode();
    Serial.printf("-----------RAK1906 Test OK!-----------\n");
    bme680_get();
    Serial.printf("-----------RAK1906 Test OK!-----------\n");
  }
  else
  {
    Serial.printf("-----------RAK1906 Test Failed!-----------\n");
  }
}*/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h> // Click to install library: http://librarymanager/All#Adafruit_BME680

Adafruit_BME680 bme;
// Might need adjustments
#define SEALEVELPRESSURE_HPA (1010.0)

void bme680_get()
{
  Serial.print("Temperature = ");
  Serial.print(bme.temperature);
  Serial.println(" *C");

  Serial.print("Pressure = ");
  Serial.print(bme.pressure / 100.0);
  Serial.println(" hPa");

  Serial.print("Humidity = ");
  Serial.print(bme.humidity);
  Serial.println(" %");

  Serial.print("Gas = ");
  Serial.print(bme.gas_resistance / 1000.0);
  Serial.println(" KOhms");

  Serial.println();
}

void bme680_test(unsigned long timeout) 
{
  Wire.begin();

  if (!bme.begin(0x76)) 
  {
    Serial.printf("-----------RAK1906 Test Failed!-----------\n");
    return;
  }
  else
  {
    Serial.printf("-----------RAK1906 Test OK!-----------\n");
  }

  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms

  delay(100);
  if (! bme.performReading())
  {
    Serial.println("Failed to perform reading :(");
  }
  bme680_get();
}


/************************************BME680*******RAK1906**test****end***************************/

#endif
