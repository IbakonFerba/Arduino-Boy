#pragma once

#ifndef CHARS_H
#define CHARS_H

#include "stdafx.h"

//struct for a text char containing the char and a encoded bitmap for displaying the char
struct ArduinoBoyChar {
  char c;
  byte bitmap[HEIGHT];

  ArduinoBoyChar(const char& rC, const byte charBitmap[HEIGHT]) {
    c = rC;
    for(byte row = 0; row < HEIGHT; ++row) {
        bitmap[row] = charBitmap[row];
    }
  }

  byte getPixel(const byte& row, const byte& col) const {
    return (bitmap[row] >> col) & 1;
  }
};



//all chars
#define NUM_OF_CHARS 28
const ArduinoBoyChar ArduinoBoyChars[NUM_OF_CHARS] = {
  ArduinoBoyChar('a', (byte[HEIGHT]){0,24,36,36,60,36,36,0}),
  ArduinoBoyChar('b', (byte[HEIGHT]){0,28,36,28,36,36,28,0}),
  ArduinoBoyChar('c', (byte[HEIGHT]){0,24,36,4,4,36,24,0}),
  ArduinoBoyChar('d', (byte[HEIGHT]){0,28,36,36,36,36,28,0}),
  ArduinoBoyChar('e', (byte[HEIGHT]){0,60,4,28,4,4,60,0}),
  ArduinoBoyChar('f', (byte[HEIGHT]){0,60,4,28,4,4,4,0}),
  ArduinoBoyChar('g', (byte[HEIGHT]){0,56,4,4,52,36,24,0}),
  ArduinoBoyChar('h', (byte[HEIGHT]){0,36,36,60,36,36,36,0}),
  ArduinoBoyChar('i', (byte[HEIGHT]){0,16,0,24,16,16,16,0}),
  ArduinoBoyChar('j', (byte[HEIGHT]){0,32,32,32,32,36,24,0}),
  ArduinoBoyChar('k', (byte[HEIGHT]){0,36,20,12,20,20,36,0}),
  ArduinoBoyChar('l', (byte[HEIGHT]){0,4,4,4,4,4,60,0}),
  ArduinoBoyChar('m', (byte[HEIGHT]){0,68,108,84,68,68,68,0}),
  ArduinoBoyChar('n', (byte[HEIGHT]){0,36,36,44,52,36,36,0}),
  ArduinoBoyChar('o', (byte[HEIGHT]){0,24,36,36,36,36,24,0}),
  ArduinoBoyChar('p', (byte[HEIGHT]){0,28,36,36,28,4,4,0}),
  ArduinoBoyChar('q', (byte[HEIGHT]){0,24,36,36,36,24,32,0}),
  ArduinoBoyChar('r', (byte[HEIGHT]){0,28,36,36,28,20,36,0}),
  ArduinoBoyChar('s', (byte[HEIGHT]){0,24,36,12,48,36,24,0}),
  ArduinoBoyChar('t', (byte[HEIGHT]){0,124,16,16,16,16,16,0}),
  ArduinoBoyChar('u', (byte[HEIGHT]){0,36,36,36,36,36,24,0}),
  ArduinoBoyChar('v', (byte[HEIGHT]){0,36,36,36,36,24,24,0}),
  ArduinoBoyChar('w', (byte[HEIGHT]){0,68,68,68,84,108,68,0}),
  ArduinoBoyChar('x', (byte[HEIGHT]){0,36,36,24,24,36,36,0}),
  ArduinoBoyChar('y', (byte[HEIGHT]){0,40,40,40,16,16,16,0}),
  ArduinoBoyChar('z', (byte[HEIGHT]){0,60,32,16,8,4,60,0}),
  ArduinoBoyChar(' ', (byte[HEIGHT]){0,0,0,0,0,0,0,0}),
  ArduinoBoyChar('-', (byte[HEIGHT]){0,0,0,0,60,0,0,0})
};

#endif
