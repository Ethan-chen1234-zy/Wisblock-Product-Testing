#ifdef RAK14014_MODULE

#include <Adafruit_GFX.h>      // Click here to get the library: http://librarymanager/All#Adafruit_GFX
#include <Adafruit_ST7789.h>  // Click here to get the library: http://librarymanager/All#Adafruit_ST7789
//#include "FT6336U.h"    //Click here to get the library: http://librarymanager/All#RAK14014-FT6336U   2026.1.21 v1.0.1  FT6336U只能找到RAK14014-FT6336U，头文件：RAK14014-FT6336U.h
#include "RAK14014_FT6336U.h" 
#include <SPI.h>


#define CS            SS
#define BL            WB_IO3
#define RST           WB_IO5
#define DC            WB_IO4

#define RST_PIN       WB_IO5
#define INT_PIN       WB_IO6

Adafruit_ST7789 testTft = Adafruit_ST7789(CS, DC, RST);
//FT6336U testFt6336u(RST_PIN, INT_PIN);   //v1.0.1版本库中 实例化不需传递参数
FT6336U testFt6336u;

void RAK14014_test(unsigned long timeout)
{ 
  pinMode(WB_IO2, OUTPUT);
  digitalWrite(WB_IO2, HIGH);
  
  pinMode(BL, OUTPUT);
  digitalWrite(BL, HIGH); // Enable the backlight, you can also adjust the backlight brightness through PWM.
  
  testTft.init(240, 320); // Init ST7789 240x240.
  testTft.setRotation(3);
  
  testTft.fillScreen(ST77XX_RED);
  delay(2000);
  testTft.fillScreen(ST77XX_GREEN);
  delay(2000);
  testTft.fillScreen(ST77XX_BLUE);
  delay(2000);
  

  testFt6336u.begin(); // No reset. Reset is reset when the screen is reset

  pinMode(INT_PIN, INPUT_PULLUP);
  
  testTft.setTextSize(1);
  testTft.setCursor(20, 50);
  testTft.setTextColor(ST77XX_WHITE);
  testTft.setTextWrap(true);
  testTft.print("Touch the screen within 5s.");
  Serial.println("Touch the screen within 5s.");
  delay(100);

  testTft.setCursor(20, 100);
  time_t time = millis();
  while((millis() - time) < 5000)
  {
    if(digitalRead(INT_PIN) == 0)
    {
      testTft.print("RAK14014 Test OK!");
      Serial.printf("RAK14014 Test OK!\n");
      digitalWrite(BL, LOW);
      return;
    }
  }
  
  testTft.setCursor(20, 100);
  testTft.print("RAK14014 Test Failed!");
  Serial.printf("RAK14014 Test Failed!\n");
  digitalWrite(BL, LOW);
}

#endif
