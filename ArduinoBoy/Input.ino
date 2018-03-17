#include "stdafx.h"
#include "Input.h"

//------------------------------------------
//constructor
Input::Input() {
  //setup pins
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);
  pinMode(UP, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);

  //initialize prev values
  m_prevLeftVal = 0;
  m_prevRightVal = 0;
  m_prevUpVal = 0;
  m_prevDownVal = 0;
}

//------------------------------------------
//input
Input::getInput() {
  //read button values
  byte leftVal = digitalRead(LEFT);
  byte rightVal = digitalRead(RIGHT);
  byte upVal = digitalRead(UP);
  byte downVal = digitalRead(DOWN);




  //send button events if needed
  if (leftVal < 1) {
    m_observerMessage.type = MessageType::INPUT_LEFT;

    if (m_prevLeftVal != leftVal) {
      m_observerMessage.secondaryType = SecondaryMessageType::JUST_PRESSED;
    } else {
      m_observerMessage.secondaryType = SecondaryMessageType::STD;
    }

    notifyObservers();
  }

  if (rightVal < 1) {
    m_observerMessage.type = MessageType::INPUT_RIGHT;

    if (m_prevRightVal != rightVal) {
      m_observerMessage.secondaryType = SecondaryMessageType::JUST_PRESSED;
    } else {
      m_observerMessage.secondaryType = SecondaryMessageType::STD;
    }

    notifyObservers();
  }

  if (upVal < 1) {
    m_observerMessage.type = MessageType::INPUT_UP;

    if (m_prevUpVal != upVal) {
      m_observerMessage.secondaryType = SecondaryMessageType::JUST_PRESSED;
    } else {
      m_observerMessage.secondaryType = SecondaryMessageType::STD;
    }

    notifyObservers();
  }

  if (downVal < 1) {
    m_observerMessage.type = MessageType::INPUT_DOWN;

    if (m_prevDownVal != downVal) {
      m_observerMessage.secondaryType = SecondaryMessageType::JUST_PRESSED;
    } else {
      m_observerMessage.secondaryType = SecondaryMessageType::STD;
    }

    notifyObservers();
  }



  //save values as prev values
  m_prevLeftVal = leftVal;
  m_prevRightVal = rightVal;
  m_prevUpVal = upVal;
  m_prevDownVal = downVal;
}

