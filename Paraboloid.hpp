#ifndef PARABOLOID_HPP
#define PARABOLOID_HPP

#include "Circle.hpp"
#include "Vector.hpp"
#include "Material.hpp"
#include "Intersection.hpp"

struct Paraboloid : Object {
public:
  float h;
  Circle cap;
  Vector top;

  Paraboloid(Vector* p0, Material* m0, float r0 = 2);

  Intersection intersect(Ray* r);

  void createChild(Paraboloid* parab);
};

#endif
