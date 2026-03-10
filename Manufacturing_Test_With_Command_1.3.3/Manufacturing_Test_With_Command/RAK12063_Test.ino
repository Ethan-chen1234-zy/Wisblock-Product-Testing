// #ifdef RAK12063_MODULE

// #include "RAK_ADC_ADS1000.h"  //http://librarymanager/All#RAK_ADC_ADS1000    2026.1.20   此库无法查找，该模块也被RAK store移除

// RAK_ADC_ADS1000 ads1000;

// void RAK12063_init(void)
// {
//   pinMode(WB_IO2, OUTPUT);
//   digitalWrite(WB_IO2, HIGH); // Enable power supply.
//   delay(300);
// }

// void getMB1000Range(void) 
// {
//   float ads_Voltage = 0;
//   ads_Voltage = ads1000.getVoltage();
//   Serial.printf("ads_Voltage=%0.3f V\r\n", ads_Voltage);
//   float distance_inch = (ads_Voltage * 1000) / 6.4;  //Distance unit: inch
//   float distance_cm = distance_inch * 2.54;          //Distance unit: inch
//   Serial.printf("distance_inch=%0.2f inch  distance_cm=%0.2f cm  configRegister=%x\r\n", distance_inch, distance_cm, ads1000.getConfigRegister());
//   Serial.println();
// }

// void RAK12063_test(unsigned long timeout)
// {
//   RAK12063_init();

//   delay(1000);
//   if (!ads1000.begin()) 
//   {
//     Serial.println("The link failed,Please check the module connection");
//     Serial.printf("RAK12063 Test Failed\n");
//     return;
//   }
//   ads1000.softwareReset();
//   delay(100);
//   ads1000.setConfigRegister(0x81);

//   time_t startTime = millis();

//   while ((millis() - startTime) < 5000) 
//   {
//     getMB1000Range();
//     delay(1000);
//   }
// }

// #endif
