#ifndef __PRODUCTION_TEST_CONFIGURE__
#define __PRODUCTION_TEST_CONFIGURE__

#include <Wire.h>

// define software version
#define VERSION "Version: 1.3.3"

// define modules included in software, 1 is included, 0 is not included.
// if included, please install the library on the right.
#define RAK1901_MODULE     // SHTC3         | library: http://librarymanager/All#SparkFun_SHTC3
#define RAK1902_MODULE     // LPS22HB       | library: http://librarymanager/All#Arduino_LPS22HB
#define RAK1903_MODULE     // OPT3001       | library: http://librarymanager/All#OPT3001
#define RAK1904_MODULE     // LIS3DH        | library: http://librarymanager/All#SparkFun_LIS3DH_Arduino_Library
#define RAK1906_MODULE     // BME680        | library: http://librarymanager/All#ClosedCube_BME680_Arduino
#define RAK1910_MODULE     // 7Q-GPS
#define RAK12500_MODULE    // M8Q-GPS       | library: http://librarymanager/All#SparkFun_u-blox_GNSS 

#define RAK5801_MODULE     // 4-20mA
#define RAK5802_MODULE     // RS485         | library: http://librarymanager/All#ArduinoModbus
#define RAK5811_MODULE     // 0-5v

#define RAK12003_MODULE    // MLX90632      | library: http://librarymanager/All#SparkFun_MLX90632_Arduino_Library
#define RAK15000_MODULE    // EEPROM_I2C    | library: http://librarymanager/All#Adafruit_EEPROM_I2C
#define RAK15001_MODULE    // FLASH_SPI     | library: http://librarymanager/All#Adafruit_SPIFlash
#define RAK18000_MODULE    // PDM_mic
#define RAK18001_MODULE    // buzzer
#define RAK19002_MODULE    // Boost

//V 1.0.8 Version update content.
#define RAK13003_MODULE    // MCP23017      | library: http://librarymanager/All#Adafruit_MCP23017
#define RAK13004_MODULE    // PCA9685       | library: http://librarymanager/All#PCA9685
#define RAK14002_MODULE    // CAP1293       | library: http://librarymanager/All#RAK14002-CAP1293-Library

//V 1.0.9 Version update content.
#define RAK15002_MODULE    // SD Card       | library: //http://librarymanager/All#SD
#define RAK12002_MODULE    // RTC           | library: //http://librarymanager/All#Melopero_RV3028
#define RAK17000_MODULE    // DC Motor
#define RAK14001_MODULE    // RGB LED       | library: //http://librarymanager/All#NCP5623
#define RAK13001_MODULE    // DI DO

#define RAK12005_MODULE   //water detection
#define RAK12009_MODULE   //alcohol detection

//V 1.1.0 Version update content.
#define RAK12004_MODULE   //MQ2 sensor detection
#define RAK12006_MODULE   //PIR sensor                   | library:: http://librarymanager/All#RAKwireless_MQx_library
#define RAK12007_MODULE   //ultrasonic measure distance  
#define RAK12010_MODULE   //Light Sensor detection       | library:: http://librarymanager/All#RAKwireless_VEML7700
#define RAK12012_MODULE   //Heart rate Sensor detection 
#define RAK13005_MODULE   //LINBus communication         | library: http://librarymanager/All#RAKwireless_TLE7259_LIN_Bus_library
#define RAK14000_MODULE   //Epaper driver               | library: http://librarymanager/All#Adafruit_EPD
#define RAK14003_MODULE   //LED_BAR 

//V 1.1.1 Version update content.
#define RAK12011_MODULE   //Pressure WT sensor detection | library: http://librarymanager/All#Adafruit_LPS2X
#define RAK12015_MODULE   //Vibration sensor detection 
#define RAK12016_MODULE   //Flex sensor detection        | library: http://librarymanager/All#RAKwireless_MQx_library  
#define RAK13101_MODULE   //GSM/GPRS                      

//V 1.1.2 Version update content.
#define RAK12017_MODULE   //IR sensor detection           |         
#define RAK12018_MODULE   //CodeReader
#define RAK14006_MODULE   //Rotary Encoder                 
#define RAK16000_MODULE   //DC Current                    | library: http://librarymanager/All#INA219_WE
#define RAK16001_MODULE   //ADC Sensor detection          | library: http://librarymanager/All#RAKwireless_ADS7830_library

