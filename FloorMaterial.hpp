#ifndef FLOOR_MATERIAL_HPP
#define FLOOR_MATERIAL_HPP

#include "Material.hpp"
#include "DiffuseBlinn.hpp"
#include "Color.hpp"
#include "Intersection.hpp"
#include "Light.hpp"
#include "Vector.hpp"

struct FloorMaterial : Material {
  DiffuseBlinn m1;
  DiffuseBlinn m2;
  float shine;

  FloorMaterial();

  Color bounce(const Intersection& in, Light** lights, int s);

  Material* getMaterialAt(const Vector& v);
};

#endif
