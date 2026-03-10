#ifdef RAK14006_MODULE

#define ENCODER_A_PIN WB_IO6  //clockwise
#define ENCODER_B_PIN WB_IO4  //anticlockwise
#define SWITCH_PIN    WB_IO5  //press key
//position is 0 when start up
uint8_t RAK14006_Flag[3] = {0};
bool press_flag = false;
bool clockwise_flag = false;
bool anticlockwise_flag = false;


void handle_1() {
  press_flag = true;
}
void handle_2() {
  clockwise_flag = true;
}
void handle_3() {
  anticlockwise_flag = true;
}

void RAK14006_Init(void)
{
  //setup our pins
  pinMode(ENCODER_A_PIN, INPUT);
  pinMode(ENCODER_B_PIN, INPUT);
  pinMode(SWITCH_PIN, INPUT);

  attachInterrupt(SWITCH_PIN, handle_1, FALLING);
  attachInterrupt(ENCODER_A_PIN, handle_2, RISING);
  attachInterrupt(ENCODER_B_PIN, handle_3, RISING);
  //setup our serial
  Serial.println("Please first turn the button clockwise, then counterclockwise, finally press the button!!");
}
void RAK14006_test(unsigned long timeout)
{
  RAK14006_Init();
  unsigned long time_now = millis();
  while ((millis() - time_now) < timeout)
  {
    if (press_flag == true)
    {
      press_flag = false;
      RAK14006_Flag[0] = 1;
    }
    if (clockwise_flag == true)
    {
      clockwise_flag = false;
      RAK14006_Flag[1] = 1;
    }
    if (anticlockwise_flag == true)
    {
      anticlockwise_flag = false;
      RAK14006_Flag[2] = 1;
    }
  }
  if (RAK14006_Flag[0] == 1 && RAK14006_Flag[1] == 1 && RAK14006_Flag[2] == 1)
  {
    Serial.printf("RAK14006 Test OK!\n");
    memset(RAK14006_Flag,0,sizeof(RAK14006_Flag)/sizeof(uint8_t));
  }
  else
  {
    Serial.printf("RAK14006 Test Failed!\n");
  }
}
#endif
