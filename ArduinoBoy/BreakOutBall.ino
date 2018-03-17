#include "stdafx.h"
#include "BreakOutBall.h"


//------------------------------------------
//update
void BreakOutBall::updateBall(const float& rDeltaTime, const BreakOutPlatform& rPlatform) {
  m_pos += (m_vel * rDeltaTime);

  if (m_pos.x <= 0 || m_pos.x >= WIDTH) {
    m_vel.x *= -1;
  }
  if (m_pos.y <= 0) {
    m_vel.y *= -1;
  }

  if (m_pos.y >= HEIGHT) {
    m_observerMessage.type = MessageType::BREAK_OUT_BALL_DIED;
    notifyObservers();
  }

  rPlatform.checkBall(m_pos, m_vel);
}


//------------------------------------------
//render
void BreakOutBall::draw(Display& rDisplay) const {
  rDisplay.draw(floor(m_pos.x), floor(m_pos.y));
}


//------------------------------------------
//setter
void BreakOutBall::setPos(const Vector2& pos) {
  m_pos.x = pos.x;
  m_pos.y = pos.y;
}

void BreakOutBall::setVel(const float& x, const float& y) {
  m_vel.x = x;
  m_vel.y = y;
}

void BreakOutBall::multVel(const float& factorX, const float& factorY) {
  m_vel.x *= factorX;
  m_vel.y *= factorY;
}

//------------------------------------------
//getter
const Vector2& BreakOutBall::getPos() const {
  return m_pos;
}

const Vector2 BreakOutBall::getNextPos(const float& rDeltaTime) const {
  return m_pos + m_vel * rDeltaTime;
}

