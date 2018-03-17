#pragma once

#ifndef BREAK_OUT_PLATFORM_H
#define BREAK_OUT_PLATFORM_H

#include "stdafx.h"
#include "Vector2.h"

enum class MovementDir {
  NONE,
  LEFT,
  RIGHT
};

class BreakOutPlatform {
  public:
    BreakOutPlatform() : m_pos(4, HEIGHT - 1) {}

    MovementDir movementDir;

    void reset();

    void moveLR(const float& rDeltaTime);

    void draw(Display& rDisplay) const;

    void checkBall(const Vector2& rPos, Vector2& rVel) const;

    const Vector2& getPos() const;
  private:
    const float MOVEMENT_SPEED = 10.0f;
    const byte EXTENDS = 1;
    const byte RELFECTION_ANGLE_SIDES = 20;

    Vector2 m_pos;
};

#endif
