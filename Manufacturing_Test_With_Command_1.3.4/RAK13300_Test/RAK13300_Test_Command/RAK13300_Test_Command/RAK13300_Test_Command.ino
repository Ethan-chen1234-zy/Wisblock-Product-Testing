#include <Arduino.h>
#include <SX126x-Arduino.h> //http://librarymanager/All#SX126x
#include <SPI.h>

#define VERSION       "1.0.0"
#define DATE          'R'
#define RX_TIME_OUT   5000

// Function declarations
void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr);
void OnRxTimeout(void);
void OnRxError(void);

void OnTxDone(void);
void OnTxTimeout(void);


// Define LoRa parameters
#define RF_FREQUENCY 868300000  // Hz
#define TX_OUTPUT_POWER 22    // dBm
#define LORA_BANDWIDTH 0    // [0: 125 kHz, 1: 250 kHz, 2: 500 kHz, 3: Reserved]
#define LORA_SPREADING_FACTOR 7 // [SF7..SF12]
#define LORA_CODINGRATE 1   // [1: 4/5, 2: 4/6,  3: 4/7,  4: 4/8]
#define LORA_PREAMBLE_LENGTH 8  // Same for Tx and Rx
#define LORA_SYMBOL_TIMEOUT 0 // Symbols
#define LORA_FIX_LENGTH_PAYLOAD_ON false
#define LORA_IQ_INVERSION_ON false
#define RX_TIMEOUT_VALUE 3000
#define TX_TIMEOUT_VALUE 3000

static RadioEvents_t RadioEvents;

static uint8_t flag = 0;  //  指示命令是否执行完成
void setup() 
{
  time_t timeout = millis();
  Serial.begin(115200);
  while (!Serial)
  {
    if ((millis() - timeout) < 5000)
    {
      delay(100);
    }
    else
    {
      break;
    }
  }
  Serial.println("=====================================");
  Serial.println("RAK13300 Manufacturing Test");
  Serial.println(VERSION);
  Serial.println("=====================================");

}

void loop() 
{
  String command = "";
  
  while(flag!=0)
  {
    delay(200);
  }
  Serial.printf("\nPlease insert Command!!! \n");
  while (!Serial.available()) 
  {
    delay(200);
  };

  while (Serial.available() > 0) 
  {
    command += char(Serial.read());
    //Serial.println(command);
    delay(10);
  }

  if (String("TEST RAK13300") == command)
  {
    flag = 1;
    Serial.println("\nSTART TEST RAK13300");
    pinMode(WB_IO2, OUTPUT);
    digitalWrite(WB_IO2, LOW);
    delay(1000);
    digitalWrite(WB_IO2, HIGH);

    lora_rak13300_init();// Initialize LoRa chip.
    //lora_rak4630_init();// Initialize LoRa chip.
    
    RadioEvents.TxDone = OnTxDone;// Initialize the Radio callbacks
    RadioEvents.RxDone = OnRxDone;
    RadioEvents.TxTimeout = NULL;
    RadioEvents.RxTimeout = NULL;
    RadioEvents.RxError = OnRxError;
    RadioEvents.CadDone = NULL;
    
    // Initialize the Radio
    Radio.Init(&RadioEvents);
    
    Radio.SetChannel(RF_FREQUENCY);
    
    // Set Radio TX configuration
    Radio.SetTxConfig(MODEM_LORA, TX_OUTPUT_POWER, 0, LORA_BANDWIDTH,
                      LORA_SPREADING_FACTOR, LORA_CODINGRATE,
                      LORA_PREAMBLE_LENGTH, LORA_FIX_LENGTH_PAYLOAD_ON,
                      true, 0, 0, LORA_IQ_INVERSION_ON, TX_TIMEOUT_VALUE);
                      
    Serial.println("Starting Radio.Tx");
    send();
    WaitOnTimeOut();
  }
}

void WaitOnTimeOut(void)
{
  unsigned long time_now = millis();
  while ( (millis() - time_now) < RX_TIME_OUT)
  {
    if (flag == 0)
    {
      return;
    }
  }
  Serial.println("RAK13300 Test Failed!");
  flag = 0;
}

/**@brief Function to be executed on Radio Tx Done event
 */
void OnTxDone(void)
{
  Serial.println("OnTxDone");

  Radio.SetChannel(RF_FREQUENCY); // Set Radio channel

  Radio.SetRxConfig(MODEM_LORA, LORA_BANDWIDTH, LORA_SPREADING_FACTOR,
            LORA_CODINGRATE, 0, LORA_PREAMBLE_LENGTH,
            LORA_SYMBOL_TIMEOUT, LORA_FIX_LENGTH_PAYLOAD_ON,
            0, true, 0, 0, LORA_IQ_INVERSION_ON, true); // Set Radio RX configuration

  // Start LoRa
  Serial.println("Starting Radio.Rx");
  Radio.Rx(RX_TIMEOUT_VALUE);
}

/**@brief Function to be executed on Radio Tx Timeout event
 */
void OnTxTimeout(void)
{
  Serial.println("OnTxTimeout");
  Serial.println("RAK13300 Test Failed!");
  flag = 0;
}

void send()
{
  uint8_t TxdBuffer[5];
  TxdBuffer[0] = DATE;
  Radio.Send(TxdBuffer, 1);
  Serial.println("Send Date...");
}

/**@brief Function to be executed on Radio Tx Done event
 */
void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr)
{
  uint8_t RcvBuffer[64];
  Serial.println("OnRxDone");
  delay(10);
  memcpy(RcvBuffer, payload, size);

  Serial.printf("RssiValue=%d dBm, SnrValue=%d\n", rssi, snr);

  if( RcvBuffer[0] == DATE )
  {
    Serial.println("RAK13300 Test OK!");
    flag = 0;
  }
  else
  {
    Serial.println("RAK13300 Test Failed!");
    flag = 0;
  }
}


/**@brief Function to be executed on Radio Rx Timeout event
 */
void OnRxTimeout(void)
{
  Serial.println("OnRxTimeout");
  Serial.println("RAK13300 Test Failed!");
  flag = 0;
}

/**@brief Function to be executed on Radio Rx Error event
 */
void OnRxError(void)
{
  Serial.println("OnRxError");
  Serial.println("RAK13300 Test Failed!");
  flag = 0;
}
