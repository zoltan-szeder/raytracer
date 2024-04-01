#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Material.hpp"
#include "Vector.hpp"
#include "Intersection.hpp"
#include "Ray.hpp"

struct Object {
public:
  Material* m;
  Vector* p;

  Object(Vector* p0, Material* m0);

  Vector* getPosition();

  Material* getMaterial();

  virtual Intersection intersect(Ray* r) = 0;
};

#endif
