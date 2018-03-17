#include "stdafx.h"
#include "OperatingSystem.h"

//------------------------------------------
//constructor
OperatingSystem::OperatingSystem(const Input* ptrInputManager) : m_ptr_inputManager(ptrInputManager), m_buttonsPressed(0), m_menuButtonsTimeHeld(0), m_state(OSState::MENU), m_selectedProgram(0) {
  m_ptr_inputManager->addObserver(this);
}




//------------------------------------------
//update
void OperatingSystem::updateOS(const float& rDeltaTime, Display& rDisplay) {
  checkReturnToMenu(rDeltaTime);

  switch (m_state) {
    case OSState::MENU:
      drawMenu(rDisplay);
      break;
    case OSState::TRANSITION:
      updateTransition(rDeltaTime);
      drawTransition(rDisplay);
      break;
    case OSState::PROGRAM:
      updateProgram(rDeltaTime);
      renderProgram(rDisplay);
      break;
  }
}




//------------------------------------------
//menu
void OperatingSystem::checkReturnToMenu(const float& rDeltaTime) {
  //check if all buttons are pressed, increase the timer if true, set it to 0 if false
  if (m_buttonsPressed == 4) {
    m_menuButtonsTimeHeld += rDeltaTime;
  } else if (m_menuButtonsTimeHeld != 0) {
    m_menuButtonsTimeHeld = 0;
  }

  //stop running program and activate menu if buttons are held for set amount of time
  if (m_menuButtonsTimeHeld > TIME_TO_HOLD_BUTTONS_FOR_MENU && m_state != OSState::MENU) {
    if (m_state == OSState::PROGRAM) {
      stopActiveProgram();
    }

    m_state = OSState::MENU;
  }

  //reset buttons held counter
  m_buttonsPressed = 0;
}

void OperatingSystem::nextProgram() {
  //do nothing if we are not in the menu
  if (m_state != OSState::MENU) {
    return;
  }

  //cycle foreward through programs
  m_selectedProgram = m_selectedProgram < NUM_OF_PROGRAMS - 1 ? m_selectedProgram + 1 : 0;
}

void OperatingSystem::prevProgram() {
  //do nothing if we are not in the menu
  if (m_state != OSState::MENU) {
    return;
  }

  //cycle backwards through programs
  m_selectedProgram = m_selectedProgram > 0 ? m_selectedProgram - 1 : NUM_OF_PROGRAMS - 1;
}

void OperatingSystem::drawMenu(Display& rDisplay) const {
  rDisplay.setScreen(m_programs[m_selectedProgram]->icon);
}




//------------------------------------------
//transition
void OperatingSystem::startTransition() {
  if (m_state != OSState::MENU) {
    return;
  }

  m_state = OSState::TRANSITION;
  m_transitionText.setText(m_programs[m_selectedProgram]->title);
}

void OperatingSystem::updateTransition(const float& rDeltaTime) {
  if (m_transitionText.scrollText(rDeltaTime)) {
    startActiveProgram();
  }
}

void OperatingSystem::drawTransition(Display& rDisplay) const {
  m_transitionText.drawText(rDisplay);
}

//------------------------------------------
//programs
void OperatingSystem::startActiveProgram() {
  m_state = OSState::PROGRAM;
  m_programs[m_selectedProgram]->startProgram(m_ptr_inputManager);
}

void OperatingSystem::stopActiveProgram() {
  m_programs[m_selectedProgram]->stopProgram(m_ptr_inputManager);
}

void OperatingSystem::updateProgram(const float& rDeltaTime) {
  m_programs[m_selectedProgram]->updateProgram(rDeltaTime);
}

void OperatingSystem::renderProgram(Display& rDisplay) const {
  m_programs[m_selectedProgram]->renderProgram(rDisplay);
}



//------------------------------------------
//observer
void OperatingSystem::notify(const Message& rMessage) {
  switch (rMessage.type) {
    case MessageType::INPUT_RIGHT:
      if (rMessage.secondaryType == SecondaryMessageType::JUST_PRESSED) {
        nextProgram();
      }
      ++m_buttonsPressed;
      break;
    case MessageType::INPUT_LEFT:
      if (rMessage.secondaryType == SecondaryMessageType::JUST_PRESSED) {
        prevProgram();
      }
      ++m_buttonsPressed;
      break;
    case MessageType::INPUT_UP:
      ++m_buttonsPressed;
      break;
    case MessageType::INPUT_DOWN:
      if (rMessage.secondaryType == SecondaryMessageType::JUST_PRESSED) {
        startTransition();
      }
      ++m_buttonsPressed;
      break;
  }
}

