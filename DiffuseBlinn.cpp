#include "DiffuseBlinn.hpp"

DiffuseBlinn::DiffuseBlinn(const Color& cd0, const Color& cs0, const float shine0) {
  cd = cd0;
  cs = cs0;
  shine = shine0;
}

Color DiffuseBlinn::bounce(const Intersection& in, Light** lights, const int s) {
  Color color;
  for(int i = 0; i < s; i++)
  {
    Lightning l = lights[i]->light(in, shine);
    color += cd*l.a + cd*l.d + cs*l.s;
  }
  return color.saturate(0, 1);
}

