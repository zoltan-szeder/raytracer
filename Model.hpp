#ifndef MODEL_HPP
#define MODEL_HPP

#include "Object.hpp"
#include "Light.hpp"
#include "Intersection.hpp"
#include "Ray.hpp"

#define MAXOBJECTS 10
#define MAXLIGHTS 4

struct Model {
public:
  Object* objects[MAXOBJECTS];
  int p;

  Light* lights[MAXLIGHTS];
  int lp;

  Model();

  void addObject(Object* o);

  Object* getObject(int i);

  void addLight(Light* l);

  Light** getLights();

  int getLightsNum();

  Intersection intersect(Ray* r, Object** o) const;
};

#endif
