#ifndef DIFFUSE_BLINN_HPP
#define DIFFUSE_BLINN_HPP

#include "Material.hpp"

struct DiffuseBlinn : Material {
  Color cd;
  Color cs;
  float shine;

  DiffuseBlinn(const Color& cd0, const Color& cs0, const float shine0 = 64);

  Color bounce(const Intersection& in, Light** lights, const int s);
};

#endif
