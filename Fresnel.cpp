#include "Fresnel.hpp"

Fresnel::Fresnel(const Color& n0, const Color& k0, const Color& cd0, const Color& cs0, bool refl0, bool refr0, float shine0) {
  n = n0;
  k = k0;

  cd = cd0;
  cs = cs0;

  refl = refl0;
  refr = refr0;

  shine = shine0;

  F0 = fresnelF0();
}

Color Fresnel::bounce(const Intersection& in, Light** lights, const int s) {
  Color color;

  for(int i = 0; i < s; i++) {   
    Lightning l = lights[i]->light(in, shine);
    color += cd*l.a + cd*l.d + cs*l.s;
  }

  if(ttl == 0) {
    return color;
  }

  if(refl) {
    Ray r = reflect(in);
    ttl--;
    color += fresnel(in) * camera.trace(&r);
    ttl++;
  }

  if(refr) {
    Intersection inters = refract(in);
    if(inters.v) {
      Ray r(inters.p, inters.d);
      ttl--;
      color += (Color(1, 1, 1) - fresnel(in))*camera.trace(&r);
      ttl++;
    }
  }

  return color.saturate(0, 1);
}

Color Fresnel::fresnelF0() {
  Color k2 = k*k;
  Color n1 = n - 1;
  Color n2 = n + 1;
  return (n1*n1 + k2)/(n2*n2 + k2) ;
};

Color Fresnel::fresnel(const Intersection& in) {
  float costheta = fabs(in.d*in.n);
  return F0 + (-F0 + 1) * pow(1 - costheta, 5);
}

Ray Fresnel::reflect(const Intersection& in) {
  Vector P = in.p;
  Vector V = in.d;
  Vector N = in.n;
  float costheta = fabs(N*V);
  return Ray(P, V + N*costheta*2.0);
}

Intersection Fresnel::refract(const Intersection& in) {
  Vector N = in.n;
  Vector V = in.d;
  float costheta = -V*N;
  Color ncurr(1, 1, 1);

  if(costheta < 0) {
    costheta = -costheta, N = -N;
  }

  if(fmod(ttl, 2) == fmod(TTL, 2)) {
    ncurr = n;
  } else {
    ncurr = ncurr / n;
  }
 
  float d = 1.0 - (1.0 - costheta*costheta)/(ncurr.r*ncurr.r);
  if(d < 0) {
    return Intersection();
  }

  Vector v = V/ncurr.r + N*(costheta/ncurr.r - sqrt(d));
  return Intersection(v, in.p, N);
}
