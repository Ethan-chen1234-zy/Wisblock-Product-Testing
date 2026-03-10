#ifdef RAK14013_MODULE

#include "Production_test_configure.h"
#include <Wire.h>

//#define INT_PIN                           WB_IO6
#define INT_PIN                           WB_IO5
#define INT_LED                           LED_GREEN
#define RESET_PIN                         WB_IO4
#define SLAVE_I2C_ADDRESS_DEFAULT         0x21
//JOYSTICK Sensor Register Addresses
#define JOYSTICK_GET_DATA             0x01 // (r)   2 bytes
#define JOYSTICK_GET_I2C_ADDRESS      0x02  //(r)   1 bytes
#define JOYSTICK_SET_I2C_ADDRESS      0x03  //(w)   1 bytes
#define JOYSTICK_GET_VERSION          0x04 // (r)   1 bytes
#define JOYSTICK_SET_INT_TYPE         0x05 // (W)   1 bytes, five keys, from bit4-bit0, 0-push, 1-release. 
#define JOYSTICK_GET_X_POSITION       0x06 // (r)   2 bytes, return the analog quantity. Range:0-1024, middle position is 507(near 512)
#define JOYSTICK_GET_Y_POSITION       0x07 // (r)   2 bytes, return the analog quantity. Range:0-1024, middle position is 507(near 512)
#define JOYSTICK_SET_X_LEFT_THREHOLD  0x08 // (w)   2 bytes, set the analog quantity. Range:0-1024
#define JOYSTICK_SET_X_RIGHT_THREHOLD 0x09 // (w)   2 bytes, set the analog quantity. Range:0-1024
#define JOYSTICK_SET_Y_UP_THREHOLD    0x0A // (w)   2 bytes, set the analog quantity. Range:0-1024
#define JOYSTICK_SET_Y_DOWN_THREHOLD  0x0B // (w)   2 bytes, set the analog quantity. Range:0-1024
#define JOYSTICK_GET_X_LEFT_THREHOLD  0x0C // (r)   2 bytes, get the analog quantity. Range:0-1024
#define JOYSTICK_GET_X_RIGHT_THREHOLD 0x0D // (r)   2 bytes, get the analog quantity. Range:0-1024
#define JOYSTICK_GET_Y_UP_THREHOLD    0x0E // (r)   2 bytes, get the analog quantity. Range:0-1024
#define JOYSTICK_GET_Y_DOWN_THREHOLD  0x0F // (r)   2 bytes, get the analog quantity. Range:0-1024


uint8_t flag = 0;

//motion1       NA      NA     NA   keyE keyD keyC keyB keyA     
//bit           7       6      5     4     3    2    1    0
//motion2       NA     NA     NA    NA    x-l   x-r  y-u  y-d
//bit           7       6      5     4     3    2    1    0
uint8_t judge()
{
  uint8_t data[2] = {0};
  uint8_t motion[2]  = {0}; //we use 8 bit to record the motion
  uint16_t tmp = 0;
  uint8_t status = 0;
  
  read_from_ttiny(JOYSTICK_GET_DATA,motion,2);
  if((motion[0] & 0x01) == 0x01)
  { 
    Serial.println("KeyA Pressed");
    status = 1;
    digitalWrite(INT_LED, LOW); 
    return status;
  }
  if((motion[0] & 0x02) == 0x02)
  {
    Serial.println("KeyB Pressed");
    status = 2;
    digitalWrite(INT_LED, LOW); 
    return status;
  }  
  if((motion[0] & 0x04) == 0x04)
  {
    Serial.println("KeyC Pressed");
    status = 3;
    digitalWrite(INT_LED, LOW); 
    return status;
  }
  if((motion[0] & 0x08) == 0x08)
  {
    Serial.println("KeyD Pressed");
    status = 4;
    digitalWrite(INT_LED, LOW); 
    return status;
  }
  if((motion[0] & 0x10) == 0x10)
  {
    Serial.println("KeyE Pressed");
    status = 5;
    digitalWrite(INT_LED, LOW); 
    return status;
  }
  if((motion[1] & 0x04) == 0x04)
  {
//    tmp = 0;
//    read_from_ttiny(JOYSTICK_GET_X_POSITION,data,2);
//    tmp = (((uint16_t)data[0]) << 8) | ((uint16_t)data[1]);
//    if(tmp != 0xFFFF)
//    {
//       Serial.print("RIGHT ");
//       Serial.print("X Position is ");
//       Serial.println(tmp); 
//    }
    Serial.println("RIGHT");
    status = 6;
    digitalWrite(INT_LED, LOW); 
    return status;
  }
  if((motion[1] & 0x08) == 0x08)
  {
//    tmp = 0;
//    read_from_ttiny(JOYSTICK_GET_X_POSITION,data,2);
//    tmp = (((uint16_t)data[0]) << 8) | ((uint16_t)data[1]);
//    if(tmp != 0xFFFF)
//    {
//       Serial.print("LEFT ");
//       Serial.print("X Position is ");
//       Serial.println(tmp); 
//    }
    Serial.println("LEFT ");
    status = 7;
    digitalWrite(INT_LED, LOW); 
    return status;

  }
  if((motion[1] & 0x02) == 0x02)
  {
//    tmp = 0;
//    read_from_ttiny(JOYSTICK_GET_Y_POSITION,data,2);
//    tmp = (((uint16_t)data[0]) << 8) | ((uint16_t)data[1]);
//    if(tmp != 0xFFFF)
//    {    
//       Serial.print("UP ");
//       Serial.print("Y Position is ");
//       Serial.println(tmp); 
//    }
    Serial.println("UP ");
    status = 8;
    digitalWrite(INT_LED, LOW); 
    return status;

  }
  if((motion[1] & 0x01) == 0x01)
  {
//    tmp = 0;
//    read_from_ttiny(JOYSTICK_GET_Y_POSITION,data,2);
//    tmp = (((uint16_t)data[0]) << 8) | ((uint16_t)data[1]);
//    if(tmp != 0xFFFF)
//    {    
//       Serial.print("DOWN ");
//       Serial.print("Y Position is ");
//       Serial.println(tmp); 
//    }
    Serial.println("DOWN ");
    status = 9;
    digitalWrite(INT_LED, LOW); 
    return status;
  }  
  digitalWrite(INT_LED, LOW); 
  return status;
}

