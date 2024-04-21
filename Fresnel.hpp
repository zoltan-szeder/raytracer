#ifndef FRESNEL_HPP
#define FRESNEL_HPP

#define TTL 5

struct Fresnel : Material {
  static int ttl;

  Color cd;
  Color cs;

  Color n;
  Color k;

  bool refl;
  bool refr;

  float shine;

  Color F0;
  

  Fresnel(const Color& n0, const Color& k0, const Color& cd0, const Color& cs0, bool refl0 = true, bool refr0 = true, float shine0 = 64);

  Color bounce(const Intersection& in, Light** lights, const int s);

  Color fresnelF0();

  Color fresnel(const Intersection& in);

  Ray reflect(const Intersection& in);

  Intersection refract(const Intersection& in);
};

int Fresnel::ttl = TTL;

#endif
