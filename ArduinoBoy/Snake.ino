#include "stdafx.h"
#include "Snake.h"

//------------------------------------------
//constructor
Snake::Snake() {
  setMenuInfo();
}


//------------------------------------------
//setup
void Snake::startProgram(Input* ptrInputManager) {
  reset();
  randomSeed(micros()); //random seed for bait spawning

  ptrInputManager->addObserver(this);
}

void Snake::stopProgram(Input* ptrInputManager) {
  ptrInputManager->removeObserver(this);

  if (snake) {
    delete snake;
    snake = NULL;
  }
}

void Snake::clearField() {
  for (byte row = 0; row < HEIGHT; ++row) {
    m_playField[row] = 0;
    m_baitField[row] = 0;
  }
}

void Snake::resetSnake() {
  if (snake) {
    delete snake;
    snake = NULL;
  }
  snake = new SnakeSegment(4, 4);

  m_movementDir = Direction::UP;
  m_movementTimer = 0.0f;

  SnakeSegment* current = snake;
  //place snake on field (this can handle snakes that are longer than one initially)
  while (current) {
    m_playField[current->row] = m_playField[current->row] |(1 << current->col);
    current = current->next;
  }
}

void Snake::reset() {
  clearField();
  resetSnake();

  m_state = GameState::PLAYING;

  m_currentGameOverRow = 0;
  m_gameOverTimer = 0;

  m_baitTimer = 0;

  spawnBait();
}



//------------------------------------------
//game
void Snake::updateProgram(const float& rDeltaTime) {
  switch (m_state) {
    case GameState::PLAYING:
      moveSnake(rDeltaTime);

      m_baitTimer += rDeltaTime;
      if (m_baitTimer >= BAIT_INTERVAL) {
        spawnBait();
      }
      break;
    case GameState::GAME_OVER:
      updateGameOver(rDeltaTime);
      break;
  }
}

void Snake::renderProgram(Display& rDisplay) const {
  rDisplay.setScreen(m_playField);
}

byte Snake::getCell(const byte& rRow, const byte& rCol) const {
  return (m_playField[rRow] >> rCol) & 1;
}


//------------------------------------------
//game over
void Snake::updateGameOver(const float& rDeltaTime) {
  m_gameOverTimer += rDeltaTime;
  //make the screen light up row by row from the top
  if (m_gameOverTimer >= GAME_OVER_UPDATE_INTERVAL && m_currentGameOverRow < HEIGHT) {
    m_gameOverTimer = 0.0f;

    m_playField[m_currentGameOverRow++] = 255;
  }
}


//------------------------------------------
//bait
void Snake::spawnBait() {
  m_baitTimer = 0;

  //get a random position
  byte randomRow = floor(random(0, HEIGHT));
  byte randomCol = floor(random(0, WIDTH));

  //if at the chose position there is allready something(snake or bait), get a new random position until we found an empty place
  while (getCell(randomRow, randomCol) == 1) {
    randomRow = floor(random(0, HEIGHT));
    randomCol = floor(random(0, WIDTH));
  }

  //add the bait to the play field and the bait field
  m_playField[randomRow] = (1 << randomCol) |  m_playField[randomRow];
  m_baitField[randomRow] = (1 << randomCol) |  m_baitField[randomRow];
}

byte Snake::getBaitCell(const byte& rRow, const byte& rCol) const {
  return (m_baitField[rRow] >> rCol) & 1;
}

//------------------------------------------
//snake
void Snake::moveSnake(const float& rDeltaTime) {
  m_movementTimer += rDeltaTime;
  if (m_movementTimer >= MOVEMENT_INTERVAL) {
    m_movementTimer = 0.0f;

    SnakeSegment* tail = snake->getLastSegment();
    byte prevTailRow = tail->row;
    byte prevTailCol = tail->col;

    byte nextRow = 0;
    byte nextCol = 0;
    switch (m_movementDir) {
      case Direction::UP:
        nextRow = snake->row > 0 ? snake->row - 1 : HEIGHT - 1;
        nextCol = snake->col;
        break;
      case Direction::DOWN:
        nextRow = snake->row < HEIGHT - 1 ? snake->row + 1 : 0;
        nextCol = snake->col;
        break;
      case Direction::LEFT:
        nextRow = snake->row;
        nextCol = snake->col > 0 ? snake->col - 1 : WIDTH - 1;
        break;
      case Direction::RIGHT:
        nextRow = snake->row;
        nextCol = snake->col < WIDTH - 1 ? snake->col + 1 : 0;
        break;
    }

    bool foundBait = false;
    if (getCell(nextRow, nextCol) == 1) {
      if (getBaitCell(nextRow, nextCol) == 1) {
        m_baitField[nextRow] = (1 << nextCol) ^  m_baitField[nextRow];
        foundBait = true;
      } else {
        m_state = GameState::GAME_OVER;
        return;
      }
    }

    if (foundBait) {
      snake->addSegment(nextRow, nextCol);
    } else {
      snake->updateSegment(nextRow, nextCol);
    }
    m_playField[snake->row] = (1 << snake->col) | m_playField[snake->row];

    if(!foundBait) {
      m_playField[prevTailRow] = (1 << prevTailCol) ^ m_playField[prevTailRow];
    }
  }
}


//------------------------------------------
//observer
void Snake::notify(const Message& rMessage) {
  switch (rMessage.type) {
    case MessageType::INPUT_RIGHT:
      if (rMessage.secondaryType == SecondaryMessageType::JUST_PRESSED && m_movementDir != Direction::LEFT) {
        m_movementDir = Direction::RIGHT;
      }
      break;
    case MessageType::INPUT_LEFT:
      if (rMessage.secondaryType == SecondaryMessageType::JUST_PRESSED && m_movementDir != Direction::RIGHT) {
        m_movementDir = Direction::LEFT;
      }
      break;
    case MessageType::INPUT_UP:
      if (rMessage.secondaryType == SecondaryMessageType::JUST_PRESSED && m_movementDir != Direction::DOWN) {
        m_movementDir = Direction::UP;
      }
      break;
    case MessageType::INPUT_DOWN:
      if (rMessage.secondaryType == SecondaryMessageType::JUST_PRESSED) {
        if (m_state == GameState::GAME_OVER) {
          reset();
        } else if (m_movementDir != Direction::UP) {
          m_movementDir = Direction::DOWN;
        }
      }
      break;
  }
}

