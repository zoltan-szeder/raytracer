#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Object.hpp"
#include "Vector.hpp"
#include "Material.hpp"
#include "Intersection.hpp"


struct Sphere : Object {
public:
  float rad;

  Sphere(Vector* p0, Material* m0, float rad0 = 1);
  Intersection intersect(Ray* r);
  void createChild(Sphere* sphere);
};

#endif
