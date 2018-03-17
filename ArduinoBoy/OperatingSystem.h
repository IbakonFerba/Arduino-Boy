#pragma once

#ifndef OPERATING_SYSTEM_H
#define OPERATING_SYSTEM_H

#include "stdafx.h"
#include "Observer.h"
#include "Input.h"
#include "Display.h"
#include "ArduinoBoyProgram.h"
#include "Text.h"

#include "Snake.h"
#include "Paint.h"
#include "BreakOut.h"

enum class OSState {
  MENU,
  TRANSITION,
  PROGRAM
};



class OperatingSystem : public Observer {
  public:
    OperatingSystem() {}
    OperatingSystem(const Input* ptrInputManager);

    void updateOS(const float& rDeltaTime, Display& rDisplay);

    void notify(const Message& rMessage) override;
  private:
    Input* m_ptr_inputManager;
    OSState m_state;


    //==============================
    //menu
    const float TIME_TO_HOLD_BUTTONS_FOR_MENU = 1.0f;

    byte m_buttonsPressed;
    float m_menuButtonsTimeHeld;

    void checkReturnToMenu(const float& rDeltaTime);

    void nextProgram();
    void prevProgram();
    void drawMenu(Display& rDisplay) const;
    //==============================



    //==============================
    //transition
    Text m_transitionText;

    void startTransition();

    void updateTransition(const float& rDeltaTime);
    void drawTransition(Display& rDisplay) const;
    //==============================



    //==============================
    //programs
    static const byte NUM_OF_PROGRAMS = 3;
    ArduinoBoyProgram* m_programs[NUM_OF_PROGRAMS] = {new Snake(), new Paint(), new BreakOut()};

    byte m_selectedProgram;

    void startActiveProgram();
    void stopActiveProgram();
    void updateProgram(const float& rDeltaTime);
    void renderProgram(Display& rDisplay) const;
    //==============================
};

#endif
