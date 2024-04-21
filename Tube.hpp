#ifndef TUBE_HPP
#define TUBE_HPP

#include "Circle.hpp"
#include "Vector.hpp"
#include "Material.hpp"
#include "Intersection.hpp"

struct Tube : Object {
public:
  float rad;
  float h;

  Circle cap;
  Vector top;
  Vector bottom;

  Tube(Vector* p0, Material* m0, float rad0 = 0.5, float h0 = 1);

  Intersection intersect(Ray* r);

  void createChild(Tube* tube);
};

#endif
