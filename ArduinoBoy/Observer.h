#pragma once

#ifndef OBSERVER_H
#define OBSERVER_H

#include "stdafx.h"

enum class MessageType
{
  STD,
  INPUT_LEFT,
  INPUT_RIGHT,
  INPUT_UP,
  INPUT_DOWN,
  BREAK_OUT_BALL_DIED
};



enum class SecondaryMessageType {
  STD,
  JUST_PRESSED,
};



struct Message
{
  MessageType type = MessageType::STD;
  SecondaryMessageType secondaryType = SecondaryMessageType::STD;
};



class Observer
{
  public:
    Observer() {}
    virtual ~Observer() {}
    virtual void notify(const Message& rMessage) = 0;
};

#endif
