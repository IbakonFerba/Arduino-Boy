# include "stdafx.h"
#include "Paint.h"

//------------------------------------------
//constructor
Paint::Paint() {
  setMenuInfo();
}


//------------------------------------------
//setup
void Paint::startProgram(Input* ptrInputManager) {
  ptrInputManager->addObserver(this);
  reset();
}
void Paint::stopProgram(Input* ptrInputManager) {
  ptrInputManager->removeObserver(this);
}


void Paint::reset() {
  //clear canvas
  for (byte row = 0; row < HEIGHT; ++row) {
    m_canvas[row] = 0;
  }

  //set brush position
  m_brushRow = 0;
  m_brushCol = 0;

  //reset brush timers
  m_brushBlinkTimer = 0;
  m_brushMovementTimer = 0;

  //set brush movement and mode
  m_brushMovement = BrushMovement::NONE;
  m_brushMode = BrushMode::MOVE;

  //reset button combos
  m_drawComboHeld = 0;
  m_eraseComboHeld = 0;

  m_drawComboHeldPrev = 0;
  m_eraseComboHeldPrev = 0;
}






//------------------------------------------
//update
void Paint::updateProgram(const float& rDeltaTime) {
  //update brush blinking
  if (m_brushBlinkTimer >= BRUSH_BLINK_INTERVAL * 2) {
    m_brushBlinkTimer = 0;
  }

  m_brushBlinkTimer += rDeltaTime;



  //Brush modes
  if (m_drawComboHeld == 2 && m_drawComboHeldPrev < 2) {
    if (m_brushMode == BrushMode::DRAW) {
      m_brushMode = BrushMode::MOVE;
    } else {
      m_brushMode = BrushMode::DRAW;
    }
  } else if (m_eraseComboHeld == 2 && m_eraseComboHeldPrev < 2) {
    if (m_brushMode == BrushMode::ERASE) {
      m_brushMode = BrushMode::MOVE;
    } else {
      m_brushMode = BrushMode::ERASE;
    }
  }

  //dont move if one of the button combos is held
  if (m_drawComboHeld == 2 || m_eraseComboHeld == 2) {
    m_brushMovement = BrushMovement::NONE;
  }

  //save and reset button combos
  m_drawComboHeldPrev = m_drawComboHeld;
  m_eraseComboHeldPrev = m_eraseComboHeld;
  m_drawComboHeld = 0;
  m_eraseComboHeld = 0;

  //move the brush
  moveBrush(rDeltaTime);
  m_brushMovement = BrushMovement::NONE;


  //draw or erase
  if (m_brushMode == BrushMode::DRAW) {
    byte wantVal = 1 << m_brushCol;
    m_canvas[m_brushRow] =  m_canvas[m_brushRow] | wantVal;
  } else if (m_brushMode == BrushMode::ERASE) {
    byte wantVal = 1 << m_brushCol;
    wantVal = 255 ^ wantVal;
    m_canvas[m_brushRow] =  m_canvas[m_brushRow] & wantVal;
  }
}

void Paint::moveBrush(const float& rDeltaTime) {
  if (m_brushMovement == BrushMovement::NONE) {
    m_brushMovementTimer = 0;
    return;
  }

  if (m_brushMode == BrushMode::MOVE) {
    m_brushBlinkTimer = BRUSH_BLINK_INTERVAL;
  } else {
    m_brushBlinkTimer = 0;
  }

  m_brushMovementTimer += rDeltaTime;

  if (m_brushMovementTimer >= BRUSH_MOVEMENT_INTERVAL) {
    switch (m_brushMovement) {
      case BrushMovement::UP:
        if (m_brushRow > 0) {
          --m_brushRow;
        }
        break;
      case BrushMovement::DOWN:
        if (m_brushRow < HEIGHT - 1) {
          ++m_brushRow;
        }
        break;
      case BrushMovement::LEFT:
        if (m_brushCol > 0) {
          --m_brushCol;
        }
        break;
      case BrushMovement::RIGHT:
        if (m_brushCol < WIDTH - 1) {
          ++m_brushCol;
        }
        break;
    }
  }

  if (m_brushMovementTimer >= BRUSH_MOVEMENT_INTERVAL) {
    m_brushMovementTimer = 0;
  }
}



//------------------------------------------
//render
void Paint::renderProgram(Display& rDisplay) const {
  rDisplay.setScreen(m_canvas);

  if (m_brushBlinkTimer >= BRUSH_BLINK_INTERVAL && m_brushBlinkTimer <= BRUSH_BLINK_INTERVAL * 2) {
    rDisplay.drawMapped(m_brushCol, m_brushRow, &xOr);
  }
}


//------------------------------------------
//observer
void Paint::notify(const Message& rMessage) {
  switch (rMessage.type) {
    case MessageType::INPUT_RIGHT:
      m_eraseComboHeld += 1;
      m_brushMovement = BrushMovement::RIGHT;
      break;
    case MessageType::INPUT_LEFT:
      m_eraseComboHeld += 1;
      m_brushMovement = BrushMovement::LEFT;
      break;
    case MessageType::INPUT_UP:
      m_drawComboHeld += 1;
      m_brushMovement = BrushMovement::UP;
      break;
    case MessageType::INPUT_DOWN:
      m_drawComboHeld += 1;
      m_brushMovement = BrushMovement::DOWN;
      break;
  }
}

