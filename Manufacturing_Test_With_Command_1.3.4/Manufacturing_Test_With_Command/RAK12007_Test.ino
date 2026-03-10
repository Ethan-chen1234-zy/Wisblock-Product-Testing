#ifdef RAK12007_MODULE
#include <Wire.h>
#include <Adafruit_GFX.h>   //Click here to get the library: http://librarymanager/All#Adafruit_GFX
#include <Adafruit_SSD1306.h>   //Click here to get the library: http://librarymanager/All#Adafruit_SSD1306

#ifdef RAK4630
#define BOARD "RAK4631 "
#define  RAK4631_BOARD true
#else
#define  RAK4631_BOARD false
#endif

#define TRIG WB_IO6
#define ECHO WB_IO4
#define PD   WB_IO5   //power done control （=1 power done，=0 power on） 

#define TIME_OUT  24125 //max measure distance is 4m,the velocity of sound is 331.6m/s in 0℃,TIME_OUT=4*2/331.6*1000000=24215us

float ratio = 346.6 / 1000 / 2; //velocity of sound =331.6+0.6*25℃(m/s),(Indoor temperature about 25℃)

long int duration_time();  //measure high level time

void RAK12007_init()
{
  pinMode(ECHO, INPUT);   // Echo Pin of Ultrasonic Sensor is an Input
  pinMode(TRIG, OUTPUT);  // Trigger Pin of Ultrasonic Sensor is an Output
  pinMode(PD, OUTPUT);    // power done control pin is an Output
  digitalWrite(TRIG, LOW);
  digitalWrite(PD, LOW);
  pinMode(LED_BLUE, OUTPUT);   // The LED is an Output
  duration_time();
  delay(1000);
}
void RAK12007_test(unsigned long timeout)
{
  long int duration, mm;
  digitalWrite(LED_BLUE, HIGH);
  RAK12007_init();
  unsigned long time_now = millis();
  while ( (millis() - time_now) < timeout)
  {
    duration = duration_time();
    if (duration > 0)
    {
      mm = duration * ratio; //Test distance = (high level time×velocity of sound (340M/S) / 2,
      digitalWrite(LED_BLUE, LOW);
      Serial.print(mm);
      Serial.print("mm");
      Serial.println();
    }
    else
    {
      Serial.println("Out of range");
    }
    delay(100);
  }
}
long int duration_time()
{
  long int respondTime;
  pinMode(TRIG, OUTPUT);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(12);   //pull high time need over 10us
  digitalWrite(TRIG, LOW);
  pinMode(ECHO, INPUT);
  respondTime = pulseIn(ECHO, HIGH); // microseconds
  delay(33);
  if (RAK4631_BOARD)
  {
    respondTime = respondTime * 0.7726; // Time calibration factor is 0.7726,to get real time microseconds for 4631board
  }
  //   Serial.printf("respond time is %d\r\n",respondTime);

  if ((respondTime > 0) && (respondTime < TIME_OUT)) //ECHO pin max timeout is 33000us according it's datasheet
  {
    return respondTime;
  }
  else
  {
    return -1;
  }
}
#endif
