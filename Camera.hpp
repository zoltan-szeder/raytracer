#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Model.hpp"
#include "Vector.hpp"
#include "Screen.hpp"
#include "Color.hpp"

struct Camera {
private:
  Vector pos;
  Vector focus;
  Vector distance;
  Vector up;
  Vector right;
  Screen* screen;

  Model* model;

public:
  Camera( Model* model0, const Vector& pos0, const Vector& focus0, Screen* screen0 );

  void render();

  Color trace( Ray* r );
};

#endif
