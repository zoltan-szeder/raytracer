#ifndef RAY_HPP
#define RAY_HPP

#include "Vector.hpp"

struct Ray
{
public:
  Vector p;
  Vector v;

  Ray(const Vector& p0, const Vector& v0);

  Ray convert(Vector* vec);

  Ray deconvert(Vector* vec);
};

#endif
