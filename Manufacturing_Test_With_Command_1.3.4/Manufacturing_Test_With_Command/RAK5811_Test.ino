#ifdef RAK5811_MODULE

#include "Production_test_configure.h"

/*********************************0-5V****RAK5811**test***start***************************/
void ain_test(unsigned long timeout)
{
  float voltage_ain = 0;
  float voltage = 0;

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
  pinMode(A1, INPUT_PULLDOWN);  // set pull-down on analog pin 1
  analogReference(AR_INTERNAL_3_0);
  analogOversampling(128);

  delay(200);
  //mcu_ain_value = analogRead(A0);
  int mcu_ain_value = 0;
  int average_value = 0;
  average_value = analogRead(4);
  voltage_ain = average_value * 3.0 / 1024;
  voltage = voltage_ain / 0.6;
  //voltage = (int)(voltage / 0.1) * 0.1;

  Serial.printf("-----------raw = %d-----------\n", mcu_ain_value);
  Serial.printf("-----------AIN0 voltage = %f V-----------\n", voltage);

  //if( 33 == (int)(voltage * 10) )
  if (  voltage >= 3.2 && voltage <= 3.4)   //Modify the test success range to ±0.1 By：Michael Time:2021-4-25 14:26:49
  {
    Serial.printf("-----------RAK5811 AIN0 Test OK!-----------\n");
  }
  else
  {
    Serial.printf("-----------RAK5811 AIN0 Test Failed!-----------\n");
  }

  delay(200);
  mcu_ain_value = 0;
  average_value = 0;
  average_value = analogRead(A1);
  voltage_ain = average_value * 3.0 / 1024;
  voltage = voltage_ain / 0.6;
  //voltage = (int)(voltage / 0.1) * 0.1;

  Serial.printf("-----------AIN1 voltage = %f V-----------\n", voltage);

  if (  voltage >= 3.2 && voltage <= 3.4)   //Modify the test success range to ±0.1 By：Michael Time:2021-4-25 14:26:49
  {
    Serial.printf("-----------RAK5811 AIN1 Test OK!-----------\n");
  }
  else
  {
    Serial.printf("-----------RAK5811 AIN1 Test Failed!-----------\n");
  }
}
/*********************************0-5V****RAK5811**test***end***************************/

#endif
