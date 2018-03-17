#pragma once

#ifndef PAINT_H
#define PAINT_H

#include "stdafx.h"
#include "ArduinoBoyProgram.h"

enum class BrushMovement {
  NONE,
  UP,
  DOWN,
  LEFT,
  RIGHT
};

enum class BrushMode {
  MOVE,
  DRAW,
  ERASE
};

class Paint : public ArduinoBoyProgram, public Observer {
  public:
    Paint();

    //==============================
    //ArduinoBoyProgram functions
    void startProgram(Input* ptrInputManager) override;
    void stopProgram(Input* ptrInputManager) override;

    void updateProgram(const float& rDeltaTime) override;
    void renderProgram(Display& rDisplay) const override;
    //==============================


    //==============================
    //Observer
    void notify(const Message& rMessage) override;
    //==============================
  private:
    //==============================
    //general
    byte m_canvas[HEIGHT];
   
    void reset();
    //==============================


    //==============================
    //brush
    const float BRUSH_BLINK_INTERVAL = 0.5f;
    float m_brushBlinkTimer;

    const float BRUSH_MOVEMENT_INTERVAL = 0.2f;
    float m_brushMovementTimer;

    BrushMovement m_brushMovement;
    BrushMode m_brushMode;

    byte m_brushRow;
    byte m_brushCol;

    byte m_drawComboHeld;
    byte m_eraseComboHeld;

    byte m_drawComboHeldPrev;
    byte m_eraseComboHeldPrev;

    void moveBrush(const float& rDeltaTime);
    //==============================



    //==============================
    //program info
    void setMenuInfo() {
      title = "Paint";

      byte ic[HEIGHT] = {131, 197, 227, 113, 56, 25, 6, 0};
      for (byte row = 0; row < HEIGHT; ++row) {
        icon[row] = ic[row];
      }
    }
    //==============================
};

#endif
