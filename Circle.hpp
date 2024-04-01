#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "Object.hpp"

#include "Vector.hpp"
#include "Material.hpp"
#include "Intersection.hpp"
#include "Ray.hpp"


struct Circle : Object
{
  float r;

  Circle(Vector* p, Material* m, float r0);

  Intersection intersect(Ray* ray);
};

#endif
