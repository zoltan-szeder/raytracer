#include "Object.hpp"

Object::Object(Vector* p0, Material* m0) {
  p = p0;
  m = m0;
}

Vector* Object::getPosition() {
  return p;
}

Material* Object::getMaterial() {
  return m;
}
