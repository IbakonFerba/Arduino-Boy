#pragma once

#ifndef SNAKE_SEGMENT_H
#define SNAKE_SEGMENT_H

#include "stdafx.h"

class SnakeSegment {
  public:
    SnakeSegment() {}
    SnakeSegment(const byte& r, const byte& c);
    ~SnakeSegment();
    byte row;
    byte col;

    SnakeSegment* next = NULL;

    void addSegment(const byte& r, const byte& c);
    void updateSegment(const byte& r, const byte& c);

    SnakeSegment* getLastSegment() const;
};

#endif
