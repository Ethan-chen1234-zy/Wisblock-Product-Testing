#ifdef RAK13005_MODULE
#include  "lin_bus.h" //library: http://librarymanager/All#RAKwireless_TLE7259_LIN_Bus_library

#if defined(_VARIANT_RAK4630_)
#define BOARD "RAK4631 "
int lin_tx = 16;
#elif defined(_VARIANT_RAK11300_)
#define BOARD "RAK11300 "
int lin_tx = 0;
#else
#define BOARD "RAK11200 "   //default board is RAK11200
int lin_tx = 21;
#endif

int lin_en = WB_IO6;  //internal pulldown, EN=0 is sleep mode, EN=1 is normal operation mode.
int lin_wk = WB_IO5;  //low active
// LIN Object

lin_bus lin1(Serial1, LIN_V1, lin_en, lin_wk, lin_tx);
unsigned long baute = 9600;
uint16_t sendCount = 0;


void RAK13005_init()
{
  // Nothing to do here.
  pinMode(lin_wk, OUTPUT);
  digitalWrite(lin_wk, HIGH);
  lin1.master(baute);
  Serial.println("TEST RAK13005");
}
void RAK13005_testS(unsigned long timeout)
{
  RAK13005_init();
  int dataSize = 3;
  uint8_t test_ok = 0;
  uint8_t readData[3];
  uint8_t sendData[3] = {0x55, 0, 0xff}; //
  time_t startTime = millis();
  while ((millis() - startTime) < timeout)
  {
    lin1.write(0x01, sendData, dataSize); // Write data to LIN
    time_t rx_timeout = millis();
    while ((millis() - rx_timeout) < 600)
    {
      int ok = lin1.listen(0x01, readData, dataSize); //read slaver
      if (ok == 1)
      {
        //        Serial.println("RAK13005 read data is ok");
        if ((readData[0] == sendData[0]) && (readData[1] == sendData[1]) && (readData[2] == sendData[2]))
        {
          Serial.printf("\r\n-----------RAK13005 Test OK-------------\r\n");
          Serial1.end();
          return;
        }
      }
    }
    //    Serial.println("wait for next command");
  }
  Serial.printf("\r\n-----------RAK13005 Test Failed----------\r\n");
  Serial1.end();
}

void RAK13005_testR(unsigned long timeout)
{
  uint8_t slaver_id = 1;
  uint8_t dataSize = 3;
  uint16_t receiveCount = 0;
  uint8_t sendData[3] = {0};
  uint8_t readData[dataSize];
  uint8_t i = 0;
  lin1.slave(baute, slaver_id);
  Serial.println("------------------------------");
  Serial.println(BOARD);
  Serial.println("TEST RAK13005 slaver");
  Serial.println("------------------------------");
  time_t startTime = millis();
  while ((millis() - startTime) < timeout)
  {
    int ok = lin1.read(readData, dataSize); //  int ok = lin1.listen(slaver_id,readData,dataSize);
    if (ok == 1)
    {
      Serial.printf("The LIN bus receive count is %d\r\n", receiveCount++);
      Serial.println("TEST RAK13005 receive data");
      for (uint8_t i = 0; i < dataSize; i++)
      {
        sendData[i] = readData[i];
        Serial.printf("The data[%d] is %d \r\n", i, readData[i]);
      }
      delay(50);
      lin1.write(slaver_id, sendData, dataSize);
    }
  }
}
#endif
