#pragma once

#ifndef STDAFX_H
#define STDAFX_H

#include <stddef.h>

#define HEIGHT 8
#define WIDTH 8

enum class GameState {
  PLAYING,
  GAME_OVER,
  WON
};


byte xOr(const byte& rIsValue, const byte& rOther) {
  return rIsValue ^rOther;
}

#endif
