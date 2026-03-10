#ifdef RAK13801_MODULE
#include <SPI.h>
#include <DW1000Ng.hpp>    // Click to install library: http://librarymanager/All#RAK13801_UWB v1.0.0


const uint8_t PIN_SS = SS; // spi select pin
const uint8_t PIN_RST = WB_IO6;
const uint8_t PIN_IRQ = WB_IO5;

int16_t numReceived = 0; // todo check int type
String message;

device_configuration_t DEFAULT_CONFIG = {
    false,
    true,
    true,
    true,
    false,
    SFDMode::STANDARD_SFD,
    Channel::CHANNEL_5,
    DataRate::RATE_850KBPS,
    PulseFrequency::FREQ_16MHZ,
    PreambleLength::LEN_256,
    PreambleCode::CODE_3
};

void RAK13801_init(void)
{
  pinMode(WB_IO2, OUTPUT);
  digitalWrite(WB_IO2, HIGH); //Turn on the power switch
  delay(300);
  
  Serial.println(F("### DW1000Ng-arduino-receiver-test ###"));
  // initialize the driver
  DW1000Ng::initializeNoInterrupt(PIN_SS,PIN_RST);
  Serial.println(F("DW1000Ng initialized ..."));

  // DEBUG chip info and registers pretty printed
  char msg[128];


  DW1000Ng::applyConfiguration(DEFAULT_CONFIG);

  DW1000Ng::setDeviceAddress(6);
  DW1000Ng::setNetworkId(10);

  DW1000Ng::setAntennaDelay(16436);
  Serial.println(F("Committed configuration ..."));
  // DEBUG chip info and registers pretty printed

  DW1000Ng::getPrintableDeviceIdentifier(msg);
  Serial.print("Device ID: "); Serial.println(msg);
  DW1000Ng::getPrintableExtendedUniqueIdentifier(msg);
  Serial.print("Unique ID: "); Serial.println(msg);
  DW1000Ng::getPrintableNetworkIdAndShortAddress(msg);
  Serial.print("Network ID & Device Address: "); Serial.println(msg);
  DW1000Ng::getPrintableDeviceMode(msg);
  Serial.print("Device mode: "); Serial.println(msg);

  DW1000Ng::getPrintableDeviceIdentifier(msg);
  Serial.print("Device ID: "); Serial.println(msg);
}

void RAK13801_test(unsigned long timeout)
{
  RAK13801_init();
  DW1000Ng::startReceive();
  
  time_t time_now = millis();
  while ((millis() - time_now) < 5000)
  {
    if (DW1000Ng::isReceiveDone())
    {
      DW1000Ng::clearReceiveStatus();
      // get data as string
      DW1000Ng::getReceivedData(message);
      Serial.print("Data is ... "); Serial.println(message);
      Serial.print("RX power is [dBm] ... "); Serial.println(DW1000Ng::getReceivePower());
      Serial.print("Signal quality is ... "); Serial.println(DW1000Ng::getReceiveQuality());
      Serial.println();
      if(message.indexOf("Hello DW1000Ng") != -1)
      {
        Serial.printf("RAK13801 Test OK\n");
        return; 
      }
      else
      {
        Serial.printf("RAK13801 Test Failed\n");
        return; 
      }
    }
  }
  Serial.printf("RAK13801 Test Failed\n");  
}
#endif
