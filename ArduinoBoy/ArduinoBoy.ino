#include "stdafx.h"
#include "Display.h"
#include "Input.h"
#include "OperatingSystem.h"

/* By FABIAN KOBER
 * 
 * This sketch is the software for the ArduinBoy by FABIAN KOBER.
 * 
 * If you want to write a program for the ArduinoBoy that works with the
 * existing OS, just inherit a class from ArduinoBoyProgram and add an instance of it
 * to the m_programs arra in OperatingSystem.h
 */

float prevTime = 0;

Display disp;
Input* inputManager;

OperatingSystem* OS;

void setup() {
  //Serial.begin(9600); //uncomment if you need to print to the serial monitor

  //Setup input manager
  inputManager = new Input();

  //Setup OS
  OS = new OperatingSystem(inputManager);
}

void loop() {
  //==============================
  //delta time
  float dt = micros() - prevTime;
  dt /= 1000000;
  prevTime = micros();
  //==============================


  //==============================
  //input
  inputManager->getInput();
  //==============================

  //==============================
  //update and render programs
  OS->updateOS(dt, disp);
  //==============================

  //==============================
  //rendering
  disp.render();
  disp.clearDisplay();
  //==============================
}
