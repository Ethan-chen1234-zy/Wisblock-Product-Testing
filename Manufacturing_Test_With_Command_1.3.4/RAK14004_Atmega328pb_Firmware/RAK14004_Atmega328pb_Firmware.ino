#include <Wire1.h>
#include <EEPROM.h>

#define GPIOA_PIN0  (9)
#define GPIOA_PIN1  (8)
#define GPIOA_PIN2  (7)
#define GPIOA_PIN3  (6)
#define GPIOA_PIN4  (5)
#define GPIOA_PIN5  (3)
#define GPIOA_PIN6  (4)
#define GPIOA_PIN7  (2)

#define GPIOB_PIN0  (A0)
#define GPIOB_PIN1  (A1)
#define GPIOB_PIN2  (A2)
#define GPIOB_PIN3  (A3)
#define GPIOB_PIN4  (A4)
#define GPIOB_PIN5  (A5)
#define GPIOB_PIN6  (A6)
#define GPIOB_PIN7  (A7)
#define GPIO_INT    (10)

#define I2C_ADDRESS_DEFAULT         0x5F
#define I2C_ADDRESS_STORE_ADDRESS   0x01
#define FIRMWARE_VERSION            0x02

//Soil Moisture Sensor Register Addresses
#define SENSOR_GET_KEYPAD        0x01 // (r)   2 bytes
#define SENSOR_GET_I2C_ADDRESS   0x02  // (r)   1 bytes
#define SENSOR_SET_I2C_ADDRESS   0x03  // (w)   1 bytes
#define SENSOR_GET_VERSION       0x04 // (r)   1 bytes

uint8_t GPIOA_Buf[8] = {GPIOA_PIN0, GPIOA_PIN1, GPIOA_PIN2, GPIOA_PIN3, GPIOA_PIN4, GPIOA_PIN5, GPIOA_PIN6, GPIOA_PIN7};
uint8_t GPIOB_Buf[8] = {GPIOB_PIN0, GPIOB_PIN1, GPIOB_PIN2, GPIOB_PIN3, GPIOB_PIN4, GPIOB_PIN5, GPIOB_PIN6, GPIOB_PIN7};
uint8_t GetStatusBuf[8] =    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t GetOldStatusBuf[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t rev[2] = {0};

void setup() {
  // put your setup code here, to run once:
  for (uint8_t aCount = 0; aCount < 8; aCount++)
  {
    pinMode(GPIOA_Buf[aCount], OUTPUT);
    digitalWrite(GPIOA_Buf[aCount], HIGH);
    pinMode(GPIOB_Buf[aCount], INPUT);
  }
  pinMode(GPIO_INT, OUTPUT);
  digitalWrite(GPIO_INT, LOW);

  Wire1.begin(I2C_ADDRESS_DEFAULT);   //use the default
  Wire1.onReceive(receiveEvent); // register event
  Wire1.onRequest(requestEvent); // register event
  delay(10);
}

/* brief:function that executes whenever data is received from master this function is registered as an event, see setup()
*/
void receiveEvent(int howMany) {
  (void)howMany;  // cast unused parameter to void to avoid compiler warning
  int i = 0;
  while ( Wire1.available() ) // slave may send less than requested
  {
    rev[i++] = Wire1.read(); // receive a byte as a proper uint8_t
  }
  if (rev[0] == SENSOR_SET_I2C_ADDRESS)
  {
    rev[0] = 0;
    rev[1] = 0;
  }
}

/* function that executes whenever data is requested by master this function is registered as an event, see setup()*/
void requestEvent() {

  if (rev[0] == SENSOR_GET_VERSION)
  {
    Wire1.write(FIRMWARE_VERSION);
  }
  else if (rev[0] == SENSOR_GET_KEYPAD)
  {
    for (uint8_t rCount = 0; rCount < 8; rCount++)
    {
      Wire1.write(GetStatusBuf[rCount]);
    }
    memset(GetStatusBuf, 0, 8); //sizeof(GetStatusBuf) / sizeof(uint8_t)
  }
  else if (rev[0] == SENSOR_GET_I2C_ADDRESS)
  {
    uint8_t tmp = EEPROM.read(I2C_ADDRESS_STORE_ADDRESS);
    if (tmp == 0xFF)
    {
      Wire1.write(I2C_ADDRESS_DEFAULT);
    }
    else
    {
      Wire1.write(tmp);
    }

  }
  else
  {
    Wire1.write(0);
  }
  rev[0] = 0;
  rev[1] = 0;
}


void GetInput(void)
{
  for (uint8_t aCount = 0; aCount < 8; aCount++)
  {
    pinMode(GPIOA_Buf[aCount], OUTPUT);
    digitalWrite(GPIOA_Buf[aCount], LOW);
    delay(10);
    for (uint8_t bCount = 0; bCount < 8; bCount++)
    {
      uint8_t gData = 0x00;
      if (digitalRead(GPIOB_Buf[bCount]) == 0)
      {
        delay(8);
        if (digitalRead(GPIOB_Buf[bCount]) == 0)
        {
          gData = 0x01;
          GetStatusBuf[aCount] = GetStatusBuf[aCount] | (gData << bCount);
        }
      }
      else
      {
        gData = 0x00;
        GetStatusBuf[aCount] = GetStatusBuf[aCount] | (gData << bCount);
      }
    }
    digitalWrite(GPIOA_Buf[aCount], HIGH);
    delay(1);
    pinMode(GPIOA_Buf[aCount], INPUT);

    if (aCount == 7)
    {
      uint8_t arraysEqual = 1;
      int bufcount = 0;
      while (bufcount < 8)
      {
        if (GetStatusBuf[bufcount] == GetOldStatusBuf[bufcount])
        {
          //arraysEqual = 1;
        }
        else
        {
          arraysEqual = 0;
          break;
        }
        bufcount++;
      }
      if (arraysEqual == 0)
      {
        digitalWrite(GPIO_INT, HIGH);
      }
      digitalWrite(GPIO_INT, LOW);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  GetInput();
}
