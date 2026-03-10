#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <EEPROM.h>
#include <Wire.h>


#define I2C_ADDRESS_DEFAULT           0x21
#define I2C_ADDRESS_STORE_ADDRESS     0x01
#define X_H_LEFT_THREHOLD_ADDRESS     0x02
#define X_L_LEFT_THREHOLD_ADDRESS     0x03
#define X_H_RIGHT_THREHOLD_ADDRESS    0x04
#define X_L_RIGHT_THREHOLD_ADDRESS    0x05
#define Y_H_UP_THREHOLD_ADDRESS       0x06
#define Y_L_UP_THREHOLD_ADDRESS       0x07
#define Y_H_DOWN_THREHOLD_ADDRESS     0x08
#define Y_L_DOWN_THREHOLD_ADDRESS     0x09
#define KEY_INT_TYPE_ADDRESS          0x0A
#define FIRMWARE_VERSION              0x02

//Sensor Register Addresses
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


volatile uint8_t rev[4] = {0};
//motion1       NA      NA     NA   keyE keyD keyC keyB keyA     
//bit           7       6      5     4     3    2    1    0
//motion2       NA     NA     NA    NA    x-l   x-r  y-u  y-d
//bit           7       6      5     4     3    2    1    0
volatile uint8_t motion1  = 0; //we use 5 bit to record the key
volatile uint8_t motion2  = 0; //we use 4 bit to record the direction
volatile uint16_t x_left_threshold = 200;
volatile uint16_t x_right_threshold = 900;
volatile uint16_t y_down_threshold = 200;
volatile uint16_t y_up_threshold = 900;
volatile uint8_t int_type = 0;    //five keys, from bit4-bit0, 0-push, 1-release. 

void setup() {
  pinMode(PIN_A1, INPUT);  //Key3
  pinMode(PIN_A0, INPUT);  //Key4
  pinMode(PIN_A3, INPUT); // joystick y vertical
  pinMode(PIN_A7, INPUT);  // joystick x horizontal
  pinMode(PIN_A2, INPUT); //Key2
  pinMode(PIN_B1, INPUT); //Key5
  pinMode(PIN_B2, INPUT); //Key1
  pinMode(PIN_A5, OUTPUT); //interrupt  
  digitalWrite(PIN_A5, LOW); // inactive
  //read the store from eeprom
  if(EEPROM.read(I2C_ADDRESS_STORE_ADDRESS) == 0xFF)
  {
     Wire.begin(I2C_ADDRESS_DEFAULT);   //use the default
  }
  else
  {
     Wire.begin(EEPROM.read(I2C_ADDRESS_STORE_ADDRESS));  //use store
  }
  int_type = EEPROM.read(KEY_INT_TYPE_ADDRESS);
  if(int_type == 0xFF)
  {
    int_type = 0;
  }
  uint8_t tmp1[2] = {0};
  tmp1[0] = EEPROM.read(X_H_LEFT_THREHOLD_ADDRESS);
  tmp1[1] = EEPROM.read(X_L_LEFT_THREHOLD_ADDRESS);
  x_left_threshold = ((uint16_t)tmp1[0] << 8) | ((uint16_t)tmp1[1]);
  if(x_left_threshold == 0xFFFF){x_left_threshold = 200;}
  tmp1[0] = EEPROM.read(X_H_RIGHT_THREHOLD_ADDRESS);
  tmp1[1] = EEPROM.read(X_L_RIGHT_THREHOLD_ADDRESS);
  x_right_threshold = ((uint16_t)tmp1[0] << 8) | ((uint16_t)tmp1[1]);
  if(x_right_threshold == 0xFFFF){x_right_threshold = 900;}
  tmp1[0] = EEPROM.read(Y_H_UP_THREHOLD_ADDRESS);
  tmp1[1] = EEPROM.read(Y_L_UP_THREHOLD_ADDRESS);
  y_up_threshold = ((uint16_t)tmp1[0] << 8) | ((uint16_t)tmp1[1]);  
  if(y_up_threshold == 0xFFFF){y_up_threshold = 900;}
  tmp1[0] = EEPROM.read(Y_H_DOWN_THREHOLD_ADDRESS);
  tmp1[1] = EEPROM.read(Y_L_DOWN_THREHOLD_ADDRESS);
  y_down_threshold = ((uint16_t)tmp1[0] << 8) | ((uint16_t)tmp1[1]);  
  if(y_down_threshold == 0xFFFF){y_down_threshold = 200;}  
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent); // register event
}


