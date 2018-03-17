#include "stdafx.h"
#include "SnakeSegment.h"

SnakeSegment::SnakeSegment(const byte& r, const byte& c) {
  row = r;
  col = c;
}

SnakeSegment::~SnakeSegment() {
  if(next) {
      delete next;
      next = NULL;
  }
}


void SnakeSegment::addSegment(const byte& r, const byte& c) {
  if(next) {
      next->addSegment(row, col);
  } else {
    next = new SnakeSegment(row, col);
  }

  row = r;
  col = c;
}


void SnakeSegment::updateSegment(const byte& r, const byte& c) {
  if(next) {
    next->updateSegment(row, col);
  }

  row = r;
  col = c;
}


SnakeSegment* SnakeSegment::getLastSegment() const {
  if(next) {
    return next->getLastSegment();
  } else {
    return this;
  }
}

