#include <math.h>
#include "Color.hpp"

Color::Color(float r0, float g0, float b0) {
  r = r0; g = g0; b = b0;
}

Color Color::operator*(float a) {
  return Color(r * a, g * a, b * a);
}

Color Color::operator*(const Color& c) {
  return Color(r * c.r, g * c.g, b * c.b);
}

Color Color::operator/(const Color& c) {
  return Color(r / c.r, g / c.g, b / c.b);
}

Color Color::operator+(const Color& c) {
  return Color(r + c.r, g + c.g, b + c.b);
}

Color Color::operator-()
{
  return Color(-r, -g, -b);
}

Color Color::operator-(float a)
{
  return Color(r-a, g-a, b-a);
}

Color Color::operator-(const Color& c)
{
  return Color(r-c.r, g-c.g, b-c.b);
}

Color& Color::operator+=(const Color& c) {
  r += c.r;
  g += c.g;
  b += c.b;
  return *this;
}

Color Color::operator^(float p)
{
  return Color(pow(r, p), pow(g, p), pow(b, p));
}

Color Color::saturate(float min, float max){
  return Color(
    fmin(fmax(r, min), max),
    fmin(fmax(g, min), max),
    fmin(fmax(b, min), max)
  );
}
