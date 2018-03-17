#pragma once

#ifndef ARDUINO_BOY_PROGRAM
#define ARDUINO_BOY_PROGRAM

#include "stdafx.h"
#include "Input.h"
#include "Display.h"

class ArduinoBoyProgram {
  public:
    ArduinoBoyProgram() {}
    virtual ~ArduinoBoyProgram() {}

    String title = "";
    byte icon[HEIGHT] = {0, 0, 0, 0, 0, 0, 0, 0};

    virtual void startProgram(Input* ptrInputManager) = 0; //set all observers in here
    virtual void stopProgram(Input* ptrInputManager) = 0; //remove all observers in here

    virtual void updateProgram(const float& rDeltaTime) = 0;
    virtual void renderProgram(Display& rDisplay) const = 0;
};

#endif
