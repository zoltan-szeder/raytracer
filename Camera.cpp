#include "Camera.hpp"

Camera::Camera(Model* model0, const Vector& pos0, const Vector& focus0, Screen* screen0) {
  model = model0;
  pos = pos0;
  focus = focus0;
  screen = screen0;

  Vector v = (focus - pos).normalize();

  if(v.px == 0 && v.py == 0)
  {
    if(v.pz > 0)
    {
      up = Vector(0, 0, 1);
      right = Vector(0, 1, 0);
    }
    else
    {
      up = Vector(0, 0, -1);
      right = Vector(0, -1, 0);
    }
  }
  else {
    float l = -(v.pz / (v * v));

    up = (Vector(0, 0, 1) + v*l).normalize();
    right = v % up;
  }

  distance = v*1.5;
}

void Camera::render() {
  Vector i = up / (screen->y / 2.0);
  Vector j = right / (screen->y / 2.0);
  int py = 0;
  for(int ly = -screen->y / 2; ly < screen->y / 2; ly++) {
    int px = 0;
    for(int lx = -screen->x / 2; lx < screen->x / 2; lx++) {
      Ray r(pos, distance + i*ly + j*lx);
      Color c = trace(&r);

        screen->canvas[py*screen->y + px] = c;
      px++;
    }
    py++;
    screen->draw();
  }
}

Color Camera::trace(Ray* r) const {
  Object* o[1];
  o[0] = NULL;
  Intersection in = model->intersect(r, o);

  if(*o) {
    Light** l = model->getLights();
    int s = model->getLightsNum();
    Material* m = (*o)->getMaterial();
    return m->bounce(in, l, s);
  }

  return Color(0.694, 0.914, 0.984);
}

