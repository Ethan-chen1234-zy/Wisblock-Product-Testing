#ifdef RAK5801_MODULE

#include "Production_test_configure.h"

/*********************************4-20mA****RAK5801**test***start***************************/
void ain0_4_20mA_test(unsigned long timeout)
{
  int mcu_ain_value;
  float voltage_ain;
  float current;
  int current_int;

  /*
     WisBLOCK IO 3v3_S Power On
  */
  pinMode(34, OUTPUT);
  digitalWrite(34, HIGH);

  /*
     WisBLOCK RAK5801/RAK5811 12V Power On
  */
  pinMode(17, OUTPUT);
  digitalWrite(17, HIGH);

  pinMode(4, INPUT_PULLDOWN);  // set pull-down on IO4
  analogReference(AR_DEFAULT);

  delay(100);
  analogOversampling(128);

  delay(200);
  mcu_ain_value = analogRead(4);
  voltage_ain = mcu_ain_value * 3.6 / 1024;
  current = voltage_ain / 149 * 1000;
  current_int = (int)(current + 0.5);

  Serial.printf("-----------AIN0 current_int = %d-----------\n", current_int);

  if ( 4 ==  current_int)
  {
    Serial.printf("-----------RAK5801 AIN0 Test OK!-----------\n");
  }
  else
  {
    Serial.printf("-----------RAK5801 AIN0 Test Failed!-----------\n");
  }
}

void ain1_4_20mA_test(unsigned long timeout)
{
  int mcu_ain_value;
  float voltage_ain;
  float current;
  int current_int;

  /*
     WisBLOCK IO 3v3_S Power On
  */
  pinMode(34, OUTPUT);
  digitalWrite(34, HIGH);

  /*
     WisBLOCK RAK5801/RAK5811 Power On
  */
  pinMode(17, OUTPUT);
  digitalWrite(17, HIGH);

  pinMode(A1, INPUT_PULLDOWN);  // set pull-up on analog pin 1
  analogReference(AR_DEFAULT);

  delay(100);
  analogOversampling(128);

  delay(200);
  mcu_ain_value = analogRead(A1);
  voltage_ain = mcu_ain_value * 3.6 / 1024;
  current = voltage_ain / 149 * 1000;
  current_int = (int)(current + 0.5);
  //Serial.printf("\n-----------4-20mA Test-----------\n");

  Serial.printf("-----------AIN1 current_int = %d-----------\n");

  if ( 4 ==  current_int)
  {
    Serial.printf("-----------RAK5801 AIN1 Test OK!-----------\n");
  }
  else
  {
    Serial.printf("-----------RAK5801 AIN1 Test Failed!-----------\n");
  }
}
/*********************************4-20mA****RAK5801**test***end***************************/

#endif
