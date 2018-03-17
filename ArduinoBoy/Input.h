#pragma once

#ifndef INPUT_H
#define INPUT_H

#include "stdafx.h"
#include "Subject.h"

class Input : public Subject {
  public:
    Input();

    getInput();
  private:
    //==============================
    //define pins for buttons
    static const byte LEFT = 1;
    static const byte RIGHT = 0;
    static const byte UP = 3;
    static const byte DOWN = 2;
    //==============================



    //==============================
    //input values from previous frame
    byte m_prevLeftVal;
    byte m_prevRightVal;
    byte m_prevUpVal;
    byte m_prevDownVal;
    //==============================
};

#endif
