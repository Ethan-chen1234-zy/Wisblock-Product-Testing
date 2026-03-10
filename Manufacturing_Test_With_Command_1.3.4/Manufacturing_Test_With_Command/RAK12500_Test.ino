#ifdef RAK12500_MODULE

#include <SparkFun_u-blox_GNSS_Arduino_Library.h> //http://librarymanager/All#SparkFun_u-blox_GNSS 
SFE_UBLOX_GNSS myGNSS; 

void RAK12500_test(unsigned long time_out)
{
  long latitude=0;
  long longitude=0;
  long altitude=0;
  static int GPS_InitStatus = 0;

  if(GPS_InitStatus == 0)
  {
    if(RAK12500_Init() == 0)
    {
      return;
    }
    else 
      GPS_InitStatus=1;    
  }


  unsigned long time_now = millis();
  while ( (millis() - time_now) < time_out)
  {
    latitude  = myGNSS.getLatitude();
    longitude = myGNSS.getLongitude();
    altitude  = myGNSS.getAltitude();

    if((latitude != 0) && (longitude != 0) && (altitude != 0))
    {
      Serial.println();
      Serial.print(F(" Lat: "));
      Serial.print(latitude);
      Serial.print(F(" Long: "));
      Serial.print(longitude);
      Serial.print(F(" (degrees * 10^-7)"));
      Serial.print(F(" Alt: "));
      Serial.print(altitude);
      Serial.print(F(" (mm)"));
      Serial.println();
      Serial.printf("-----------RAK12500 Test OK-------------\r\n");
      return;
    }
    latitude=0;
    longitude=0;
    altitude=0; 
    Serial.print(".");
    delay(1000);
  }
  Serial.printf("-----------RAK12500 Test Failed----------\r\n");  
}
uint8_t RAK12500_Init(void)
{
//  pinMode(WB_IO2, OUTPUT);
//  digitalWrite(WB_IO2, 0);
//  delay(1000);
//  digitalWrite(WB_IO2, 1);
  Serial1.begin(9600);
  while (!Serial1);      // Wait for user to open terminal
  if(myGNSS.begin(Serial1) != true)
  {
    Serial.printf("\r\n-----------RAK12500 Test Failed----------\r\n"); 
    return 0;
  }
  else
  {
    myGNSS.setUART1Output(COM_TYPE_UBX);      //Set the UART port to output UBX only
    myGNSS.setI2COutput(COM_TYPE_UBX);        //Set the I2C port to output UBX only (turn off NMEA noise)
    myGNSS.saveConfiguration();               //Save the current settings to flash and BBR
    Serial.printf("\r\nRAK12500 init successful!\r\n");
    return 1;
  }
}

#endif
