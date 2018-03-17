#include "stdafx.h"
#include "Text.h"

//------------------------------------------
//set text
void Text::setText(const String text) {
  m_text = text;
  m_currentChar = 0;
  m_nextChar = 1;
  m_currentCharOffset = 8;

  //find bitmaps for first two characters
  findCharBitmap(m_currentChar, m_currentCharBitmapIndex);
  findCharBitmap(m_nextChar, m_nextCharBitmapIndex);
}

void Text::setText(const String text, const float& rScrollSpeed) {
  setText(text);
  m_scrollSpeed = rScrollSpeed;
}


void Text::findCharBitmap(const byte& rC, short& rBitmapIndex) {
  if (rC < m_text.length()) {
    char c = tolower(m_text.charAt(rC));

    for (byte i = 0; i < NUM_OF_CHARS; ++i) {
      if (ArduinoBoyChars[i].c == c) {
        rBitmapIndex = i;
        return;
      }
    }
  }

  rBitmapIndex = -1;
}

//------------------------------------------
//scroll text
bool Text::scrollText(const float& rDeltaTime) {
  m_currentCharOffset -= rDeltaTime * m_scrollSpeed;

  if (m_currentCharOffset < -7) {
    if (m_nextChar < m_text.length()) {
      m_currentChar = m_nextChar++;
      m_currentCharOffset = 0;

      findCharBitmap(m_currentChar, m_currentCharBitmapIndex);
      findCharBitmap(m_nextChar, m_nextCharBitmapIndex);
      return false;
    }
    return true;
  }

  return false;
}


//------------------------------------------
//draw text
void Text::drawText(Display& rDisp) const {
  byte offset = floor(m_currentCharOffset);

  if (m_currentChar != -1) {
    for (byte row = 0; row < HEIGHT; ++row) {
      for (byte col = 0; col < WIDTH; ++col) {
        if (ArduinoBoyChars[m_currentCharBitmapIndex].getPixel(row, col) > 0) {
          rDisp.draw(col + offset, row);
        }
      }
    }
  }

  offset += WIDTH;
  if (m_nextCharBitmapIndex  != -1) {
    for (byte row = 0; row < HEIGHT; ++row) {
      for (byte col = 0; col < WIDTH; ++col) {
        if (ArduinoBoyChars[m_nextCharBitmapIndex].getPixel(row, col) > 0) {
          rDisp.draw(col + offset, row);
        }
      }
    }
  }
}

