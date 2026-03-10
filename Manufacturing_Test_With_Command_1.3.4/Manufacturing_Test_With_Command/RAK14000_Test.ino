#ifdef RAK14000_MODULE

#include "Production_test_configure.h"
#include <Adafruit_GFX.h>
#include <Adafruit_EPD.h> //Click here to get the library: http://librarymanager/All#Adafruit_EPD

#define POWER_ENABLE   WB_IO2
#define EPD_MOSI       MOSI
#define EPD_MISO       -1     // not use
#define EPD_SCK        SCK
#define EPD_CS         SS
#define EPD_DC         WB_IO1
#define SRAM_CS        -1     // not use
#define EPD_RESET      -1     // not use
#define EPD_BUSY       WB_IO4

void RAK14000_testB(unsigned long timeout)
{
  Adafruit_SSD1680 display(212, 104, EPD_MOSI,
                           EPD_SCK, EPD_DC, EPD_RESET,
                           EPD_CS, SRAM_CS, EPD_MISO,
                           EPD_BUSY);


  display.begin(false);
  
  display.clearBuffer();
  display.fillScreen(EPD_WHITE);
  display.display(true);
  delay(2000);

  display.clearBuffer();
  display.fillScreen(EPD_BLACK);
  display.display(true);
}

void RAK14000_testR(unsigned long timeout)
{
  Adafruit_SSD1680 display(250, 122, EPD_MOSI,
                           EPD_SCK, EPD_DC, EPD_RESET,
                           EPD_CS, SRAM_CS, EPD_MISO,
                           EPD_BUSY);

  display.begin(false);

  display.clearBuffer();
  display.fillScreen(EPD_WHITE);
  display.display(true);
  delay(2000);

  display.clearBuffer();
  display.fillScreen(EPD_BLACK);
  display.display(true);
  delay(2000);

  display.clearBuffer();
  display.fillScreen(EPD_RED);
  display.display(true);
  delay(2000);
}
#endif
