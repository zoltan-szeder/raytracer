#ifndef POINT_LIGHT_HPP
#define POINT_LIGHT_HPP

#include "Light.hpp"
#include "Vector.hpp"
#include "Color.hpp"
#include "Model.hpp"

struct PointLight : Light {
public:
  const Model& model;
  Vector p;
  Color dc;
  float dp;
  Color sc;
  float sp;

  PointLight(
    const Model& model0,
    const Vector& p0, const Color& dc0, const Color& sc0,
    const float dp0 = 1, const float sp0 = 1
  );

  Lightning light(const Intersection& in, const float shine = 0);
};

#endif
