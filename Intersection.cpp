#include "Intersection.hpp"

Intersection::Intersection(bool v0) {
  v = v0;
}

Intersection::Intersection(const Vector& d0, const Vector& p0, const Vector& n0, bool v0) {
  d = d0;
  p = p0;
  n = n0;
  v = v0;
}

Intersection::Intersection(const Intersection& i) {
  v = i.v;
  p = i.p;
  n = i.n;
  v = i.v;
}

Intersection Intersection::convert(Vector* vec) {
  return Intersection(
    vec->convertdir(&d).normalize(),
    vec->convert(&p),
    vec->convertdir(&n).normalize(),
    v
  );
}

Intersection Intersection::deconvert(Vector* vec) {
  return Intersection(
    vec->deconvertdir(&d).normalize(),
    vec->deconvert(&p),
    vec->deconvertdir(&n).normalize(),
    v
  );
}

