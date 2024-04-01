#include "GL/gl.h"
#include "GL/glut.h"

#include "Screen.hpp"
#define WIDTH 600
#define HEIGHT 600

Screen::Screen() {
  x = WIDTH;
  y = HEIGHT;
}

void Screen::draw() {
  glClear(GL_COLOR_BUFFER_BIT);
  glDrawPixels(x, y, GL_RGB, GL_FLOAT, canvas);
  glutSwapBuffers();
}