//V 1.1.3 Version update content.
#define RAK12019_MODULE   //UVlight LTR390                |  
#define RAK12014_MODULE   //TOF                           | library: http://librarymanager/All#stm32duino_vl53l0x
#define RAK12025_MODULE   //Three-axis gyro               | 
#define RAK13007_MODULE   //Relay    
#define RAK12035_MODULE   //Soil moisture   
#define RAK12023_MODULE   //Soil moisture  

//V 1.1.4 Version update content.
//Modify only one judgment condition

//V 1.1.5 Version update content.
#define RAK12021_MODULE   //RGBC                          | library: http://librarymanager/All#RAKwireless_TCS37725_RGBC_library
#define RAK13600_MODULE   //NFC                           | library: http://librarymanager/All#RAK13600-PN532
#define RAK14004_MODULE   //KEYPAD              
#define RAK12013_MODULE   //3GHZ Radar
#define RAK12031_MODULE   //T-Fork

//V 1.1.8 Version update content.
#define RAK12029_MODULE   //Inductive                     | library: http://librarymanager/All#RAK12029_LDC1614   
#define RAK12001_MODULE   //Fingerprint    
#define RAK14012_MODULE   //LED Matrix

//V 1.1.9 Version update content.
#define RAK13800_MODULE   //Ethernet                      | library: http://librarymanager/All#RAKwireless_W5100S
#define RAK14008_MODULE   //Gesture                       | library: http://librarymanager/All#Gesture_PAJ7620
#define RAK16002_MODULE   //Coulomb
#define RAK14013_MODULE   //Joystick

//V 1.2.1 Version update content.
#define RAK12032_MODULE   //3-Axis                        | library:  http://librarymanager/All#SparkFun_ADXL313
#define RAK12034_MODULE   //9-Axis                        | library:  http://librarymanager/All#RAK12034_BMX160
#define RAK12037_MODULE   //T&H SCD30                     | library:  http://librarymanager/All#SparkFun_SCD30
#define RAK12040_MODULE   //8x8 IR                        | library:  http://librarymanager/All#SparkFun_GridEYE_Arduino_Library
#define RAK12047_MODULE   //VOC                           | library:  http://librarymanager/All#SensirionI2CSgp40

//V 1.2.2 Version update content.
#define RAK12022_MODULE   //PT100                         | library:  http://librarymanager/RAK12022_MAX31865
#define RAK12008_MODULE   //CO2 detection                 | library:  http://librarymanager/All#SparkFun_STC3x
#define RAK12044_MODULE   //Hall                          | library:  http://librarymanager/All#RAKwireless_MQx_library  
#define RAK12027_MODULE   //Earthquake                    | library:  http://librarymanager/RAK12027_D7S
#define RAK1905_MODULE    //9-Axis                        | library:  http://librarymanager/RAK12027_D7S
#define RAK12020_MODULE   //Light TSL                     | library:  http://librarymanager/All#Adafruit_TSL2591

//V 1.2.3 Version update content.
#define RAK12033_MODULE   //6-Axis                        | library:  http://librarymanager/All#RAK12033_IIM42652
#define RAK13006_MODULE   //CAN BUS                       | library:  http://librarymanager/All#RAK13006_CAN
#define RAK5814_MODULE    //ECC                           | library:  http://librarymanager/All#SparkFun_ATECCX08a

//V 1.2.4 Version update content.
#define RAK15003_MODULE   //FRAM 256kBit                  | library:  http://librarymanager/All#RAK1500x-MB85RC
#define RAK15004_MODULE   //FRAM 512kBit                  | library:  http://librarymanager/All#RAK1500x-MB85RC
#define RAK17001_MODULE   //DC Motor                      |
#define RAK12054_MODULE   //Encoder                       | library:  http://librarymanager/All#RAK12054-AS5600

//V 1.2.5 Version update content.
#define RAK12039_MODULE   //dust                          | library:  http://librarymanager/All#RAK12039_PMSA003I
#define RAK12052_MODULE   //32x24 IR                      | library:  http://librarymanager/All#RAK12052-MLX90640

