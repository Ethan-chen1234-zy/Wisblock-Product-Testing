#ifdef RAK5860_MODULE

void RAK5860_init()
{
  pinMode(WB_IO2, OUTPUT); 
  digitalWrite(WB_IO2, HIGH);

  pinMode(WB_IO1, OUTPUT); 
  digitalWrite(WB_IO1, HIGH);
}
void RAK5860_test(unsigned long timeout)
{
  RAK5860_init();
  digitalWrite(WB_IO1, HIGH);
  Serial.println("RAK5860 Power on!");
  delay(1000);
  digitalWrite(WB_IO1, LOW);
}
#endif
