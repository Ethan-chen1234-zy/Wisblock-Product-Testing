#ifdef RAK13007_MODULE

void RAK13007_test(unsigned long timeout)
{
    //Sensor power switch
  pinMode(WB_IO2, OUTPUT);
  digitalWrite(WB_IO2, HIGH);
  pinMode(WB_IO4, OUTPUT);
  digitalWrite(WB_IO4, LOW);
  delay(300);

  Serial.println("Relay OFF");
  
  digitalWrite(WB_IO4, LOW);
  delay(3000);

  Serial.println("Relay ON");
  digitalWrite(WB_IO4, HIGH);
  delay(3000);
}
#endif
