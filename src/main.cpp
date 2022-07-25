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
bool changeND = false;
bool ChangeColour = false;

uint16_t SetApature = 0;
uint16_t Gain = 0;


void Buttion_1()
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > debounceTime)
  {
    CheckFucntion = true;
  }
  last_interrupt_time = interrupt_time;
}
void Buttion_2()
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > debounceTime)
  {
    Serial.println("Bution 2 Pushed");
    SetApature = F2_8;
  }
  last_interrupt_time = interrupt_time;
}
void Buttion_3()
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > debounceTime)
  {
    Serial.println("Buttion 3 Pushed");
    SetApature = F4_0;
  }
  last_interrupt_time = interrupt_time;
}
void Buttion_4()
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > debounceTime)
  {
    Serial.println("Buttion 4 Pushed");
    SetApature = F5_6;
  }
  last_interrupt_time = interrupt_time;
}
void Buttion_5()
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > debounceTime)
  {
    Serial.println("Buttion 5 Pushed");
    changeShutter = true;
    changeND = true;
    ChangeColour = true;
  }
  last_interrupt_time = interrupt_time;
}
void A_Button()
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > debounceTime)
  {
    Serial.println("Buttion A Pressed");
    Gain = G0;
  }
  last_interrupt_time = interrupt_time;
}
void B_Buttion()
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > debounceTime)
  {
    Serial.println("Buttion B Pressed");
    Gain = G3;
  }
  last_interrupt_time = interrupt_time;
}
void C_Buttion()
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > debounceTime)
  {
    Serial.println("Buttion C Pressed");
    Gain = G6;
  }
  last_interrupt_time = interrupt_time;
}
void D_Buttion()
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > debounceTime)
  {
    Serial.println("Buttion D Pressed");
    Gain = G9;
  }
  last_interrupt_time = interrupt_time;
}
void E_Buttion()
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > debounceTime)
  {
    Serial.println("Buttion E Pressed");
    Gain = G12;
  }
  last_interrupt_time = interrupt_time;
}
void F_Buttion()
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > debounceTime)
  {
    Serial.println("Buttion F Pressed");
    Gain = G15;
  }
  last_interrupt_time = interrupt_time;
}
void G_Buttion()
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > debounceTime)
  {
    Serial.println("Buttion G Pressed");
    Gain = G18;
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
  attachInterrupt(BUTTION_1, Buttion_1, FALLING);

  pinMode(BUTTION_2, INPUT_PULLUP);
  attachInterrupt(BUTTION_2, Buttion_2, FALLING);

  pinMode(BUTTION_3, INPUT_PULLUP);
  attachInterrupt(BUTTION_3, Buttion_3, FALLING);

  pinMode(BUTTION_4, INPUT_PULLUP);
  attachInterrupt(BUTTION_4, Buttion_4, FALLING);

  pinMode(BUTTION_5, INPUT_PULLUP);
  attachInterrupt(BUTTION_5, Buttion_5, FALLING);

  pinMode(BUTTION_A, INPUT_PULLUP);
  attachInterrupt(BUTTION_A, A_Button, FALLING);

  pinMode(BUTTION_B, INPUT_PULLUP);
  attachInterrupt(BUTTION_B, B_Buttion, FALLING);

  pinMode(BUTTION_C, INPUT_PULLUP);
  attachInterrupt(BUTTION_C, C_Buttion, FALLING);

  pinMode(BUTTION_D, INPUT_PULLUP);
  attachInterrupt(BUTTION_D, D_Buttion, FALLING);

  pinMode(BUTTION_E, INPUT_PULLUP);
  attachInterrupt(BUTTION_E, E_Buttion, FALLING);

  pinMode(BUTTION_F, INPUT_PULLUP);
  attachInterrupt(BUTTION_F, F_Buttion, FALLING);

  pinMode(BUTTION_G, INPUT_PULLUP);
  attachInterrupt(BUTTION_G, G_Buttion, FALLING);
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
  if (Gain)
  {
    camera.setGain(Gain);
    Gain = 0;
  }
  
}
void setND()
{
  if (changeND)
  {
    camera.setND();
    changeND = false;
  }
  
}
void setColourTemp()
{
  if (ChangeColour)
  {
    camera.setWhiteKelv();
    ChangeColour = false;
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
  setND();
  setColourTemp();
  changeCameraGain();
}

void printArray(char array[])
{
  char *arrayPtr = array;
  arrayPtr++;
  Serial.print(arrayPtr);
}
