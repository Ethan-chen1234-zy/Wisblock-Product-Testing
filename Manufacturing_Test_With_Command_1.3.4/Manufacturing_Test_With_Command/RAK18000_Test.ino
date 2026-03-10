#ifdef RAK18000_MODULE

#include "Production_test_configure.h"
#include <PDM.h>  //I2S

//#define PDM_DATA_PIN  24    //first vesion hardware IO
//#define PDM_CLK_PIN   25
//#define PDM_PWR_PIN   -1

#define PDM_DATA_PIN  21  //second vesion hardware IO
#define PDM_CLK_PIN   4
#define PDM_PWR_PIN   -1

// buffer to read samples into, each sample is 16-bits
short sampleBuffer[256] = {0};
// number of samples read
volatile int samplesRead = 0;

short max_value = 0;
short min_value = 0;
  
void RAK18000_test(unsigned long time_out) 
{ 
  RAK18001_init();
  PDM.setPins(PDM_DATA_PIN, PDM_CLK_PIN, PDM_PWR_PIN);
  PDM.setBufferSize(256);
  // configure the data receive callback
  PDM.onReceive(onPDMdata);
  // optionally set the gain, defaults to 20
  PDM.setGain(20);   
  // initialize PDM with:
  // - 2 means stereo, 1 means single
  // - a 16 kHz sample rate
  if (!PDM.begin(2, PCM_16000)) 
  {
//    Serial.println("Failed to start PDM!");    
    Serial.printf("RAK18000 Test Failed\n");    
  }
  else
  {  
    unsigned long time_now = millis();
    while( (millis()-time_now) < 1000)
    {   
      for (int i = 0; i < samplesRead; i++) 
      { 
        sampleBuffer[i] = 0;
      }
      // clear the read count
      samplesRead = 0;
    } 
    buzzer(4000);  
    time_now = millis();
//    unsigned long time_now = millis();
    while( (millis()-time_now) < time_out)
    {
//      buzzer(4000);       
      RAK18000_read();
    }
    Serial.println(min_value);
    Serial.println(max_value); 
    max_value = 0;
    min_value = 0;   
    HwPWM0.stop();   
//    Serial.printf("RAK18000 Test OK\n");  
  }
   PDM.end();
} 
void RAK18000_read() 
{
    for (int i = 0; i < samplesRead; i++) 
    {  //Simple filtering, if less than 200, it will be regarded as noise
        if(sampleBuffer[i] <= 600 && sampleBuffer[i] >= -600)
        {
          sampleBuffer[i] = 0;
        } 
        else
        {          
          max_value = sampleBuffer[i];
          if(sampleBuffer[i] < min_value)
          {
            min_value = sampleBuffer[i];
          }
          if(sampleBuffer[i] > max_value)
          {
            max_value = sampleBuffer[i];
          }          
        }            
    }
    // clear the read count
    samplesRead = 0;
//    Serial.println(min_value);
//    Serial.println(max_value);   
}
void onPDMdata() {
  // query the number of bytes available
  int bytesAvailable = PDM.available();
  // read into the sample buffer
  PDM.read((uint8_t *)sampleBuffer, bytesAvailable);
  // 16-bit, 2 bytes per sample
  samplesRead = bytesAvailable / 2;
}

#endif
