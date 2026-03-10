#ifdef RAK19002_MODULE

#include "Production_test_configure.h"

//Slot A: WB_IO1 17
//Slot B: WB_IO2 34
//Slot C: WB_IO3 21
//Slot D: WB_IO5 9
void RAK19002_test(unsigned long timeout)
{
  pinMode(17, OUTPUT);
  pinMode(34, OUTPUT);
  pinMode(21, OUTPUT);
  pinMode(9, OUTPUT);

  digitalWrite(17, HIGH);
  digitalWrite(34, HIGH);
  digitalWrite(21, HIGH);
  digitalWrite(9, HIGH);
}
#endif
