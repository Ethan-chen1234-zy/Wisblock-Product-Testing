#ifdef RAK12052_MODULE

#include <Adafruit_MLX90640.h> // Click here to get the library: http://librarymanager/All#Adafruit_MLX90640

Adafruit_MLX90640 mlx;
//float frame[32*24]; // buffer for full frame of temperatures

void RAK12052_test(unsigned long timeout)
{
  pinMode(WB_IO2, OUTPUT);
  digitalWrite(WB_IO2, HIGH); 

  if (!mlx.begin(MLX90640_I2CADDR_DEFAULT, &Wire)) 
  {
    Serial.printf("RAK12052 Test Failed\n");
    return;
  }
  Serial.printf("RAK12052 Test OK\n");
  return;
//  delay(500);
//  if (mlx.getFrame(frame) != 0) 
//  {
//    Serial.printf("RAK12052 Test Failed\n");
//    return;
//  }
//
//  if((frame[0]< -20) || (frame[0]> 60))
//  {
//    Serial.println("Temperature:");
//    Serial.print(frame[0]);
//    Serial.println(" [C]"); 
//    Serial.printf("RAK12052 Test OK\n");
//    return;
//  }
//  Serial.printf("RAK12052 Test Failed\n");
//  return;
}
#endif
