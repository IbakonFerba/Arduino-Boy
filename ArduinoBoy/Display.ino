#include "Display.h"

//------------------------------------------
//constructor
Display::Display() {
  //setup pins
  for (byte row = 0; row < HEIGHT; ++row) {
    pinMode(m_rows[row], OUTPUT);
    digitalWrite(m_rows[row], HIGH);
  }

  for (byte col = 0; col < WIDTH; ++col) {
    pinMode(m_cols[col], OUTPUT);
    digitalWrite(m_cols[col], LOW);
  }

  //make sure display is empty
  clearDisplay();
}




//------------------------------------------
//drawing
void Display::draw(const byte& col, const byte& row) {
  if (row < HEIGHT && row > -1 && col < WIDTH && col > -1) { //check if position is inside screen, then set pixel
    byte wantVal = 1 << col; //get a 8 bit binary number with a one ath the desired column by bitshifting 1 by the number of ther column
    m_image[row] = m_image[row] | wantVal; //AND the exiting value and the wanted pixel value
  }
}

void Display::drawMapped(const byte& col, const byte& row, byte (*ptrMapFunction)(const byte&, const byte&)) {
  if (row < HEIGHT && row > -1 && col < WIDTH && col > -1) { //check if position is inside screen, then set pixel
    byte wantVal = 1 << col; //get a 8 bit binary number with a one ath the desired column by bitshifting 1 by the number of ther column
    m_image[row] = (*ptrMapFunction)(m_image[row], wantVal); //determining teh value by using the provided function
  }
}

void Display::setScreen(const byte image[HEIGHT]) {
  for (byte row = 0; row < HEIGHT; ++row) {
    m_image[row] = image[row];
  }
}




//------------------------------------------
//rendering
void Display::clearDisplay() {
  for (byte row = 0; row < HEIGHT; ++row) {
    m_image[row] = 0;
  }
}

void Display::render() const {
  for (byte row = 0; row < HEIGHT; ++row) {
    for (byte col = 0; col < WIDTH; ++col) {
      digitalWrite(m_cols[col], (m_image[row] >> col) & 1);
    }

    digitalWrite(m_rows[row], LOW);
    delay(1);
    digitalWrite(m_rows[row], HIGH);
  }
}

