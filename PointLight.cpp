#include "PointLight.hpp"

PointLight::PointLight(
  const Vector& p0, const Color& dc0, const Color& sc0,
  const float dp0, const float sp0)
{
  p = p0;
  dc = dc0;
  dp = dp0;
  sc = sc0;
  sp = sp0;
}

Lightning PointLight::light(const Intersection& in, const float shine)
{
  Lightning l = Lightning(Color(), Color(), Color());

  Ray r(in.p, p - in.p);
  Object* o[1];
  o[0] = NULL;

  Intersection shadow = model.intersect(&r, o);
  if(shadow.v)
  {
    return l;
  }

  Vector V = -in.d.normalize();
  Vector N = in.n;
  Vector L = p - in.p;
  float Ld = L.abs();
  L = L.normalize();

  float di = L*N;

  l.d = dc*(dp*di/(Ld*Ld));

  Vector H = (L + V).normalize();
  float si = pow(H*N, shine);

  l.s = sc*(sp*si/(Ld*Ld));
  return l;
}

