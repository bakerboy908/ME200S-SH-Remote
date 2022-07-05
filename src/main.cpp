#include <Arduino.h>
#include <ME200S.hpp>
#define debounceTime 200
void printArray(char array[]);
#define CHECK_BUTTON_PIN 11
#define AUTO_FOCUS_PIN 8
#define SET_BUTTON_PIN 5
#define SHUTTER_COONTROL_BUTTON_PIN 3
#define ONESHOT_AF_BUTTON_PIN 2
#define F2_8_BUTTON_PIN A0
#define F4_0_BUTTON_PIN A1
#define F5_6_BUTTON_PIN A2
#define F8_0_BUTTON_PIN A3
#define F11_BUTTON_PIN A5
#define F16_BUTTON_PIN A7
#define F22_BUTTON_PIN 10

ME200S camera;

bool CheckFucntion = false;
bool AutoFocus = false;
bool oneShotAF = false;
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
void setButton()
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > debounceTime)
  {
    Serial.println("set Button Pressed");
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
  delay(1000);
  Serial.println("Setup Started");
  pinMode(CHECK_BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(CHECK_BUTTON_PIN, checkButton, FALLING);

  pinMode(AUTO_FOCUS_PIN, INPUT_PULLUP);
  attachInterrupt(AUTO_FOCUS_PIN, autoFocusButton, FALLING);

  pinMode(SET_BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(SET_BUTTON_PIN, setButton, FALLING);

  pinMode(SHUTTER_COONTROL_BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(SHUTTER_COONTROL_BUTTON_PIN, shutterControlButton, FALLING);

  pinMode(ONESHOT_AF_BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(ONESHOT_AF_BUTTON_PIN, oneShotAFButton, FALLING);

  pinMode(F2_8_BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(F2_8_BUTTON_PIN, f2_8Button, FALLING);

  pinMode(F4_0_BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(F4_0_BUTTON_PIN, F4_0Button, FALLING);

  pinMode(F5_6_BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(F5_6_BUTTON_PIN, F5_6Button, FALLING);

  pinMode(F8_0_BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(F8_0_BUTTON_PIN, F8_0Button, FALLING);

  pinMode(F11_BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(F11_BUTTON_PIN, F11Button, FALLING);

  pinMode(F16_BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(F16_BUTTON_PIN, F16Button, FALLING);

  pinMode(F22_BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(F22_BUTTON_PIN, F22Button, FALLING);
  Serial.println("Setup Completed");
}

void checkFunction()
{
  if (CheckFucntion)
  {
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
    CheckFucntion = false;
  }
}
void setApature()
{
  if (SetApature)
  {
    camera.setApature(SetApature);
    SetApature = 0;
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
{if (oneShotAF)
{
  camera.oneShotAF();
  oneShotAF = false;
}

}
void loop()
{
  checkFunction();
  setApature();
  setAutoFocus();
  oneShotFocus();

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
