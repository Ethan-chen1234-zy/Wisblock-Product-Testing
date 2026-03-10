#ifdef RAK14004_MODULE

#include "Production_test_configure.h"
#include "Arduino.h"
#define SLAVE_I2C_ADDRESS_DEFAULT            0x5F
// Sensor Register Addresses
#define SENSOR_GET_KEYPAD        0x01  // (r)   2 bytes
#define SENSOR_GET_I2C_ADDRESS   0x02  // (r)   1 bytes
#define SENSOR_SET_I2C_ADDRESS   0x03  // (w)   1 bytes
#define SENSOR_GET_VERSION       0x04  // (r)   1 bytes      
#define KEYPAD_VERSION           0x02

uint8_t InterruptFlag = 0;



/*brief: IIC Read data*/
uint8_t readflag = 0;
void read_from_Atmega328p(uint8_t reg, uint8_t *data, uint8_t length)
{
  Wire.beginTransmission(SLAVE_I2C_ADDRESS_DEFAULT);
  Wire.write(reg);
  Wire.endTransmission();    // stop transmitting
  delay(20);
  Wire.requestFrom(SLAVE_I2C_ADDRESS_DEFAULT, length);
  int i = 0;
  while ( Wire.available() ) // slave may send less than requested
  {
    data[i++] = Wire.read(); // receive a byte as a proper uint8_t
    readflag = 1;
  }
}

/*brief: IIC write data*/
void write_to_Atmega328p(uint8_t reg, uint8_t data)
{
  Wire.beginTransmission(SLAVE_I2C_ADDRESS_DEFAULT);
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission();    // stop transmitting
}

void INTCallBack(void)
{
  InterruptFlag = 1;
}

void RAK14009_test(unsigned long timeout)
{
  attachInterrupt(WB_IO6, INTCallBack, RISING); // Enable interrupts.
  Serial.println("3*3 Keypad");
  Wire.begin();
  uint8_t data = 0;
  read_from_Atmega328p(SENSOR_GET_VERSION, &data, 1);
  if (data != KEYPAD_VERSION)
  {
    Serial.println("RAK14004 Test Failed!");
    return;
  }
  unsigned long time_now = millis();
  String str_end = "RAK14004_End";
  String snd = "";
  while ( (millis() - time_now) < timeout)
  {
    KeyPad_Print(3, 3);
    uint8_t time_count = 100;
    while (time_count--)
    {
      if (Serial.available() > 0)
      {
        snd += char(Serial.read());
      }
      delay(1);
    }
    if (snd == str_end)
    {
      Serial.println("RAK14009 Test Over");
      return;
    }
    delay(100);
  }
}

void RAK14010_test(unsigned long timeout)
{
  attachInterrupt(WB_IO6, INTCallBack, RISING); // Enable interrupts.
  Serial.println("3*4 Keypad");
  Wire.begin();
  uint8_t data = 0;
  read_from_Atmega328p(SENSOR_GET_VERSION, &data, 1);
  if (data != KEYPAD_VERSION)
  {
    Serial.println("RAK14004 Test Failed!");
    return;
  }
  unsigned long time_now = millis();
  String str_end = "RAK14004_End";
  String snd = "";
  while ( (millis() - time_now) < timeout)
  {
    KeyPad_Print(3, 4);
    uint8_t time_count = 100;
    while (time_count--)
    {
      if (Serial.available() > 0)
      {
        snd += char(Serial.read());
      }
      delay(1);
    }
    if (snd == str_end)
    {
      Serial.println("RAK14010 Test Over");
      return;
    }
    delay(100);
  }
}

void RAK14011_test(unsigned long timeout)
{
  attachInterrupt(WB_IO6, INTCallBack, RISING); // Enable interrupts.
  Serial.println("4*4 Keypad");
  Wire.begin();
  uint8_t data = 0;
  read_from_Atmega328p(SENSOR_GET_VERSION, &data, 1);
  if (data != KEYPAD_VERSION)
  {
    Serial.println("RAK14004 Test Failed!");
    return;
  }
  unsigned long time_now = millis();
  String str_end = "RAK14004_End";
  String snd = "";
  while ( (millis() - time_now) < timeout)
  {
    KeyPad_Print(4, 4);
    uint8_t time_count = 100;
    while (time_count--)
    {
      if (Serial.available() > 0)
      {
        snd += char(Serial.read());
      }
      delay(1);
    }
    if (snd == str_end)
    {
      Serial.println("RAK14011 Test Over");
      return;
    }
    delay(100);
  }
}

void KeyPad_Print(uint8_t x_len, uint8_t y_len)
{
  if (InterruptFlag == 1)
  {
    uint8_t rDataBuf[8] = {0};
    uint8_t PrintDataBuf[2] = {0};
    uint8_t rDataFlag[2] = {0};
    read_from_Atmega328p(SENSOR_GET_KEYPAD, rDataBuf, x_len);
    if (readflag == 1)
    {
      Serial.println("-----------------------");
      for (uint8_t aCount = 0; aCount < x_len; aCount++)
      {
        for (uint8_t bCount = 0; bCount < y_len; bCount++ )
        {
          uint8_t cmp = (rDataBuf[aCount] >> bCount) & 0x01;
          if (cmp == 0x01)
          {
            rDataFlag[0]++;
            if (rDataFlag[0] <= 2)
            {
              rDataFlag[1]++;
              PrintDataBuf[rDataFlag[0] - 1] = aCount * y_len + bCount + 1;
            }
            else
            {
              rDataFlag[1] = 0;
              Serial.println("Error please do not press more than two buttons at the same time ");
              return;
            }
          }
        }
      }
      readflag = 0;
    }
    for (uint8_t pCount = 0; pCount < rDataFlag[1]; pCount++)
    {
      Serial.printf("K%d pressed\r\n", PrintDataBuf[pCount]);
    }
    Serial.println("-----------------------");
    Serial.println();
    InterruptFlag = 0;
  }
}
#endif
