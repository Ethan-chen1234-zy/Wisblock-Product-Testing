#ifdef RAK17000_MODULE

#define MOTOR_AIN1  SCK        
#define MOTOR_AIN2  SS     
#define MOTOR_BIN1  WB_IO3  
#define MOTOR_BIN2  MOSI   
#define MOTOR_SLEEP WB_IO6

void RAK17000_init(void)
{
  // Enable DRV8833 output.
  pinMode(MOTOR_SLEEP, OUTPUT); 
  digitalWrite(MOTOR_SLEEP, HIGH);

  pinMode(MOTOR_AIN1, OUTPUT);
  pinMode(MOTOR_AIN2, OUTPUT);
  pinMode(MOTOR_BIN1, OUTPUT);
  pinMode(MOTOR_BIN2, OUTPUT);

}

void RAK17000_test(unsigned long timeout)
{
  RAK17000_init();

  digitalWrite(MOTOR_AIN2, LOW);
  digitalWrite(MOTOR_BIN2, LOW); 
  digitalWrite(MOTOR_AIN1, HIGH);
  digitalWrite(MOTOR_BIN1, HIGH);
  delay(2000);

  digitalWrite(MOTOR_AIN2, HIGH);
  digitalWrite(MOTOR_BIN2, HIGH); 
  digitalWrite(MOTOR_AIN1, LOW);
  digitalWrite(MOTOR_BIN1, LOW);
  delay(2000);
  
  digitalWrite(MOTOR_AIN2, LOW);
  digitalWrite(MOTOR_BIN2, LOW); 
  digitalWrite(MOTOR_AIN1, LOW);
  digitalWrite(MOTOR_BIN1, LOW);
}

#endif
