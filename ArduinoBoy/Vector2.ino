#include "Vector2.h"


float Vector2::magnitude() const {
  return sqrt(x * x + y * y);
}

void Vector2::normalize()
{
  const float mag = magnitude();

  if (mag != 0) {
    x /= mag;
    y /= mag;
  }
}

void Vector2::rotate(const float& angle, const bool& deg) {
  float a = angle;
  if(deg) {
    a = angle * PI/180;
  }
  float xnew = cos(a) * x - sin(a) * y;
  float ynew = sin(a) * x + cos(a) * y;

  x = xnew;
  y = ynew;
}


Vector2 Vector2::operator+(const Vector2& other) const {
  return Vector2(x + other.x, y + other.y);
}

void Vector2::operator+=(const Vector2& other) {
  x += other.x;
  y += other.y;
}

Vector2 Vector2::operator*(const Vector2& other) const {
  return Vector2(x * other.x, y * other.y);
}

Vector2 Vector2::operator*(const int other) const {
  return Vector2(x * other, y * other);
}

Vector2 Vector2::operator*(const float other) const {
  return Vector2(x * other, y * other);
}

void Vector2::operator*=(const Vector2& other) {
  x *= other.x;
  y *= other.y;
}

void Vector2::operator*=(const int other) {
  x *= other;
  y *= other;
}

void Vector2::operator*=(const float other) {
  x *= other;
  y *= other;
}

