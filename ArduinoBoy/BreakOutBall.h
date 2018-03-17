#pragma once

#ifndef BREAK_OUT_BALL_H
#define BREAK_OUT_BALL_H

#include "stdafx.h"
#include "Vector2.h"
#include "Subject.h"

#include "BreakOutPlatform.h"

class BreakOutBall : public Subject {
  public:
    BreakOutBall() {}

    const float BALL_SPEED = 6.5f;

    void updateBall(const float& rDeltaTime, const BreakOutPlatform& rPlatform);

    void draw(Display& rDisplay) const;


    void setPos(const Vector2& pos);
    void setVel(const float& x, const float& y);
    void multVel(const float& factorX, const float& factorY);

    const Vector2& getPos() const;
    const Vector2 getNextPos(const float& rDeltaTime) const;
  private:
    Vector2 m_pos;
    Vector2 m_vel;
};

#endif