void detect()
{
  flag = 1;
  digitalWrite(INT_LED, HIGH);
}

void RAK14013_init(void) 
{
  pinMode(WB_IO2, OUTPUT);
  pinMode(RESET_PIN, OUTPUT);

  digitalWrite(WB_IO2, LOW);
  digitalWrite(RESET_PIN, LOW);
  
  delay(1000);
  
  digitalWrite(WB_IO2, HIGH); 
  digitalWrite(RESET_PIN, HIGH);
  
  pinMode(INT_LED, OUTPUT);
  digitalWrite(INT_LED, LOW);
  
  Wire.begin();  
  delay(1000);
  //here we use interrupt to notify
  pinMode(INT_PIN, INPUT);
  attachInterrupt(INT_PIN, detect, RISING);
  //set interrupt type for each key. 0 for push/ 1 for release. This step is necessary.
  uint8_t itp = 0x00; 
  write_to_ttiny(JOYSTICK_SET_INT_TYPE,&itp,1); 

  uint8_t tmp[2] = {0};
  //set threshold of x right axis MSB first
  uint16_t x_right = 600;
  tmp[0]= (uint8_t)((x_right & 0xFF00) >> 8);
  tmp[1]= (uint8_t)(x_right & 0x00FF);
  write_to_ttiny(JOYSTICK_SET_X_RIGHT_THREHOLD,tmp,2);
  
  //set threshold of x left axis MSB first
  uint16_t x_left = 400;
  tmp[0]= (uint8_t)((x_left & 0xFF00) >> 8);
  tmp[1]= (uint8_t)(x_left & 0x00FF);
  write_to_ttiny(JOYSTICK_SET_X_LEFT_THREHOLD,tmp,2);

  //set threshold of y up axis MSB first
  uint16_t y_up = 600;
  tmp[0]= (uint8_t)((y_up & 0xFF00) >> 8);
  tmp[1]= (uint8_t)(y_up & 0x00FF);  
  write_to_ttiny(JOYSTICK_SET_Y_UP_THREHOLD,tmp,2);
  
  //set threshold of y down axis MSB first
  uint16_t y_down = 400;
  tmp[0]= (uint8_t)((y_down & 0xFF00) >> 8);
  tmp[1]= (uint8_t)(y_down & 0x00FF); 
  write_to_ttiny(JOYSTICK_SET_Y_DOWN_THREHOLD,tmp,2);
}

void RAK14013_test(unsigned long timeout)
{
  uint16_t key_status = 0;
  uint8_t status = 0;
  RAK14013_init();

  Serial.printf("Start the operation...\n");

  time_t time_stamp = millis();
  while ((millis() - time_stamp) < timeout)
  {
    if(flag == 1)
    {
      status = judge();
      if (status != 0)
      {
        key_status |= 1 << status;
      }
      flag = 0;
      Serial.printf("key_status = 0X %x\n",key_status);
    }
    if(key_status == 0x3FE)
    {
      Serial.printf("RAK14013 Test OK\n");
      return;
    }
    delay(10);
  }
  Serial.printf("RAK14013 Test Time Out.\n");
  Serial.printf("RAK14013 Test Failed!\n");
}

void read_from_ttiny(uint8_t reg, uint8_t *data, uint8_t length)
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

void write_to_ttiny(uint8_t reg, uint8_t *data, uint8_t length)
{
  Wire.beginTransmission(SLAVE_I2C_ADDRESS_DEFAULT); 
  Wire.write(reg);        // sends five bytes
  for(int i=0;i<length;i++)
  {
    Wire.write(data[i]);
  }
  Wire.endTransmission();    // stop transmitting
}

#endif
