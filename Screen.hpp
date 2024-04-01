#ifndef SCREEN_HPP
#define SCREEN_HPP

#include "Color.hpp"


#define WIDTH 600
#define HEIGHT 600

struct Screen
{
public:
  int x;
  int y;

  Color canvas[WIDTH * HEIGHT];

  Screen();

  void draw();
};

#endif
