#pragma once

#ifndef SNAKE_H
#define SNAKE_H

#include "stdafx.h"
#include "ArduinoBoyProgram.h"

#include "SnakeSegment.h"

enum class Direction {
  UP,
  DOWN,
  LEFT,
  RIGHT
};

class Snake : public ArduinoBoyProgram, public Observer {
  public:
    Snake();

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
    byte m_playField[HEIGHT];
    GameState m_state;

    void clearField();
    byte getCell(const byte& rRow, const byte& rCol) const;

    void reset();
    //==============================

    //==============================
    //snake
    SnakeSegment* snake = NULL;

    Direction m_movementDir;
    const float MOVEMENT_INTERVAL = 0.35f;
    float m_movementTimer;

    void resetSnake();
    void moveSnake(const float& rDeltaTime);
    //==============================

    //==============================
    //bait
        byte m_baitField[HEIGHT];
    const float BAIT_INTERVAL = 3.0f;
    float m_baitTimer;

    void spawnBait();
    byte getBaitCell(const byte& rRow, const byte& rCol) const;

    //==============================

    //==============================
    //gameover
    const float GAME_OVER_UPDATE_INTERVAL = 0.05f;
    float m_gameOverTimer;

    byte m_currentGameOverRow;

    void updateGameOver(const float& rDeltaTime);
    //==============================


    //==============================
    //program info
    void setMenuInfo() {
      title = "Snake";

      byte ic[HEIGHT] = {0, 30, 2, 126, 64, 104, 0, 0};
      for (byte row = 0; row < HEIGHT; ++row) {
        icon[row] = ic[row];
      }
    }
    //==============================
};

#endif
