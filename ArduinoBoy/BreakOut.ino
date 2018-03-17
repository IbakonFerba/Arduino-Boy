#include "stdafx.h"
#include "BreakOut.h"

//------------------------------------------
//constructor
BreakOut::BreakOut() {
  setMenuInfo();

  m_ball.addObserver(this);
}


//------------------------------------------
//setup
void BreakOut::startProgram(Input* ptrInputManager) {
  ptrInputManager->addObserver(this);
  reset();
}

void BreakOut::stopProgram(Input* ptrInputManager) {
  ptrInputManager->removeObserver(this);
}

void BreakOut::reset() {
  m_lifes = MAX_LIFES;
  m_platform.reset();
  resetField();

  m_ballHeld = true;

  m_currentGameOverRow = 0;
  m_gameOverTimer = 0;

  m_wonTimer = 0;
  m_wonOffset = HEIGHT;

  m_state = GameState::PLAYING;
}


void BreakOut::resetField() {
  for (byte row = 0; row < HEIGHT; ++row) {
    m_brickField[row] = row < HEIGHT / 2 ? 255 : 0; //fill the upper half with bricks
  }
}


//------------------------------------------
//update
void BreakOut::updateProgram(const float& rDeltaTime) {
  if (m_state == GameState::PLAYING) {
    m_platform.moveLR(rDeltaTime);

    if (m_ballHeld) {
      //set ball position to the middle and one above the paltform
      const Vector2& platformPos = m_platform.getPos();
      const Vector2 newBallPos(platformPos.x, platformPos.y - 1);
      m_ball.setPos(newBallPos);
    } else {
      //udpate ball and check bricks
      m_ball.updateBall(rDeltaTime, m_platform);
      checkBrickCollision(rDeltaTime);
    }
  } else if (m_state == GameState::GAME_OVER) {
    updateGameOver(rDeltaTime);
  } else if (m_state == GameState::WON) {
    updateWon(rDeltaTime);
  }
}


void BreakOut::checkBrickCollision(const float& rDeltaTime) {
  const Vector2& ballPos = m_ball.getPos();
  const Vector2 nextBallPos = m_ball.getNextPos(rDeltaTime);

  byte ballPosX = floor(ballPos.x);
  byte ballPosY = floor(ballPos.y);

  byte nextBallPosX = floor(nextBallPos.x);
  byte nextBallPosY = floor(nextBallPos.y);

  if (nextBallPosY < HEIGHT && nextBallPosX < WIDTH) {
    if (((m_brickField[nextBallPosY] >> nextBallPosX) & 1) == 1) { //this menas the ball would hit a brick
      m_brickField[nextBallPosY] = m_brickField[nextBallPosY] ^ (1 << nextBallPosX); //Delete brick
      checkWon();

      //let ball bounce off
      int ballVelMultX = 1;
      int ballVelMultY = 1;
      if (nextBallPosX < ballPosX || nextBallPosX > ballPosX) {
        ballVelMultX = -1;
      } else if (nextBallPosY < ballPosY || nextBallPosY > ballPosY) {
        ballVelMultY = -1;
      }

      m_ball.multVel(ballVelMultX, ballVelMultY);
    }
  }
}


//------------------------------------------
//render
void BreakOut::renderProgram(Display& rDisplay) const {
  if (m_wonOffset > 0) {
    rDisplay.setScreen(m_brickField);
    m_platform.draw(rDisplay);
    m_ball.draw(rDisplay);
  }

  if (m_state == GameState::WON) {
    for (unsigned row = 0; row < HEIGHT; ++row) {
      for (unsigned col = 0; col < WIDTH; ++col) {
        if ((wonScreen[row] >> col) & 1 == 1) {
          rDisplay.draw(col, row + m_wonOffset);
        }
      }
    }
  }
}


//------------------------------------------
//game over
void BreakOut::updateGameOver(const float& rDeltaTime) {
  m_gameOverTimer += rDeltaTime;
  //make the screen light up row by row from the top
  if (m_gameOverTimer >= GAME_OVER_UPDATE_INTERVAL && m_currentGameOverRow < HEIGHT) {
    m_gameOverTimer = 0.0f;

    m_brickField[m_currentGameOverRow++] = 255;
  }
}

//------------------------------------------
//won
void BreakOut::checkWon() {
  bool won = true;
  for (byte row = 0; row < HEIGHT; ++row) {
    if (m_brickField[row] != 0) {
      won = false;
    }
  }

  if (won) {
    m_state = GameState::WON;
  }
}

void BreakOut::updateWon(const float& rDeltaTime) {
   m_gameOverTimer += rDeltaTime;

  if (m_gameOverTimer >= GAME_OVER_UPDATE_INTERVAL && m_wonOffset > 0) {
    m_gameOverTimer = 0.0f;
    m_wonOffset--;
  }
}


//------------------------------------------
//observer
void BreakOut::notify(const Message& rMessage) {
  switch (rMessage.type) {
    case MessageType::INPUT_RIGHT:
      m_platform.movementDir = MovementDir::RIGHT;
      break;
    case MessageType::INPUT_LEFT:
      m_platform.movementDir = MovementDir::LEFT;
      break;
    case MessageType::INPUT_UP:
      break;
    case MessageType::INPUT_DOWN:
      if (m_state == GameState::PLAYING) {
        if (rMessage.secondaryType == SecondaryMessageType::JUST_PRESSED) {
          if (m_ballHeld) { //release ball
            m_ballHeld = false;
            m_ball.setVel(0, -m_ball.BALL_SPEED);
          }
        }
      } else if (m_state == GameState::GAME_OVER || m_state == GameState::WON) {
        reset();
      }
      break;
    case MessageType::BREAK_OUT_BALL_DIED:
      m_ballHeld = true;
      m_lifes--;

      if (m_lifes == 0 && m_state == GameState::PLAYING) {
        m_state = GameState::GAME_OVER;
      }
      break;
  }
}

