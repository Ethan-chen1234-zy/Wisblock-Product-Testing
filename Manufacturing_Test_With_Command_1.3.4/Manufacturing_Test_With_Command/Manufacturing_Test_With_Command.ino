
#include "Production_test_configure.h"

/*********************************GPIO**test***start***************************/
void gpio_test(unsigned long timeout)
{
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  pinMode(14, INPUT_PULLDOWN);
  if (!digitalRead(14))
  {
    Serial.printf("-----------P0.13 or P0.14 Test Failed!-----------\n");
  }

  pinMode(15, OUTPUT);
  digitalWrite(15, HIGH);
  pinMode(16, INPUT_PULLDOWN);
  if (!digitalRead(16))
  {
    Serial.printf("-----------P0.15 or P0.16 Test Failed!-----------\n");
  }

  pinMode(17, OUTPUT);
  digitalWrite(17, HIGH);
  pinMode(19, INPUT_PULLDOWN);
  if (!digitalRead(19))
  {
    Serial.printf("-----------P0.17 or P0.19 Test Failed!-----------\n");
  }

  pinMode(21, OUTPUT);
  digitalWrite(21, HIGH);
  pinMode(20, INPUT_PULLDOWN);
  if (!digitalRead(20))
  {
    Serial.printf("-----------P0.21 or P0.20 Test Failed!-----------\n");
  }

  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
  pinMode(10, INPUT_PULLDOWN);
  if (!digitalRead(10))
  {
    Serial.printf("-----------P0.09 or P0.10 Test Failed!-----------\n");
  }

  pinMode(25, OUTPUT);
  digitalWrite(25, HIGH);
  pinMode(24, INPUT_PULLDOWN);
  if (!digitalRead(24))
  {
    Serial.printf("-----------P0.25 or P0.24 Test Failed!-----------\n");
  }

  pinMode(26, OUTPUT);
  digitalWrite(26, HIGH);
  pinMode(30, INPUT_PULLDOWN);
  if (!digitalRead(30))
  {
    Serial.printf("-----------P0.26 or P0.30 Test Failed!-----------\n");
  }

  pinMode(29, OUTPUT);
  digitalWrite(29, HIGH);
  pinMode(28, INPUT_PULLDOWN);
  if (!digitalRead(28))
  {
    Serial.printf("-----------P0.29 or P0.28 Test Failed!-----------\n");
  }

  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  pinMode(2, INPUT_PULLDOWN);
  if (!digitalRead(2))
  {
    Serial.printf("-----------P0.03 or P0.02 Test Failed!-----------\n");
  }

  pinMode(36, OUTPUT);
  digitalWrite(36, HIGH);
  pinMode(35, INPUT_PULLDOWN);
  if (!digitalRead(35))
  {
    Serial.printf("-----------P1.04 or P1.03 Test Failed!-----------\n");
  }

  pinMode(34, OUTPUT);
  digitalWrite(34, HIGH);
  pinMode(33, INPUT_PULLDOWN);
  if (!digitalRead(33))
  {
    Serial.printf("-----------P1.02 or P1.01 Test Failed!-----------\n");
  }

  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  pinMode(5, INPUT_PULLDOWN);
  if (!digitalRead(5))
  {
    Serial.printf("-----------P0.04 or P0.05 Test Failed!-----------\n");
  }

  pinMode(31, INPUT_PULLDOWN);
  if (!digitalRead(31))
  {
    Serial.printf("-----------P0.04 or P0.31 Test Failed!-----------\n");
  }
}
/*********************************GPIO**test***end***************************/

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(300);
  }
  time_t timeout = millis();
  while (!Serial)
  {
    if ((millis() - timeout) < 5000)
    {
      delay(100);
    }
    else
    {
      break;
    }
  }
  Serial.println("=====================================");
  Serial.println("Manufacturing Test");
  Serial.println(VERSION);
  Serial.println("=====================================");
#ifdef RAK12500_MODULE
  pinMode(WB_IO2, OUTPUT);
  digitalWrite(WB_IO2, 0);
  delay(1000);
  digitalWrite(WB_IO2, 1);
#endif

}

void loop() {
  String command = "";

  Serial.printf("\nPlease insert Command!!! \n");
  while (!Serial.available()) {
    delay(200);
  };

  while (Serial.available() > 0) {
    command += char(Serial.read());
    delay(10);
  }

  Serial.println(command);

  for (int i = 0; i < test_cmd_num; i++)
  {
    if (String(test_cmd[i].cmd) == command && test_cmd[i].cmd_handler != NULL)
    {
      Serial.print("\nSTART ");
      Serial.println(String(test_cmd[i].cmd));
      delay(5);
      test_cmd[i].cmd_handler(test_cmd[i].timeout);
      Serial.printf("TEST OVER\n");
      break;
    }
    else if (i == test_cmd_num - 1)
    {
      Serial.printf("\nError Command!!!\n");
    }
  }
}
