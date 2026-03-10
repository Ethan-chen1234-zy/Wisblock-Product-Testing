#ifdef RAK1910_MODULE

#include "Production_test_configure.h"
#include <SoftwareSerial.h>

/***************************GPS*****RAK1910********test*******start*****************/
#define PRINT_GPS(str)  Serial.print(F("[GPS] ")); Serial.print(str);

#define GPS_BUFFER_SIZE 160
#define TIMEOUT 120
#define IO4 4

bool status;
char state[2];
bool signal_status = 0;

void RAK1910_rec_nmea(const char *nmea_name, char *_dataBuffer)
{
  char dummyBuffer[7] = "";
  uint8_t i = 0;
  bool valid = 0;
  bool end = 0;

  //_dataBuffer = (char *)malloc(GPS_BUFFER_SIZE);
  if (_dataBuffer == NULL)
  {
    Serial.println("_dataBuffer failed");
  }

  unsigned long previous = millis();
  while ( (!valid) && (millis() - previous) < 2000)
  {
    if (Serial1.available() > 0)
    {
      dummyBuffer[0] = Serial1.read();
      if (dummyBuffer[0] == '$')
      {
        //read five bytes
        while ((Serial1.available() < 5) && (millis() - previous) < 2000);
        for (i = 1; i < 6; i++)
        {
          dummyBuffer[i] = Serial1.read();
        }
        dummyBuffer[6] = '\0';

        //char aux[10] ="";
        //strcpy_P(aux, (char*)pgm_read_word(nmea_name));
        //strcmp returns '0' if both equal
        //if(!strcmp(dummyBuffer, aux) )
        if (!strcmp(dummyBuffer, nmea_name) )
        {
          valid = 1;
        }
      }
    }
    //avoid millis overflow problem
    if ( millis() < previous ) previous = millis();
  }

  if (valid)
  {
    previous = millis();
    i = 0;
    while ((!end) && (i < 82) &&  (millis() - previous) < 2000)
    {
      // read the GPS sentence
      if (Serial1.available() > 0)
      {
        _dataBuffer[i] = Serial1.read();
        if (_dataBuffer[i] == '*' || _dataBuffer[i] == '$')
        {
          // end of NMEA or new one.
          end = 1;
          _dataBuffer[i + 1] = '\0';
        }
        i++;
      }
      //avoid millis overflow problem
      if ( millis() < previous ) previous = millis();
    }
  }
  //PRINT_GPS(F("inbuffer: "));
  //Serial.println(_dataBuffer);
}

bool RAK1910_check()
{
  char *argument;
  char *_dataBuffer;
  char _dataBuffer2[GPS_BUFFER_SIZE];

  _dataBuffer = (char *)malloc(GPS_BUFFER_SIZE);
  RAK1910_rec_nmea("$GPRMC", _dataBuffer);

  memset(_dataBuffer2, 0x00, sizeof(_dataBuffer2));
  strncpy(_dataBuffer2, _dataBuffer, strlen(_dataBuffer));
  _dataBuffer2[strlen(_dataBuffer)] = '\0';

  free(_dataBuffer);

  //first of all, look if connected
  argument = strtok (_dataBuffer2, ",");
  //strcmp returns '0' if both equal
  if (!strcmp(argument, "V") )
  {
    strncpy(state, argument, strlen(argument));
    state[strlen(argument)] = '\0';
  }
  else
  {
    // status
    argument = strtok(NULL, ",");
    strncpy(state, argument, strlen(argument));
    state[strlen(argument)] = '\0';
  }

  if (state[0] == 'A')
  {
    return 1;
  }
  else
  {
    if (state[0] == 'V')
    {
      return 0;
    }
    // If state is not V and it is not connected, must be an error parsing
    return -1;
  }
}

bool RAK1910_check_status()
{
  unsigned long previous = millis();
  // Wait here till timeout or status=connected
  while ((!signal_status) && (millis() - previous) < 5000)
  {
    // Updates global status
    signal_status = RAK1910_check();

    //avoid millis overflow problem
    if ( millis() < previous ) previous = millis();
  }

  if (signal_status == 1)
    return 1;
  else
    return 0;
}

bool RAK1910_wait_for_signal(unsigned long timeout)
{
  unsigned long initTime = millis();
  unsigned long time = 0;
  bool status = 0;

  while (!status && (time < timeout * 1000))
  {
    status = RAK1910_check_status();
    delay(100);
    time = millis() - initTime;

    //avoid millis overflow problem
    if ( millis() < initTime ) initTime = millis();

    PRINT_GPS(F("status_waitforsignal = "));
    Serial.println(status);
  }
  return status;
}

String RAK1910_comdata = "";
void gps_test(unsigned long timeout)
{
  pinMode(17, OUTPUT);
  digitalWrite(17, HIGH);

  pinMode(34, OUTPUT);
  digitalWrite(34, 0);
  delay(1000);
  digitalWrite(34, 1);
  delay(1000);

  Serial1.begin(9600);
  while (!Serial1);
  //Serial.println("gps uart init ok!");
  delay(500);

  int i = 10000;
  while (i--)
  {
    if (Serial1.available() > 0 )
    {
      // get the byte data from the GPS
      RAK1910_comdata += char(Serial1.read());
      //delay(1);
    }
  }
  if (RAK1910_comdata == "")
  {
    Serial.printf("-----------RAK1910 Test Failed!-----------\n");
  }
  else
  {
    status = RAK1910_wait_for_signal(TIMEOUT);
    if ( status == true )
    {
      Serial.printf("-----------RAK1910 Test OK!-----------\n");
    }
    else
    {
      Serial.printf("-----------RAK1910 Test Failed!-----------\n");
    }
  }
}
/**************************GPS******RAK1910*******test*******end*******************************/

#endif
