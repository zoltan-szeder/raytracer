#include "Vector.hpp"

Vector::Vector(const float px, const float py, const float pz, 
  Vector* parent,
  const float rx, const float ry, const float rz,
  const float sx, const float sy, const float sz)
{
  this->px = px;
  this->py = py;
  this->pz = pz;

  this->rx = rx;
  this->ry = ry;
  this->rz = rz;

  this->sx = sx;
  this->sy = sy;
  this->sz = sz;

  this->parent = parent;
}

Vector::Vector(const Vector& v)
{
  *this=v;
}

Vector Vector::operator+(const Vector& v) const
{
  Vector vr(*this);
  vr.px += v.px;
  vr.py += v.py;
  vr.pz += v.pz;
  return vr;
}

Vector Vector::operator-() const
{
  Vector v(*this);
  v.px = -v.px;
  v.py = -v.py;
  v.pz = -v.pz;
  return v;
}

Vector Vector::operator-(const Vector& v) const
{
  return *this + (-v);
}

Vector Vector::operator*(const float s) const
{
  Vector v = *this;
  v.px = px*s;
  v.py = py*s;
  v.pz = pz*s;
  return v;
}

Vector Vector::operator%(const Vector& v) const
{
  Vector n;
  n.px = py * v.pz - pz * v.py;
  n.py = pz * v.px - px * v.pz;
  n.pz = px * v.py - py * v.px;
  return n;
}

float Vector::operator*(const Vector& v) const
{
  return px*v.px + py*v.py + pz*v.pz;
}

Vector Vector::operator/(const float s) const
{
  Vector v = *this;
  v.px = px/s;
  v.py = py/s;
  v.pz = pz/s;
  return v;
}

Vector& Vector::operator=(const Vector& v)
{
  px = v.px;
  py = v.py;
  pz = v.pz;

  rx = v.rx;
  ry = v.ry;
  rz = v.rz;

  sx = v.sx;
  sy = v.sy;
  sz = v.sz;
  parent = v.parent;

  return *this;
}

Vector& Vector::operator+=(const Vector& v)
{
  px += v.px;
  py += v.py;
  pz += v.pz;

  return *this;
}

Vector Vector::deconvert(const Vector* v) const
{
  if(v)
  {
    Vector v2 = *v;
    v2 = scale(v2, this->sx, this->sy, this->sz);
    v2 = rotatex(v2, this->rx);
    v2 = rotatey(v2, this->ry);
    v2 = rotatez(v2, this->rz);
    v2 = translate(v2, *this);
    v2.parent = v->parent;
    if(parent)
    {
      return parent->deconvert(&v2);
    }
    else
    {
      return v2;
    }
  }
  else
  {
    if(parent)
    {
      return parent->deconvert(this);
    }
    else
    {
      return Vector(*this);
    }
  }
}

Vector Vector::deconvertdir(const Vector* v) const
{
  if(v)
  {
    Vector v2 = *v;
    v2 = scale(v2, this->sx, this->sy, this->sz);
    v2 = rotatex(v2, this->rx);
    v2 = rotatey(v2, this->ry);
    v2 = rotatez(v2, this->rz);
    v2.parent = v->parent;
    if(parent)
    {
      return parent->deconvert(&v2);
    }
    else
    {
      return v2;
    }
  }
  else
  {
    if(parent)
    {
      return parent->deconvert(this);
    }
    else
    {
      return Vector(*this);
    }
  }
}

Vector Vector::convert(const Vector* v) const
{
  if(v)
  {
    Vector v2;
    if(parent)
    {
      v2 = parent->convert(v);
    }
    else
    {
      v2 = *v;
    }
    v2 = translate(v2, -*this);
    v2 = rotatez(v2, -this->rz);
    v2 = rotatey(v2, -this->ry);
    v2 = rotatex(v2, -this->rx);
    v2 = scale(v2, 1.0/this->sx, 1.0/this->sy, 1.0/this->sz);
    v2.parent = v->parent;
    return v2;
  }
  else
  {
    if(parent)
    {
      return parent->convert(this);
    }
    else
    {
      return *this;
    }
  }
}

Vector Vector::convertdir(const Vector* v) const
{
  if(v) 
  {   
    Vector v2; 
    if(parent)
    {   
      v2 = parent->convert(v);
    }   
    else
    {   
      v2 = *v; 
    }   
    v2 = rotatez(v2, -this->rz);
    v2 = rotatey(v2, -this->ry);
    v2 = rotatex(v2, -this->rx);
    v2 = scale(v2, 1.0/this->sx, 1.0/this->sy, 1.0/this->sz);
    v2.parent = v->parent;
    return v2; 
  }   
  else
  {   
    if(parent)
    {   
      return parent->convert(this);
    }   
    else
    {   
      return *this;
    }   
  }   
}

Vector Vector::normalize() const
{
  return *this/abs();
}

float Vector::abs() const
{
  return sqrt(px*px + py*py + pz*pz);
}
