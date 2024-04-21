#ifndef FRESNEL_HPP
#define FRESNEL_HPP

#include "Material.hpp"
#include "Camera.hpp"
#include "Color.hpp"
#include "Intersection.hpp"


#define TTL 15

struct Fresnel : Material {
  const Camera& camera;
  static int ttl;

  Color cd;
  Color cs;

  Color n;
  Color k;

  bool refl;
  bool refr;

  float shine;

  Color F0;
  

  Fresnel(const Camera& camera0, const Color& n0, const Color& k0, const Color& cd0, const Color& cs0, bool refl0 = true, bool refr0 = true, float shine0 = 64);

  Color bounce(const Intersection& in, Light** lights, const int s);

  Color fresnelF0();

  Color fresnel(const Intersection& in);

  Ray reflect(const Intersection& in);

  Intersection refract(const Intersection& in);
};

#endif
