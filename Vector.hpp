#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <stdlib.h>
#include <math.h>

#define ZERO 0.0001

struct Vector
{
  float px, py, pz;
  float rx, ry, rz;
  float sx, sy, sz;

  Vector* parent;

  Vector(const float px = 0, const float py = 0, const float pz = 0, 
    Vector* parent = NULL,
    const float rx = 0, const float ry = 0, const float rz = 0,
    const float sx = 1, const float sy = 1, const float sz = 1);

  Vector(const Vector& v);

  Vector operator+(const Vector& v) const;

  Vector operator-() const;

  Vector operator-(const Vector& v) const;

  Vector operator*(const float s) const;

  Vector operator%(const Vector& v) const;

  float operator*(const Vector& v) const;

  Vector operator/(const float s) const;

  Vector& operator=(const Vector& v);

  Vector& operator+=(const Vector& v);

  Vector deconvert(const Vector* v = NULL) const;

  Vector deconvertdir(const Vector* v = NULL) const;

  Vector convert(const Vector* v = NULL) const;

  Vector convertdir(const Vector* v = NULL) const;

  Vector normalize() const;

  float abs() const;

  static Vector scale(Vector v, 
    const float x, const float y, const float z)
  {
    v.px = v.px * x;
    v.py = v.py * y;
    v.pz = v.pz * z;
    return v;
  }
  
  static Vector rotate(Vector v, 
    const float alpha, const float beta, const float gamma)
  {
    v = rotatex(v, alpha);
    v = rotatey(v, beta);
    v = rotatez(v, gamma);
    return v;
  }
  
  static Vector translate(Vector v, const Vector& t)
  {
    v += t;
    return v;
  }
  
  static Vector rotatex(const Vector& v, const float alpha)
  {
    if(fabs(alpha) < ZERO)
    {
      return v;
    }
    return Vector(
      v.px,
      v.py * cos(alpha) + v.pz * -sin(alpha),
      v.py * sin(alpha) + v.pz *  cos(alpha));
  }
  
  static Vector rotatey(const Vector& v, const float beta)
  {
    if(fabs(beta) < ZERO)
    {
      return v;
    }
    return Vector(
      v.px *  cos(beta) + v.pz * sin(beta),
      v.py,
      v.px * -sin(beta) + v.pz * cos(beta));
  }

  static Vector rotatez(const Vector& v, const float gamma)
  {
    if(fabs(gamma) < ZERO)
    {
      return v;
    }
    return Vector(
      v.px * cos(gamma) + v.py * -sin(gamma),
      v.px * sin(gamma) + v.py *  cos(gamma),
      v.pz);
  }
};

#endif
