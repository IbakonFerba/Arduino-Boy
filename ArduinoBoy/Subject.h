#pragma once

#ifndef SUBJECT_H
#define SUBJECT_H

#include "stdafx.h"
#include "Observer.h"

class Subject
{
  public:
    virtual ~Subject() {}
    void addObserver(Observer* ptrObserver);
    void removeObserver(Observer* ptrObserver);
  protected:
    static const byte MAX_OBSERVERS = 8;
    short m_lastObserver = -1;
    Observer* m_observers[MAX_OBSERVERS];
    Message m_observerMessage;

    virtual void notifyObservers() const;
};

#endif
