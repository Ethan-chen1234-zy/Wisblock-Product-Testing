#ifdef RAK12035_MODULE

#include <Wire.h>

#define SOILMOISTURESENSOR_VERSION      0x02

#define SLAVE_I2C_ADDRESS_DEFAULT         0x20
//Soil Moisture Sensor Register Addresses
#define SOILMOISTURESENSOR_GET_CAPACITANCE   0x01   // (r)   2 bytes
#define SOILMOISTURESENSOR_GET_I2C_ADDRESS   0x02   // (r)   1 bytes
#define SOILMOISTURESENSOR_SET_I2C_ADDRESS   0x03   // (w)   1 bytes
#define SOILMOISTURESENSOR_GET_VERSION       0x04   // (r)   1 bytes

void read_from_ttiny441(uint8_t reg, uint8_t *data,uint8_t length)
{
  Wire.beginTransmission(SLAVE_I2C_ADDRESS_DEFAULT); 
  Wire.write(reg);        // sends five bytes
  Wire.endTransmission();    // stop transmitting
  delay(20);
  Wire.requestFrom(SLAVE_I2C_ADDRESS_DEFAULT,length);
  int i = 0;
  while ( Wire.available() ) // slave may send less than requested
  {
    data[i++]= Wire.read(); // receive a byte as a proper uint8_t
  }  
}

void write_to_ttiny441(uint8_t reg, uint8_t data)
{
  Wire.beginTransmission(SLAVE_I2C_ADDRESS_DEFAULT); 
  Wire.write(reg);        // sends five bytes
  Wire.write(data);
  Wire.endTransmission();    // stop transmitting
}

void RAK12035_test(unsigned long timeout)
{
  pinMode(WB_IO2, OUTPUT);
  digitalWrite(WB_IO2, HIGH);

  pinMode(WB_IO4, OUTPUT);
  digitalWrite(WB_IO4, LOW);
  delay(1000);
  digitalWrite(WB_IO4, HIGH); // 需要软件复位一下，否则复位-->发送test命令-->复位后下位单片机会出现不工作的情况。

  pinMode(WB_IO5, INPUT); 
  delay(1000);
  Wire.begin();
  
  uint8_t ID = 0;
  read_from_ttiny441(SOILMOISTURESENSOR_GET_VERSION,&ID,1);
  Serial.print("Sensor Firmware version: ");
  Serial.println(ID,HEX);
  if(ID != SOILMOISTURESENSOR_VERSION)
  {
    Serial.printf("RAK12023 & RAK12035 Test Failed!\n");
    return ;
  }
  delay(1000);

  uint8_t data[2] = {0}; 
  uint16_t Capacitance = 0;
  read_from_ttiny441(SOILMOISTURESENSOR_GET_CAPACITANCE,data,2); 
  Capacitance = (((uint16_t)data[0]) << 8) | ((uint16_t)data[1]);
  Serial.print("Soil Moisture Capacitance: ");
  Serial.println(Capacitance);
  Serial.printf("RAK12023 & RAK12035 Test OK!\n");
}

#endif
