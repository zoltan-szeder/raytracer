#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Color.hpp"
#include "Intersection.hpp"
#include "Light.hpp"

struct Material {
  virtual Color bounce( const Intersection& in, Light** lights, int s ) = 0;
};

#endif
