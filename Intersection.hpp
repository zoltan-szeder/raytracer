#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include "Vector.hpp"

struct Intersection {
public:
  Vector p;
  Vector d;
  Vector n;
  bool v;

  Intersection(bool v0 = false);

  Intersection(const Vector& d0, const Vector& p0, const Vector& n0, bool v0 = true);

  Intersection(const Intersection& i);

  Intersection convert(Vector* vec);

  Intersection deconvert(Vector* vec);
};

#endif
