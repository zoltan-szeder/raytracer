#ifndef DIFFUSE_HPP
#define DIFFUSE_HPP

#include "Material.hpp"

struct Diffuse : Material {
  Color c;

  Diffuse(const Color& c0);

  Color bounce(const Intersection& in, Light** lights, const int s);
};

#endif
