#include "stdafx.h"
#include "Subject.h"

void Subject::addObserver(Observer* ptrObserver)
{
  if (m_lastObserver < MAX_OBSERVERS) {
    m_observers[++m_lastObserver] = ptrObserver;
  }
}

void Subject::removeObserver(Observer* ptrObserver)
{
  for (byte i = 0; i < m_lastObserver; ++i) {
    if (m_observers[i] == ptrObserver) {
      m_observers[i] = m_observers[m_lastObserver];
      --m_lastObserver;
      return;
    }
  }

  --m_lastObserver;
}


void Subject::notifyObservers() const
{
  for (short i = m_lastObserver; i >= 0; --i)
  {
    m_observers[i]->notify(m_observerMessage);
  }
}
