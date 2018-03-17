#pragma once

#ifndef TEXT_H
#define TEXT_H

#include "stdafx.h"
#include "Display.h"
#include "Chars.h"

class Text {
  public:
    Text() {}

    void setText(const String text);
    void setText(const String text, const float& rScrollSpeed);

    bool scrollText(const float& rDeltaTime);
    void drawText(Display& rDisp) const;
  private:
    String m_text;
    float m_scrollSpeed = 8.0f;

    byte m_currentChar = 0;
    byte m_nextChar = 1;

    short m_currentCharBitmapIndex = -1;
    short m_nextCharBitmapIndex = -1;

    float m_currentCharOffset = 0;

    void findCharBitmap(const byte& rC, short& rBitmapIndex);
};

#endif
