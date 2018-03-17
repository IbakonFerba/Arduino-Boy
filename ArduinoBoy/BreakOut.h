#pragma once

#ifndef BREAK_OUT_H
#define BREAK_OUT_H

#include "stdafx.h"
#include "ArduinoBoyProgram.h"

#include "BreakOutPlatform.h"
#include "BreakOutBall.h"

class BreakOut : public ArduinoBoyProgram, public Observer {
  public:
    BreakOut();

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
    GameState m_state;

    void reset();
    void resetField();
    //==============================

    //==============================
    //bricks
    byte m_brickField[HEIGHT];

    void checkBrickCollision(const float& rDeltaTime);
    //==============================


    //==============================
    //player
    const byte MAX_LIFES = 3;
    byte m_lifes;

    BreakOutPlatform m_platform;
    BreakOutBall m_ball;

    bool m_ballHeld;
    //==============================

    //==============================
    //gameover
    const float GAME_OVER_UPDATE_INTERVAL = 0.05f;
    float m_gameOverTimer;

    byte m_currentGameOverRow;

    void updateGameOver(const float& rDeltaTime);
    //==============================

    //==============================
    //winning
    byte wonScreen[HEIGHT] = {0,36,36,36,36,24,24,0};

    const float WON_UPDATE_INTERVAL = 0.05f;
    float m_wonTimer;

    byte m_wonOffset;


    void checkWon();
    void updateWon(const float& rDeltaTime);
    //==============================

    //==============================
    //program info
    void setMenuInfo() {
      title = "Break-out";

      byte ic[HEIGHT] = {247, 226, 192, 0, 16, 0, 0, 14};
      for (byte row = 0; row < HEIGHT; ++row) {
        icon[row] = ic[row];
      }
    }
    //==============================
};

#endif
