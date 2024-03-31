#ifndef COLOR_HPP
#define COLOR_HPP

struct Color {
public:
  float r, g, b;

  Color(float r0 = 0, float g0 = 0, float b0 = 0);

  Color operator*(float a);

  Color operator*(const Color& c);

  Color operator/(const Color& c);

  Color operator+(const Color& c) ;

  Color operator-();

  Color operator-(float a);

  Color operator-(const Color& c);

  Color& operator+=(const Color& c);

  Color operator^(float p);

  Color saturate(float min, float max);
};

#endif
