#include <Arduino.h>
#include <ME200S.hpp>
#define debounceTime 200
void printArray(char array[]);
#ifdef VERSION_ONE

#define BUTTION_1 11
#define BUTTION_2 8
#define BUTTION_3 5
#define BUTTION_4 3
#define BUTTION_5 2
#define BUTTION_A A0
#define BUTTION_B A1
#define BUTTION_C A2
#define BUTTION_D A3
#define BUTTION_E A5
#define BUTTION_F A7
#define BUTTION_G 10
#endif
#ifndef VERSION_ONE
#define BUTTION_1 A4
#define BUTTION_2 A3
#define BUTTION_3 A2
#define BUTTION_4 A1
#define BUTTION_5 A0
#define BUTTION_A 5
#define BUTTION_B 6
#define BUTTION_C 7
#define BUTTION_D 9
#define BUTTION_E 10
#define BUTTION_F 11
#define BUTTION_G 12
#endif
ME200S camera;

bool CheckFucntion = false;
bool AutoFocus = false;
bool oneShotAF = false;
bool changeShutter = false;
bool changeGain = false;
uint16_t SetApature = 0;
void checkButton()
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > debounceTime)
  {
    CheckFucntion = true;
  }
  last_interrupt_time = interrupt_time;
}
void autoFocusButton()
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > debounceTime)
  {
    Serial.println("Auto Focus Button Pressed");
    AutoFocus = true;
  }
  last_interrupt_time = interrupt_time;
}
void setGainButton()
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > debounceTime)
  {
    Serial.println("set gain Button Pressed");
    changeGain = true;
  }
  last_interrupt_time = interrupt_time;
}
void shutterControlButton()
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > debounceTime)
  {
    Serial.println("Shutter Control Button Pressed");
    changeShutter = true;
  }
  last_interrupt_time = interrupt_time;
}
void oneShotAFButton()
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > debounceTime)
  {
    Serial.println("One Shot AF Button Pressed");
    oneShotAF = true;
  }
  last_interrupt_time = interrupt_time;
}
void f2_8Button()
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > debounceTime)
  {
    Serial.println("F2.8 Button Pressed");
    SetApature = F2_8;
  }
  last_interrupt_time = interrupt_time;
}
void F4_0Button()
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > debounceTime)
  {
    Serial.println("F4.0 Button Pressed");
    SetApature = F4_0;
  }
  last_interrupt_time = interrupt_time;
}
void F5_6Button()
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > debounceTime)
  {
    Serial.println("F5.6 Button Pressed");
    SetApature = F5_6;
  }
  last_interrupt_time = interrupt_time;
}
void F8_0Button()
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > debounceTime)
  {
    Serial.println("F 8.0 Button Pressed");
    SetApature = F8;
  }
  last_interrupt_time = interrupt_time;
}
void F11Button()
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > debounceTime)
  {
    Serial.println("F11 Button Pressed");
    SetApature = F11;
  }
  last_interrupt_time = interrupt_time;
}
void F16Button()
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > debounceTime)
  {
    Serial.println("F16 Button Pressed");
    SetApature = F16;
  }
  last_interrupt_time = interrupt_time;
}
void F22Button()
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > debounceTime)
  {
    Serial.println("F22 Button Pressed");
    SetApature = F22;
  }
  last_interrupt_time = interrupt_time;
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
  delay(1000);
  Serial.println("Setup Started");
  pinMode(BUTTION_1, INPUT_PULLUP);
  attachInterrupt(BUTTION_1, checkButton, FALLING);

  pinMode(BUTTION_2, INPUT_PULLUP);
  attachInterrupt(BUTTION_2, autoFocusButton, FALLING);

  pinMode(BUTTION_3, INPUT_PULLUP);
  attachInterrupt(BUTTION_3, setGainButton, FALLING);

  pinMode(BUTTION_4, INPUT_PULLUP);
  attachInterrupt(BUTTION_4, shutterControlButton, FALLING);

  pinMode(BUTTION_5, INPUT_PULLUP);
  attachInterrupt(BUTTION_5, oneShotAFButton, FALLING);

  pinMode(BUTTION_A, INPUT_PULLUP);
  attachInterrupt(BUTTION_A, f2_8Button, FALLING);

  pinMode(BUTTION_B, INPUT_PULLUP);
  attachInterrupt(BUTTION_B, F4_0Button, FALLING);

  pinMode(BUTTION_C, INPUT_PULLUP);
  attachInterrupt(BUTTION_C, F5_6Button, FALLING);

  pinMode(BUTTION_D, INPUT_PULLUP);
  attachInterrupt(BUTTION_D, F8_0Button, FALLING);

  pinMode(BUTTION_E, INPUT_PULLUP);
  attachInterrupt(BUTTION_E, F11Button, FALLING);

  pinMode(BUTTION_F, INPUT_PULLUP);
  attachInterrupt(BUTTION_F, F16Button, FALLING);

  pinMode(BUTTION_G, INPUT_PULLUP);
  attachInterrupt(BUTTION_G, F22Button, FALLING);
  Serial.println("Setup Completed");
}

void checkFunction()
{
  if (CheckFucntion)
  {
    if (camera.cameraVersionRequest())
    {
      Serial.print("Camera Versions: ");
      camera.printArray();
    }
    else
    {
      Serial.println();
      Serial.println("Failed to get camera version");
    }
    CheckFucntion = false;
  }
}
void setApature()
{
  if (SetApature)
  {
    bool success = false;
    // for (auto i = 0; i < 10; i++)
    {
      /* code */
      // while (!success)
      {
        Serial.println("Setting Aparture");
        // success = camera.setApature(SetApature);
        success = camera.setApatureBlocking(SetApature);
      } // send set apature until successful
    }
        SetApature = 0;
        // delay(1000);
        Serial.println("Getting Apature");
    camera.irisPossition();
    // Serial.println("Iris Possition: ");
    // camera.printArray();
    // camera.printArrayDirect();
  }
}
void setAutoFocus()
{
  if (AutoFocus)
  {
    camera.AutoFocus(true);
    AutoFocus = false;
  }
}
void oneShotFocus()
{
  if (oneShotAF)
  {
    camera.oneShotAF();
    oneShotAF = false;
  }
}
void setShutterSpeed()
{
  if (changeShutter)
  {
    camera.setShutter();
    changeShutter = false;
  }
  
}
void changeCameraGain()
{
  if (changeGain)
  {
    camera.setGain();
    changeGain = false;
  }
  
}
void loop()
{
  // delay(1000);
  // CheckFucntion = true;
  checkFunction();

  setApature();
  /* code */

  setAutoFocus();
  oneShotFocus();
  setShutterSpeed();
  changeCameraGain();
}

void printArray(char array[])
{
  char *arrayPtr = array;
  arrayPtr++;
  Serial.print(arrayPtr);
}
