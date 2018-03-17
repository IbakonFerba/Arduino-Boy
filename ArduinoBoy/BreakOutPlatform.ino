#include "stdafx.h"
#include "BreakOutPlatform.h"


//------------------------------------------
//reset
void BreakOutPlatform::reset() {
  m_pos.x = 4;

  movementDir = MovementDir::NONE;
}


//------------------------------------------
//move
void BreakOutPlatform::moveLR(const float& rDeltaTime) {
  switch (movementDir) {
    case MovementDir::LEFT:
        if (m_pos.x - EXTENDS > 1) {
          m_pos.x -= rDeltaTime * MOVEMENT_SPEED;
        }
      break;
    case MovementDir::RIGHT:
      if(m_pos.x + EXTENDS < WIDTH - 1) {
        m_pos.x += rDeltaTime * MOVEMENT_SPEED;
      }
      break;
  }

  movementDir = MovementDir::NONE;
}

//------------------------------------------
//ball
void BreakOutPlatform::checkBall(const Vector2& rPos, Vector2& rVel) const{
  byte ballPosY = floor(rPos.y);

  if(ballPosY != floor(m_pos.y)) {
    return;
  }

  byte ballPosX = floor(rPos.x);
  byte posX = floor(m_pos.x);

  if(ballPosX > posX - EXTENDS && ballPosX < posX + EXTENDS) {
    rVel.y *= -1;
  } else if(ballPosX == posX - EXTENDS) {
    rVel.y *= -1;
    rVel.rotate(-RELFECTION_ANGLE_SIDES, true);
  } else if(ballPosX == posX + EXTENDS) {
    rVel.y *= -1;
    rVel.rotate(RELFECTION_ANGLE_SIDES, true);
  }
}

//------------------------------------------
//draw
void BreakOutPlatform::draw(Display& rDisplay) const {
  for (int i = -EXTENDS; i <= EXTENDS; ++i) {
    rDisplay.draw(floor(m_pos.x) + i, floor(m_pos.y));
  }
}


//------------------------------------------
//getter
const Vector2& BreakOutPlatform::getPos() const {
  return m_pos;
}

