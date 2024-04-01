#ifndef AMBIENT_LIGHT_HPP
#define AMBIENT_LIGHT_HPP

#include "Light.hpp"

struct AmbientLight : Light {
public:
  Color ac;
  float ap;

  AmbientLight(const Color& ac0, const float ap0 = 1);

  Lightning light(const Intersection&, const float);
};

#endif
