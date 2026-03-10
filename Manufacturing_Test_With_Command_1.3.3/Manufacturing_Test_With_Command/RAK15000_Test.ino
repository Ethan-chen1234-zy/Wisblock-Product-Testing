#ifdef RAK15000_MODULE

#include "Production_test_configure.h"
#include "Adafruit_EEPROM_I2C.h"  // Click here to get the library: http://librarymanager/All#Adafruit_EEPROM_I2C
                                  // 注意，安装库使用1.1.3  更高版本的库不支持 write 函数，改为 write8.
                                  //注：2026.1.20 安装v2.0.3  write/read 函数可以使用

#define EEPROM_ADDR 0x50  // the default address!
#define MAXADD 262143   // max address in byte

void RAK15000_test(unsigned long timeout)
{
  Adafruit_EEPROM_I2C i2ceeprom;
  long g_random_addr = 0;
  unsigned char g_write_data = 0;
  unsigned char g_read_data = 0;

  pinMode(WB_IO2, OUTPUT);
  digitalWrite(WB_IO2, HIGH);   // power on for AT24C02 device
  delay(300);
  if (i2ceeprom.begin(EEPROM_ADDR))  // you can stick the new i2c addr in here, e.g. begin(0x51);
  {
    //初始化成功
    g_random_addr = random(0, MAXADD);
    g_write_data = 0x55;
    //i2ceeprom.write8(g_random_addr, g_write_data);
    i2ceeprom.write(g_random_addr, g_write_data);   //v2.0.3 可使用

    //g_read_data = i2ceeprom.read8(g_random_addr);
    g_read_data = i2ceeprom.read(g_random_addr);  //v2.0.3 可使用
    if (g_read_data == g_write_data)
    {
      // i2ceeprom.write8(g_random_addr, 0xff);
      // g_read_data = i2ceeprom.read8(g_random_addr);
      i2ceeprom.write(g_random_addr, 0xff);
      g_read_data = i2ceeprom.read(g_random_addr);
      if (g_read_data == 0xff)
      {
        Serial.printf("RAK15000 Test OK\n");
      }
      else
      {
        Serial.printf("RAK15000 Test Failed\n");
      }
    }
  }
  else
  {
    //初始化失败
    Serial.printf("RAK15000 Test Failed\n");
  }
}

#endif
