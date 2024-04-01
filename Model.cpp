#include "Model.hpp"

Model::Model() {
  p = 0;
  lp = 0;
}

void Model::addObject(Object* o) {
  objects[p] = o;
  p++;
}

Object* Model::getObject(int i) {
  if(i < 0 || i >= p)
  {
    return NULL;
  }
  return objects[i];
}

void Model::addLight(Light* l) {
  lights[lp] = l;
  lp++;
}

Light** Model::getLights() {
  return lights;
}

int Model::getLightsNum() {
  return lp;
}

Intersection Model::intersect(Ray* r, Object** o) {
  Intersection min(false);

  for(int i = 0; i < p; i++)
  {
    Object* ob = objects[i];
    Vector* v = ob->getPosition();
    Ray rc = r->convert(v);
    Intersection in = ob->intersect(&rc);
    if(! in.v)
    {
      continue;
    }
    Intersection inc = in.deconvert(v);
    if(! min.v || (min.p - r->p).abs() > (inc.p - r->p).abs())
    {
      min = inc;
      *o = ob;
    }
  }
  return min;
}
