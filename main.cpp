#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <math.h>
#include <stdlib.h>

#define ZERO 0.0001

#include "Color.cpp"
#include "Vector.cpp"
#include "Intersection.cpp"
#include "Ray.cpp"
#include "Lightning.cpp"
#include "Light.hpp"
#include "Material.hpp"
#include "Object.cpp"
#include "Model.cpp"

#include "Screen.cpp"
#include "Camera.cpp"

Vector origo;
Screen screen;
Model model;
Camera camera(
  &model,
  Vector(30, 35, 15),
  Vector(0, 0, 5),
  &screen
);

float frand(float min, float max) {
  return (max-min)*rand()/RAND_MAX + min;
}

#include "DiffuseBlinn.cpp"
#include "Fresnel.cpp"
#include "FloorMaterial.cpp"

#include "AmbientLight.cpp"
#include "PointLight.cpp"

#include "Circle.cpp"
#include "Sphere.cpp"
#include "Paraboloid.cpp"
#include "Tube.cpp"
#include "Floor.cpp"

void initialize() {
  srand(8762);

  // Create ambient lighting
  AmbientLight l0(
    Color(1, 1, 1),
    0.02
  );
  model.addLight(&l0);

  // Create light red point light
  PointLight l1(
    Vector(50,  50, 40), Color(1, 0.5, 0.5), Color(1, 0.5, 0.5),
    3000, 6000
  );
  model.addLight(&l1);

  // Create light green point light
  PointLight l2(
    Vector(-50,  50, 40), Color(0.5, 1, 0.5), Color(0.5, 1, 0.5),
    3000, 6000
  );
  model.addLight(&l2);

  // Create light blue point light
  PointLight l3(
    Vector(-20, -70, 40), Color(0.5, 0.5, 1), Color(0.5, 0.5, 1),
    3000, 6000
  );
  model.addLight(&l3);

  // Create Floor
  FloorMaterial floormaterial;
  Vector floorcenter(0, 0, 0, NULL, 0, 0, 0, 1, 1, 1);
  Floor floor(&floorcenter, &floormaterial);
  model.addObject(&floor);

  // Create Gold Spheres
  Fresnel gold(
    Color(0.17, 0.35, 1.5), Color(3.1, 2.7, 1.9),
    Color(0.27, 0.16, 0.0), Color(1, 0.94, 0.84),
    true, false
  );

  Vector sphere0center(20, 0, 5);
  Sphere sphere0(&sphere0center, &gold, 5);
  model.addObject(&sphere0);

  Vector sphere1center(frand(-1, 1), frand(-1, 1), frand(0, 1));
  Sphere sphere1(&sphere1center, &gold, 5);
  sphere0.createChild(&sphere1);
  model.addObject(&sphere1);

  Vector sphere2center(frand(-1, 1), frand(-1, 1), frand(0, 1));
  Sphere sphere2(&sphere2center, &gold, 5);
  sphere1.createChild(&sphere2);
  model.addObject(&sphere2);

  // Create Silver Paraboloids
  Fresnel silver(
    Color(0.14, 0.16, 0.13), Color(4.1, 2.3, 3.1),
    Color(0.2, 0.2, 0.2), Color(1, 1, 1),
    true, false
  );

  Vector paraboloid0center(0, -5, 0, NULL, 0, 0, 0.5*M_PI);
  Paraboloid paraboloid0(&paraboloid0center, &silver, sqrt(20));
  model.addObject(&paraboloid0);

  Vector paraboloid1center(frand(-1, 1), frand(-1, 1));
  Paraboloid paraboloid1(&paraboloid1center, &silver, sqrt(20));
  paraboloid0.createChild(&paraboloid1);
  model.addObject(&paraboloid1);

  Vector paraboloid2center(frand(-1, 1), frand(-1, 1));
  Paraboloid paraboloid2(&paraboloid2center, &silver, sqrt(20));
  paraboloid1.createChild(&paraboloid2);
  model.addObject(&paraboloid2);

  // Create Glass Tubes
  Fresnel glass(
    Color(1.5, 1.5, 1.5), Color(0.0, 0.0, 0.0),
    Color(0.0, 0.0, 0.0), Color(1, 1, 1),
    false, true
  );

  Vector tube0center(0, 18.28, 0, NULL, 0, 0, 0, 1, 1, 1);
  Tube tube0(&tube0center, &glass, 5, 20);
  model.addObject(&tube0);

  Vector tube1center(frand(0, 1), frand(0, 1), frand(0.25, 0.75));
  Tube tube1(&tube1center, &glass, 5, 20);
  tube0.createChild(&tube1);
  model.addObject(&tube1);

  Vector tube2center(frand(0, 1), frand(0, 1), frand(0.25, 0.75));
  Tube tube2(&tube2center, &glass, 5, 20);
  tube1.createChild(&tube2);
  model.addObject(&tube2);

  camera.render();

  glutPostRedisplay();
}

void display() {
  screen.draw();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(screen.x, screen.y);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Raytracer");

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    initialize();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}

