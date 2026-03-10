#ifdef RAK17001_MODULE

#define STSPIN250_PH           WB_IO4        //the PH pin determines the direction of the current
#define STSPIN250_PWM          WB_IO3        //the PWM pin can be used to regulate the speed of the rotation
#define STSPIN250_FAULT_CHECK  WB_IO5
#define STSPIN250_EN           WB_IO6

void RAK17001_init(void)
{
  pinMode(WB_IO2, OUTPUT);
  digitalWrite(WB_IO2, HIGH);
  delay(300);
  
  pinMode(STSPIN250_PH, OUTPUT);
  digitalWrite(STSPIN250_PH, HIGH);

  pinMode(STSPIN250_PWM, OUTPUT);
  digitalWrite(STSPIN250_PWM, LOW);

  pinMode(STSPIN250_EN, OUTPUT);
  digitalWrite(STSPIN250_EN, HIGH);
}

void RAK17001_test(unsigned long timeout)
{
  RAK17001_init();

  digitalWrite(STSPIN250_PH, HIGH);
  analogWrite(STSPIN250_PWM, 200);
  delay(2000);

  analogWrite(STSPIN250_PWM, 0);
  delay(1000);
  
  digitalWrite(STSPIN250_PH, LOW);
  analogWrite(STSPIN250_PWM, 200);
  delay(2000);
  analogWrite(STSPIN250_PWM, 0);
}

#endif