//V 1.2.6 Version update content.
#define RAK15005_MODULE   //FRAM 1024kBit                 | library:  http://librarymanager/All#RAK1500x-MB85RC
#define RAK13801_MODULE   //UWB   
#define RAK13010_MODULE   //SDI_12                        | library:  http://librarymanager/All#RAK12033-SDI12  

//V 1.2.7 Version update content.
#define RAK15006_MODULE   //FRAM 4MBit                    | library:  http://librarymanager/All#Adafruit_FRAM_SPI version:2.4.1 
// #define RAK12063_MODULE   //UItrasonic                    | library:  http://librarymanager/All#RAK_ADC_ADS1000
#define RAK14014_MODULE   //TFT                           | library:  http://librarymanager/All#Adafruit_ST7789  http://librarymanager/All#Adafruit_GFX

//V 1.2.8 Version update content.
#define RAK13011_MODULE   //MagneticSwitch  

//V 1.2.9 Version update content.
#define RAK12059_MODULE   //liquid_level_measurement      | library:  http://librarymanager/All#RAKwireless_ADC_SGM58031_library 
#define RAK12067_MODULE
#define RAK13012_MODULE
//extern void RAK12067_test(unsigned long time_out);
//extern void RAK13012_test(unsigned long time_out);

//V 1.3.0 Version update content.
#define RAK15007_MODULE   //FRAM                          | library:  //http://librarymanager/All#RAK15007_CY15B108QN

//V 1.3.2 Version update content.
#define RAK5860_MODULE    // 
#define RAK12501_MODULE   // GPS,like 1906

//V 1.3.3 Version update RAK13101 test function.

// donnot delete, if deleted, RAK1903 cannot compile successfully.
#ifdef RAK1903_MODULE 1
#include <ClosedCube_OPT3001.h>
#endif

// Function declaration
extern void gpio_test(unsigned long timeout);

extern void SHTC3_test(unsigned long timeout);
extern void LPS22HB_test(unsigned long timeout);
extern void OPT3001_test(unsigned long timeout);
extern void LIS3DH_test(unsigned long timeout);
extern void bme680_test(unsigned long timeout);
extern void gps_test(unsigned long timeout);
extern void RAK12500_test(unsigned long timeout);

extern void ain0_4_20mA_test(unsigned long timeout);
extern void ain1_4_20mA_test(unsigned long timeout);
extern void RS485test(unsigned long timeout);
extern void ain_test(unsigned long timeout);

extern void RAK12003_test(unsigned long timeout);

extern void RAK15000_test(unsigned long timeout);
extern void RAK15001_test(unsigned long timeout);
extern void RAK18000_test(unsigned long timeout);
extern void RAK18001_test(unsigned long timeout);
extern void RAK19002_test(unsigned long timeout);

//V 1.0.8 Version update content.
extern void RAK13003_test(unsigned long timeout);
extern void RAK13004_test(unsigned long timeout);
extern void RAK14002_test(unsigned long timeout);

//V 1.0.9 Version update content.
extern void RAK15002_test(unsigned long timeout);
extern void RAK12002_test(unsigned long timeout);
extern void RAK17000_test(unsigned long timeout);
extern void RAK14001_test(unsigned long timeout);
extern void RAK13001_test(unsigned long timeout);

extern void RAK12005_test(unsigned long time_out);
extern void RAK12009_test(unsigned long time_out);
extern void RAK13005_test(unsigned long time_out);

//V 1.1.0 Version update content.   data:2021-07-30
extern void RAK12004_test(unsigned long timeout);
extern void RAK12006_test(unsigned long timeout);
extern void RAK12007_test(unsigned long timeout);
extern void RAK12010_test(unsigned long timeout);
extern void RAK12012_test(unsigned long timeout);
extern void RAK14003_test(unsigned long timeout);
extern void RAK13005_testS(unsigned long timeout);
extern void RAK13005_testR(unsigned long timeout);
extern void RAK14000_testB(unsigned long timeout);
extern void RAK14000_testR(unsigned long timeout);

//V 1.1.1 Version update content.   data:2021-08-26
extern void RAK12011_test(unsigned long timeout);
extern void RAK12015_test(unsigned long timeout);
extern void RAK12016_test(unsigned long timeout);
extern void RAK13101_test(unsigned long timeout);

