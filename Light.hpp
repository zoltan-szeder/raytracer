#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Lightning.hpp"
#include "Intersection.hpp"

struct Light {
public:
  virtual Lightning light(const Intersection& in, const float shine = 0) = 0;
};

#endif
