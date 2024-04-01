#include "Diffuse.hpp"

Diffuse::Diffuse(const Color& c0) {
  c = c0;
}

Color Diffuse::bounce(const Intersection& in, Light** lights, const int s) {
  Color color;

  for(int i = 0; i < s; i++)
  {
    Lightning l = lights[i]->light(in);
    color += c*l.a + c*l.d;
  }

  return color.saturate(0, 1);
}

