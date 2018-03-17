#pragma once

#ifndef DISPLAY_H
#define DISPLAY_H

#include "stdafx.h"

class Display {
  public:
    Display();

    //==============================
    //drawing
    void draw(const byte& col, const byte& row);
    void drawMapped(const byte& col, const byte& row, byte (*ptrMapFunction)(const byte&, const byte&));
    void setScreen(const byte image[HEIGHT]);
    //==============================


    //==============================
    //redering
    void clearDisplay();
    void render() const;
    //==============================
  private:
    //==============================
    //define pins
    const byte m_rows[HEIGHT] = {A0, A1, A2, A3, A4, A5, 4, 5};
    const byte m_cols[WIDTH] = {6, 7, 8, 9, 10, 11, 12, 13};
    //==============================


    //==============================
    //place to store image
    byte m_image[HEIGHT];
    //==============================
};

#endif