void loop() {   
  int x = 1024 - analogRead(PIN_A7);
  int y = 1024 - analogRead(PIN_A3);
  if(x > y_up_threshold && (digitalRead(PIN_A5) == LOW)) // left
  {
    motion2 |= 0x02;
    delay(5);
    if(x > y_up_threshold && (digitalRead(PIN_A5) == LOW))
    {
        digitalWrite(PIN_A5, HIGH); // active
        delay(5);
        digitalWrite(PIN_A5, LOW); // active        
    }
  }
  if(x < y_down_threshold && (digitalRead(PIN_A5) == LOW)) // left
  {
    motion2 |= 0x01;
    delay(5);
    if(x < y_down_threshold && (digitalRead(PIN_A5) == LOW))
    {
        digitalWrite(PIN_A5, HIGH); // active
        delay(5);
        digitalWrite(PIN_A5, LOW); // active        
    }
  }
  if(y > x_right_threshold && (digitalRead(PIN_A5) == LOW)) // up
  {
    motion2 |= 0x04;
    delay(5);
    if(y > x_right_threshold && (digitalRead(PIN_A5) == LOW))
    {
        digitalWrite(PIN_A5, HIGH); // active
        delay(5);
        digitalWrite(PIN_A5, LOW); // active        
    }
  }
  if(y < x_left_threshold && (digitalRead(PIN_A5) == LOW)) // up
  {
    motion2 |= 0x08;
    delay(5);
    if(y < x_left_threshold && (digitalRead(PIN_A5) == LOW))
    {
        digitalWrite(PIN_A5, HIGH); // active
        delay(5);
        digitalWrite(PIN_A5, LOW); // active        
    }
  }
  if(digitalRead(PIN_B2) == LOW) // A
  {
    motion1 |= 0x01;
    delay(80);
    pin_type(PIN_B2);
  }
  if(digitalRead(PIN_A2) == LOW)  //B
  {
    motion1 |= 0x02;
    delay(80);
    pin_type(PIN_A2);
  }
  if(digitalRead(PIN_A1) == LOW)  //C
  {
    motion1 |= 0x04;
    delay(80);
    pin_type(PIN_A1);
  }
  if(digitalRead(PIN_A0) == LOW)  //D
  {
    motion1 |= 0x08;
    delay(80);
    pin_type(PIN_A0);
  }
  if(digitalRead(PIN_B1) == LOW)  //Middle
  {
    motion1 |= 0x10;
    delay(80);
    pin_type(PIN_B1);
  }  
  delay(5);
}

void receiveEvent(int howMany) {

  int i = 0;
  while ( Wire.available() ) // slave may send less than requested
  {
    rev[i++]= Wire.read(); // receive a byte as a proper uint8_t
  }
  if(rev[0] == JOYSTICK_SET_I2C_ADDRESS)
  {
    EEPROM.write(I2C_ADDRESS_STORE_ADDRESS,rev[1]);   
    rev[0] = 0;
    rev[1] = 0;     
  } 
  if(rev[0] == JOYSTICK_SET_X_RIGHT_THREHOLD)
  {
    x_right_threshold = (((uint16_t)rev[1])<<8) | ((uint16_t)rev[2]);
    EEPROM.write(X_H_RIGHT_THREHOLD_ADDRESS,rev[1]);
    EEPROM.write(X_L_RIGHT_THREHOLD_ADDRESS,rev[2]);  
    rev[0] = 0;
    rev[1] = 0; 
    rev[2] = 0;         
  }
  if(rev[0] == JOYSTICK_SET_X_LEFT_THREHOLD)
  {
    x_left_threshold = (((uint16_t)rev[1])<<8) | ((uint16_t)rev[2]); 
    EEPROM.write(X_H_LEFT_THREHOLD_ADDRESS,rev[1]);
    EEPROM.write(X_L_LEFT_THREHOLD_ADDRESS,rev[2]);   
    rev[0] = 0;
    rev[1] = 0; 
    rev[2] = 0;         
  }      
  if(rev[0] == JOYSTICK_SET_Y_UP_THREHOLD)
  {
    y_up_threshold = (((uint16_t)rev[1])<<8) | ((uint16_t)rev[2]);   
    EEPROM.write(Y_H_UP_THREHOLD_ADDRESS,rev[1]);
    EEPROM.write(Y_L_UP_THREHOLD_ADDRESS,rev[2]);  
    rev[0] = 0;
    rev[1] = 0;
    rev[2] = 0;     
  }
  if(rev[0] == JOYSTICK_SET_Y_DOWN_THREHOLD)
  {
    y_down_threshold = (((uint16_t)rev[1])<<8) | ((uint16_t)rev[2]);
    EEPROM.write(Y_H_DOWN_THREHOLD_ADDRESS,rev[1]);
    EEPROM.write(Y_L_DOWN_THREHOLD_ADDRESS,rev[2]);    
    rev[0] = 0;
    rev[1] = 0;
    rev[2] = 0;     
  }    
  if(rev[0] == JOYSTICK_SET_INT_TYPE)
  {  
    int_type = rev[1];
    EEPROM.write(KEY_INT_TYPE_ADDRESS,rev[1]);   
    rev[0] = 0;
    rev[1] = 0;
  }   
}

