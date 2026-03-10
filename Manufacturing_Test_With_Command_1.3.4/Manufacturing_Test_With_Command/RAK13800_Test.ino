#ifdef RAK13800_MODULE

#include "Production_test_configure.h"
#include <RAK13800_W5100S.h> // Click to install library: http://librarymanager/All#RAKwireless_W5100S  v1.0.0  2026.1.20

#define LOCAL_PORT   8888    // Set the server port.
IPAddress ip(192, 168, 1, 155); // Set IP address,dependent on your local network.

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // Set the MAC address, do not repeat in a network.

void RAK13800_init(void)
{
  pinMode(WB_IO2, OUTPUT);
  digitalWrite(WB_IO2, HIGH); // Enable power supply.

  //Ethernet.init( SPI,SS );
  Ethernet.init( SS );  // 新版本只需片选引脚
  Ethernet.begin(mac, ip);
}

void RAK13800_test(unsigned long timeout)
{
  EthernetUDP Udp;
  RAK13800_init();
  if (Ethernet.hardwareStatus() == EthernetNoHardware)  // Check for Ethernet hardware present.
  {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    Serial.printf("RAK13800 Test Failed!\n");
    digitalWrite(WB_IO2, LOW); 
    delay(100);
    digitalWrite(WB_IO2, HIGH); 
    return;
  }
  while (Ethernet.linkStatus() == LinkOFF) 
  {
    Serial.println("Ethernet cable is not connected.");
    Serial.printf("RAK13800 Test Failed!\n");
    digitalWrite(WB_IO2, LOW); 
    delay(100);
    digitalWrite(WB_IO2, HIGH); 
    return;
  }

  Udp.begin(LOCAL_PORT);  // Start UDP.
  Serial.println("Udp begin OK.");

  time_t time_stamp = millis();
  while ((millis() - time_stamp) < timeout)
  {
    delay(100);
  }

  Serial.println("RAK13800 Test Time Out.");
  digitalWrite(WB_IO2, LOW); 
  delay(100);
  digitalWrite(WB_IO2, HIGH); 
}

#endif
