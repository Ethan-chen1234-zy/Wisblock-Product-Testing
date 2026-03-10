#ifdef RAK15002_MODULE

#include "SPI.h"
#include <SD.h>   //http://librarymanager/All#SD

#define FILE_NAME "RAK15002.txt"

char WriteBuf[20]="Hello World!\n";
char ReadBuf[20]={0};
/**
   @brief  This function is used to read data from file. 
*/
void readFile(const char * path)
{
  int cnt = 0;
  Serial.printf("Reading file: %s\n", path);
  
  File file = SD.open(path, FILE_READ); // re-open the file for reading.
  if (file) 
  {
    Serial.println("Read from file: ");
    
    while (file.available()) 
    {
      ReadBuf[cnt] = file.read();
      //Serial.write(file.read());  // read from the file until there's nothing else in it.
      cnt++;
    }
    Serial.write(ReadBuf);
    file.close(); // close the file.
  } 
  else 
  {
    Serial.println("Failed to open file for reading."); // if the file didn't open, print an error.
    return;
  }
}
/**
   @brief  This function is used to write data to file. 
*/
void writeFile(const char * path, const char * message)
{
  Serial.printf("Writing file: %s\n", path);

  File file = SD.open(path, FILE_WRITE);

  if (file) // if the file opened okay, write to it:
  {
    if(file.print(message))
    {
      Serial.println("File written.");
    } 
    else 
    {
      Serial.println("Write failed.");
    }
    file.close();
  } 
  else 
  {
    Serial.println("Failed to open file for writing."); 
    return;
  }
}

/**
   @brief  This function is used to delete file. 
*/
void deleteFile(const char * path)
{
  Serial.printf("Deleting file: %s\n", path);
  
  SD.remove(path);
}


void RAK15002_test(unsigned long timeout)
{
  if (!SD.begin()) 
  {    
    Serial.printf("RAK15002 Test Failed\n");
    return;
  }
  
  deleteFile(FILE_NAME); 
  
  writeFile(FILE_NAME , WriteBuf);
  
  readFile(FILE_NAME);

  if(strcmp(WriteBuf, ReadBuf) == 0)
  {
    Serial.printf("RAK15002 Test OK\n");
  }
  else 
  {
    Serial.printf("RAK15002 Test Failed\n");
  }
}
#endif