void requestEvent(){

  if(rev[0] == JOYSTICK_GET_VERSION)
  {
     Wire.write(FIRMWARE_VERSION);
  }
  else if(rev[0] == JOYSTICK_GET_DATA)
  {
     Wire.write(motion1);
     Wire.write(motion2);     
     motion1 = 0;
     motion2 = 0;
  }
  else if(rev[0] == JOYSTICK_GET_I2C_ADDRESS)
  {
    uint8_t tmp = EEPROM.read(I2C_ADDRESS_STORE_ADDRESS);
    if(tmp == 0xFF)
    {
       Wire.write(I2C_ADDRESS_DEFAULT);
    }
    else
    {
       Wire.write(tmp);
    }
  }
  else if(rev[0] == JOYSTICK_GET_X_POSITION)
  {
    int x = 1024 - analogRead(PIN_A3);
    if(x >= x_right_threshold || x <= x_left_threshold)
    {
      uint8_t msb = (uint8_t)(( x & 0xFF00) >> 8);
      uint8_t lsb = (uint8_t)(x & 0x00FF);
      Wire.write(msb);
      Wire.write(lsb); 
    }
  }
  else if(rev[0] == JOYSTICK_GET_Y_POSITION)
  {
    int y = 1024 - analogRead(PIN_A7);
    if(y >= y_up_threshold || y <= y_down_threshold)
    {
      uint8_t msb = (uint8_t)(( y & 0xFF00) >> 8);
      uint8_t lsb = (uint8_t)( y & 0x00FF);
      Wire.write(msb);
      Wire.write(lsb);
    } 
  }  
  else if(rev[0] == JOYSTICK_GET_X_LEFT_THREHOLD)
  {
    uint8_t c_h = (uint8_t)((x_left_threshold & 0xFF00) >> 8);    //MSB
    uint8_t c_l = (uint8_t)(x_left_threshold & 0x00FF);    //LSB
    Wire.write(c_h);
    Wire.write(c_l);
  }
  else if(rev[0] == JOYSTICK_GET_X_RIGHT_THREHOLD)
  {
    uint8_t c_h = (uint8_t)((x_right_threshold & 0xFF00) >> 8);    //MSB
    uint8_t c_l = (uint8_t)(x_right_threshold & 0x00FF);    //LSB
    Wire.write(c_h);
    Wire.write(c_l);
  } 
  else if(rev[0] == JOYSTICK_GET_Y_UP_THREHOLD)
  {
    uint8_t c_h = (uint8_t)((y_up_threshold & 0xFF00) >> 8);    //MSB
    uint8_t c_l = (uint8_t)(y_up_threshold & 0x00FF);    //LSB
    Wire.write(c_h);
    Wire.write(c_l);
  } 
  else if(rev[0] == JOYSTICK_GET_Y_DOWN_THREHOLD)
  {
    uint8_t c_h = (uint8_t)((y_down_threshold & 0xFF00) >> 8);    //MSB
    uint8_t c_l = (uint8_t)(y_down_threshold & 0x00FF);    //LSB
    Wire.write(c_h);
    Wire.write(c_l);
  }  
  else
  {
    Wire.write(0);
  }
  rev[0] = 0;
  rev[1] = 0;
}

void pin_type(uint8_t p)
{
    uint8_t tmp = 0;
    switch(p){
      case PIN_B2:
        tmp = int_type & 0x01;
        break;
      case PIN_A2:
        tmp = int_type & 0x02;
        break;
      case PIN_A1:
        tmp = int_type & 0x04;
        break;
      case PIN_A0:
        tmp = int_type & 0x08;
        break; 
      case PIN_B1:
        tmp = int_type & 0x10;
        break;                       
      default:
        break;
    }
    if(tmp == 0)
    {
        if((digitalRead(p) == LOW))    //push type
        {
          digitalWrite(PIN_A5, HIGH); // active
          delay(5);
          digitalWrite(PIN_A5, LOW); // active        
        }
    }
    else
    {
        if(digitalRead(p) == HIGH)    //release type
        {
          digitalWrite(PIN_A5, HIGH); // active
          delay(5);
          digitalWrite(PIN_A5, LOW); // active        
        }  
    }
}
