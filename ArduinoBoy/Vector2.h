#pragma once

#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2 {
  public:
    Vector2() : x(0), y(0) {}
    Vector2(const float _x, const float _y) : x(_x), y (_y) {};

    float x;
    float y;

    float magnitude() const;
    void normalize();
    void rotate(const float& angle, const bool& deg);


    Vector2 operator+(const Vector2& other) const;
    void operator+=(const Vector2& other);

    Vector2 operator*(const Vector2& other) const;
    Vector2 operator*(const int other) const;
    Vector2 operator*(const float other) const;
    void operator*=(const Vector2& other);
    void operator*=(const int other);
    void operator*=(const float other);
};

#endif
