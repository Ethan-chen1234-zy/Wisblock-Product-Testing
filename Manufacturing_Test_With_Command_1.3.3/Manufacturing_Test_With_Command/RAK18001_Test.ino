#ifdef RAK18001_MODULE

#include "Production_test_configure.h"

//Slot A: WB_IO1 17
//Slot B: WB_IO2 34
//Slot C: WB_IO3 21
//Slot D: WB_IO5 9
#define PWM_FOSC  16000000    //PWM的时钟频率为16MHz
void RAK18001_init()
{
  pinMode(WB_IO1,OUTPUT);
  pinMode(WB_IO2,OUTPUT);
 // pinMode(WB_IO3, OUTPUT); 
 // pinMode(WB_IO5, OUTPUT); 

  HwPWM0.addPin(WB_IO1);
  HwPWM0.addPin(WB_IO2);  
 // HwPWM0.addPin(WB_IO3);
 // HwPWM0.addPin(WB_IO5); 
  
//  HwPWM0.setResolution(4); // set max value by 2^bitnum - 1
//  HwPWM0.setMaxValue(4000-1);   // set max value = 16000000/pwm_frequency - 1
  buzzer(4000); //4000Hz
  HwPWM0.stop();
}
void buzzer(unsigned long freq)
{
  unsigned long duty = 0;
  unsigned long pwm_period = 0;
  pwm_period = PWM_FOSC/freq-1;
  duty = PWM_FOSC/freq/2;
  HwPWM0.setMaxValue(pwm_period);   // set max value = 16000000/pwm_frequency - 1
  
  HwPWM0.writePin(WB_IO1,duty,false);
  HwPWM0.writePin(WB_IO2,duty,false);
 // HwPWM0.writePin(WB_IO3,duty,false);
 // HwPWM0.writePin(WB_IO5,duty,false);
//  HwPWM0.stop();
}
void RAK18001_test(unsigned long time_out)
{
  RAK18001_init();
  
  RAK18000_test(time_out); 
  
//  RAK18001_init();
//  HwPWM0.stop();
//  unsigned long time_now = millis();
//  while( (millis()-time_now) < time_out)
//  {
//    buzzer(4000);
//    delay(200);
//    HwPWM0.stop();
//    delay(100);
//  }
//   HwPWM0.stop();  
}

const int buzzer_pin = 17;
void buzzer_init()
{
  pinMode(buzzer_pin, OUTPUT);
}
void buzzer_tick(unsigned t)
{ 
  tone(buzzer_pin, t);
  delay(t);   //Here it is used to adjust the delay according to the beat. The 500 index can be adjusted by myself. In this music, I find that 500 is more suitable.
  noTone(buzzer_pin);
}
void buzzer_test(unsigned long time_out)
{
  unsigned i = 0;
  buzzer_init();
  unsigned long time_now = millis();
  while ( (millis() - time_now) < time_out)
  {
    for (i = 0; i < 10000; i++)
    {
      Serial.println(i);
      buzzer_tick(i);
      //       delay(20);
    }
  }
}

#endif
