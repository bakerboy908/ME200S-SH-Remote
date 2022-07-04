#include <Arduino.h>
#include <ME200S.hpp>

void printArray(char array[]);

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000);
  Serial.println("Sending Status request in 5 seconds");
}

void loop()
{
  // put your main code here, to run repeatedly:

  delay(5000);
  ME200S camera;
  if (camera.cameraVersionRequest())
  {

    char data[10];
    camera.receivedData(data);
    Serial.print("Camera Versions: ");
    printArray(data);
  }
  else
  {
    Serial.println();
    Serial.println("Failed to get camera version");
  }

}

void printArray(char array[])
{
  char *arrayPtr = array;
  while (arrayPtr != NULL)
  {
    Serial.print(*arrayPtr);
    arrayPtr++;
  }
}
