#include "Ray.hpp"

Ray::Ray(const Vector& p0, const Vector& v0) {
  p = p0;
  v = v0;
}

Ray Ray::convert(Vector* vec) {
  return Ray(
    vec->convert(&p),
    vec->convertdir(&v)
  );
}

Ray Ray::deconvert(Vector* vec) {
  return Ray(
    vec->deconvert(&p),
    vec->deconvertdir(&v)
  );
}