//V 1.1.2 Version update content.   data:2021-09-27
extern void RAK12017_test(unsigned long timeout);
extern void RAK12018_test(unsigned long timeout);
extern void RAK14006_test(unsigned long timeout);
extern void RAK16000_test(unsigned long timeout);
extern void RAK16001_test(unsigned long timeout);

//V 1.1.3 Version update content.   data:2021-09-27
extern void RAK12019_test(unsigned long timeout);
extern void RAK12014_test(unsigned long timeout);
extern void RAK12025_test(unsigned long timeout);
extern void RAK13007_test(unsigned long timeout);
extern void RAK12035_test(unsigned long timeout);

//V 1.1.5 Version update content.   data:2021-12-10
extern void RAK12021_test(unsigned long timeout);
extern void RAK12013_test(unsigned long timeout);
extern void RAK13600_test(unsigned long timeout);
extern void RAK14004_test(unsigned long timeout);
extern void RAK12031_test(unsigned long timeout);

//V 1.1.7 Version update content.   data:2022-01-04
extern void RAK14009_test(unsigned long timeout);
extern void RAK14010_test(unsigned long timeout);
extern void RAK14011_test(unsigned long timeout);

//V 1.1.8 Version update content.   data:2022-01-17
extern void RAK12029_test(unsigned long timeout);
extern void RAK12001_test(unsigned long timeout);
extern void RAK14012_test(unsigned long timeout);

//V 1.1.9 Version update content.   data:2022-02-16
extern void RAK13800_test(unsigned long timeout);
extern void RAK14008_test(unsigned long timeout);
extern void RAK16002_test(unsigned long timeout);
extern void RAK14013_test(unsigned long timeout);

//V 1.2.1 Version update content.   data:2022-3-14
extern void RAK12032_test(unsigned long timeout);
extern void RAK12034_test(unsigned long timeout); 
extern void RAK12037_test(unsigned long timeout);
extern void RAK12040_test(unsigned long timeout);
extern void RAK12047_test(unsigned long timeout);

//V 1.2.2 Version update content.   data:2022-4-7
extern void RAK12022_test(unsigned long time_out);
extern void RAK12008_test(unsigned long time_out);
extern void RAK12044_test(unsigned long time_out);
extern void RAK12027_test(unsigned long time_out);
extern void RAK1905_test(unsigned long time_out);
extern void RAK12020_test(unsigned long time_out);

//V 1.2.3 Version update content.   data:2022-4-27
extern void RAK12033_test(unsigned long time_out);
extern void RAK13006_test(unsigned long time_out);
extern void RAK5814_test(unsigned long time_out);

//V 1.2.4 Version update content.   data:2022-5-23
extern void RAK15003_test(unsigned long time_out);
extern void RAK15004_test(unsigned long time_out);
extern void RAK17001_test(unsigned long time_out);
extern void RAK12054_test(unsigned long time_out);

//V 1.2.5 Version update content.   data:2022-7-4
extern void RAK12039_test(unsigned long time_out);
extern void RAK12052_test(unsigned long time_out);

//V 1.2.6 Version update content.   data:2022-9-26
extern void RAK15005_test(unsigned long time_out);
extern void RAK13801_test(unsigned long time_out);
extern void RAK13010_test(unsigned long time_out);

//V 1.2.7 Version update content.   data:2022-10-10
extern void RAK15006_test(unsigned long time_out);
// extern void RAK12063_test(unsigned long time_out);
extern void RAK14014_test(unsigned long time_out);

//V 1.2.8 Version update content.   data:2022-10-10
extern void RAK13011_test(unsigned long time_out);

//V 1.2.9 Version update content.   data:2023-10-15
extern void RAK12059_test(unsigned long time_out);
extern void RAK12067_test(unsigned long time_out);
extern void RAK13012_test(unsigned long time_out);


//V 1.3.0 Version update content.   data:2024-4-22
extern void RAK15007_test(unsigned long time_out);

//V 1.3.2 Version update content.   data:2025-6-29
extern void RAK12501_test(unsigned long time_out);
extern void RAK5860_test(unsigned long time_out);

//V 1.3.3 Version update RAK13101 test function.

// handler function pointer
typedef void (*test_cmd_handler)(unsigned long);

// cmd structure
typedef struct {
  char cmd[32];
  test_cmd_handler cmd_handler;
  unsigned long timeout;
} test_cmd_st;

// all test cmd
test_cmd_st test_cmd[] = {
  {"TEST GPIO", gpio_test, 0},

#ifdef RAK1901_MODULE
  {"TEST RAK1901", SHTC3_test, 0},
#endif

#ifdef RAK1902_MODULE
  {"TEST RAK1902", LPS22HB_test, 0},
#endif

#ifdef RAK1903_MODULE
  {"TEST RAK1903", OPT3001_test, 0},
#endif

#ifdef RAK1904_MODULE
  {"TEST RAK1904", LIS3DH_test, 0},
#endif

#ifdef RAK1906_MODULE
  {"TEST RAK1906", bme680_test, 0},
#endif

#ifdef RAK1910_MODULE
  {"TEST RAK1910", gps_test, 0},
#endif

#ifdef RAK12500_MODULE
  {"TEST RAK12500", RAK12500_test, 120000},
#endif

#ifdef RAK5801_MODULE
  {"TEST RAK5801-A0", ain0_4_20mA_test, 0},
  {"TEST RAK5801-A1", ain1_4_20mA_test, 0},
#endif

#ifdef RAK5802_MODULE
  {"TEST RAK5802", RS485test, 0},
#endif
#ifdef RAK5811_MODULE
  {"TEST RAK5811", ain_test, 0},
#endif

#ifdef RAK12003_MODULE
  {"TEST RAK12003", RAK12003_test, 5000},
#endif

#ifdef RAK15000_MODULE
  {"TEST RAK15000", RAK15000_test, 0},
#endif

#ifdef RAK15001_MODULE
  {"TEST RAK15001", RAK15001_test, 0},
#endif

#ifdef RAK18000_MODULE
  {"TEST RAK18000", RAK18000_test, 200},
#endif
#ifdef RAK18001_MODULE
  {"TEST RAK18001", RAK18001_test, 200},
#endif

#ifdef RAK19002_MODULE
  {"TEST RAK19002", RAK19002_test, 0},
#endif

  //V 1.0.8 Version update content.
#ifdef RAK13003_MODULE
  {"TEST RAK13003", RAK13003_test, 0},
#endif

#ifdef RAK13004_MODULE
  {"TEST RAK13004", RAK13004_test, 5000},
#endif

#ifdef RAK14002_MODULE
  {"TEST RAK14002", RAK14002_test, 15000},
#endif

  //V 1.0.9 Version update content.
#ifdef RAK15002_MODULE
  {"TEST RAK15002", RAK15002_test, 15000},
#endif

#ifdef RAK12002_MODULE
  {"TEST RAK12002", RAK12002_test, 0},
#endif

#ifdef RAK17000_MODULE
  {"TEST RAK17000", RAK17000_test, 0},
#endif

#ifdef RAK14001_MODULE
  {"TEST RAK14001", RAK14001_test, 0},
#endif

#ifdef RAK13001_MODULE
  {"TEST RAK13001", RAK13001_test, 0},
#endif
#ifdef RAK12005_MODULE
  {"TEST RAK12005", RAK12005_test, 5000},
#endif

#ifdef RAK12009_MODULE
  {"TEST RAK12009", RAK12009_test, 0},
#endif


  /*
     V 1.1.0 Version update content
  */
#ifdef RAK12004_MODULE
  {"TEST RAK12004", RAK12004_test, 0},
#endif

#ifdef RAK12006_MODULE
  {"TEST RAK12006", RAK12006_test, 10000},
#endif

#ifdef RAK12007_MODULE
  {"TEST RAK12007", RAK12007_test, 400},
#endif

#ifdef RAK12010_MODULE
  {"TEST RAK12010", RAK12010_test, 2000},
#endif

#ifdef RAK12012_MODULE
  {"TEST RAK12012", RAK12012_test, 20000},
#endif

#ifdef RAK13005_MODULE
  {"TEST RAK13005S", RAK13005_testS, 3000},
  {"TEST RAK13005R", RAK13005_testR, 3000},
#endif

#ifdef RAK14000_MODULE
  {"TEST RAK14000B", RAK14000_testB, 0},
  {"TEST RAK14000R", RAK14000_testR, 0},
#endif

#ifdef RAK14003_MODULE
  {"TEST RAK14003", RAK14003_test, 0},
#endif


  /*
     V 1.1.1 Version update content
  */
#ifdef RAK12011_MODULE
  {"TEST RAK12011", RAK12011_test, 0},
#endif

#ifdef RAK12015_MODULE
  {"TEST RAK12015", RAK12015_test, 3000},
#endif

#ifdef RAK12016_MODULE
  {"TEST RAK12016", RAK12016_test, 0},
#endif

#ifdef RAK13101_MODULE
  {"TEST RAK13101", RAK13101_test, 150000},
#endif

  /*
     V 1.1.2 Version update content
  */
#ifdef RAK12017_MODULE
  {"TEST RAK12017", RAK12017_test, 3000},
#endif

#ifdef RAK12018_MODULE
  {"TEST RAK12018", RAK12018_test, 3000},
#endif

#ifdef RAK14006_MODULE
  {"TEST RAK14006", RAK14006_test, 5000},
#endif

#ifdef RAK16000_MODULE
  {"TEST RAK16000", RAK16000_test, 0},
#endif

#ifdef RAK16001_MODULE
  {"TEST RAK16001", RAK16001_test, 0},
#endif

  /*
     V 1.1.3 Version update content
  */
#ifdef RAK12019_MODULE
  {"TEST RAK12019", RAK12019_test, 2000},
#endif

#ifdef RAK12014_MODULE
  {"TEST RAK12014", RAK12014_test, 2000},
#endif

#ifdef RAK13007_MODULE
  {"TEST RAK13007", RAK13007_test, 2000},
#endif

#ifdef RAK12025_MODULE
  {"TEST RAK12025", RAK12025_test, 2000},
#endif

#ifdef RAK12035_MODULE
  {"TEST RAK12035", RAK12035_test, 2000},
#endif

#ifdef RAK12023_MODULE
  {"TEST RAK12023", RAK12035_test, 2000},
#endif


  /*
     V 1.1.5 Version update content
  */
#ifdef RAK12021_MODULE
  {"TEST RAK12021", RAK12021_test, 2000},
#endif

#ifdef RAK12013_MODULE
  {"TEST RAK12013", RAK12013_test, 3000},
#endif

#ifdef RAK13600_MODULE
  {"TEST RAK13600", RAK13600_test, 3000},
#endif

//#ifdef RAK14004_MODULE
//  {"TEST RAK14004", RAK14004_test, 2000},
//#endif

#ifdef RAK12031_MODULE
  {"TEST RAK12031", RAK12031_test, 5000},
#endif


  /*
     V 1.1.7 Version update content
  */
#ifdef RAK14004_MODULE
  {"TEST RAK14009", RAK14009_test, 20000},
  {"TEST RAK14010", RAK14010_test, 20000},
  {"TEST RAK14011", RAK14011_test, 20000},
#endif

  /*
     V 1.1.8 Version update content
  */
#ifdef RAK12029_MODULE
  {"TEST RAK12029", RAK12029_test, 2000},
#endif

#ifdef RAK12001_MODULE
  {"TEST RAK12001", RAK12001_test, 6000},
#endif

#ifdef RAK14012_MODULE
  {"TEST RAK14012", RAK14012_test, 6000},
#endif

  /*
     V 1.1.9 Version update content
  */
#ifdef RAK13800_MODULE
  {"TEST RAK13800", RAK13800_test, 10000},
#endif

#ifdef RAK14008_MODULE
    {"TEST RAK14008", RAK14008_test, 0},
#endif

#ifdef RAK16002_MODULE
    {"TEST RAK16002", RAK16002_test, 0},
#endif

#ifdef RAK14013_MODULE
    {"TEST RAK14013", RAK14013_test, 15000},
#endif

#ifdef RAK12032_MODULE
    {"TEST RAK12032", RAK12032_test, 0},
#endif

#ifdef RAK12034_MODULE
    {"TEST RAK12034", RAK12034_test, 0},
#endif

#ifdef RAK12037_MODULE
    {"TEST RAK12037", RAK12037_test, 3000},
#endif

#ifdef RAK12040_MODULE
    {"TEST RAK12040", RAK12040_test, 3000},
#endif

#ifdef RAK12047_MODULE
    {"TEST RAK12047", RAK12047_test, 0},
#endif
  /*
     V 1.2.2 Version update content
  */
#ifdef RAK12022_MODULE
  {"TEST RAK12022", RAK12022_test, 0},
#endif
  
#ifdef RAK12008_MODULE
  {"TEST RAK12008", RAK12008_test, 0},
#endif

#ifdef RAK12044_MODULE
  {"TEST RAK12044", RAK12044_test, 0},
#endif

#ifdef RAK12027_MODULE
  {"TEST RAK12027", RAK12027_test, 0},
#endif

#ifdef RAK1905_MODULE
  {"TEST RAK1905", RAK1905_test, 0},
#endif

#ifdef RAK12020_MODULE
  {"TEST RAK12020", RAK12020_test, 0},
#endif

  /*
     V 1.2.3 Version update content
  */
#ifdef RAK12033_MODULE
  {"TEST RAK12033", RAK12033_test, 0},
#endif

#ifdef RAK13006_MODULE
  {"TEST RAK13006", RAK13006_test, 5000},
#endif

#ifdef RAK5814_MODULE
  {"TEST RAK5814", RAK5814_test, 0},
#endif

  /*
     V 1.2.4 Version update content
  */
#ifdef RAK15003_MODULE
  {"TEST RAK15003", RAK15003_test, 0},
#endif

#ifdef RAK15004_MODULE
  {"TEST RAK15004", RAK15004_test, 0},
#endif

#ifdef RAK17001_MODULE
  {"TEST RAK17001", RAK17001_test, 0},
#endif

#ifdef RAK12054_MODULE
  {"TEST RAK12054", RAK12054_test, 0},
#endif

  /*
     V 1.2.5 Version update content
  */
#ifdef RAK12039_MODULE
  {"TEST RAK12039", RAK12039_test, 0},
#endif
#ifdef RAK12052_MODULE
  {"TEST RAK12052", RAK12052_test, 0},
#endif

  /*
     V 1.2.6 Version update content
  */
#ifdef RAK15005_MODULE
  {"TEST RAK15005", RAK15005_test, 0},
#endif
#ifdef RAK13801_MODULE
  {"TEST RAK13801", RAK13801_test, 0},
#endif
#ifdef RAK13010_MODULE
  {"TEST RAK13010", RAK13010_test, 0},
#endif

  /*
     V 1.2.7 Version update content
  */
#ifdef RAK15006_MODULE
  {"TEST RAK15006", RAK15006_test, 0},
#endif

// #ifdef RAK12063_MODULE
//   {"TEST RAK12063", RAK12063_test, 5000},
// #endif

#ifdef RAK14014_MODULE
  {"TEST RAK14014", RAK14014_test, 0},
#endif

  /*
     V 1.2.8 Version update content
  */
#ifdef RAK13011_MODULE
  {"TEST RAK13011", RAK13011_test, 0},
#endif

  /*
     V 1.2.9 Version update content
  */
#ifdef RAK12059_MODULE
  {"TEST RAK12059", RAK12059_test, 0},
#endif
#ifdef RAK12067_MODULE
  {"TEST RAK12067", RAK12067_test, 0},
#endif
#ifdef RAK13012_MODULE
  {"TEST RAK13012", RAK13012_test, 0},
#endif


  /*
     V 1.3.0 Version update content
  */
#ifdef RAK15007_MODULE
  {"TEST RAK15007", RAK15007_test, 0},
#endif

  /*
     V 1.3.2 Version update content
  */
#ifdef RAK5860_MODULE
  {"TEST RAK5860", RAK5860_test, 0},
#endif
#ifdef RAK12501_MODULE
  {"TEST RAK12501", RAK12501_test, 0},
#endif

  /*
     V 1.3.3 Version update RAK13101 test function.
  */


  
};

// all cmd num
uint32_t test_cmd_num = sizeof(test_cmd) / sizeof(test_cmd_st);

#endif
