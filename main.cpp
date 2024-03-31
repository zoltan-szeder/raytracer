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
#include "Light.cpp"
#include "Material.cpp"
#include "Object.cpp"
#include "Model.cpp"

#include "Screen.cpp"
#include "Camera.cpp"

Vector origo;
Screen screen;
Model model;
Camera camera( &model, Vector( 30, 35, 15 ), Vector( 0, 0, 5 ), &screen );

float frand( float min, float max)
{
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

void initialize( ) {
  srand( 8762 );

  AmbientLight l0( Color( 1, 1, 1 ), 0.02 );
  PointLight l1( Vector(  50,  50, 40 ), Color( 1, 0.5, 0.5 ), Color( 1, 0.5, 0.5 ), 3000, 6000 );
  PointLight l2( Vector( -50,  50, 40 ), Color( 0.5, 1, 0.5 ), Color( 0.5, 1, 0.5 ), 3000, 6000 );
  PointLight l3( Vector( -20, -70, 40 ), Color( 0.5, 0.5, 1 ), Color( 0.5, 0.5, 1 ), 3000, 6000 );

  model.addLight( &l0 );
  model.addLight( &l1 );
  model.addLight( &l2 );
  model.addLight( &l3 );

  FloorMaterial floormaterial;

  Fresnel gold( Color( 0.17, 0.35, 1.5 ), Color( 3.1, 2.7, 1.9 ),
                Color( 0.27, 0.16, 0.0 ), Color( 1, 0.94, 0.84 ), true, false );
  Fresnel glass( Color( 1.5, 1.5, 1.5 ), Color( ),
                Color( 0.0, 0.0, 0.0 ), Color( 1, 1, 1 ), false, true );
  Fresnel silver( Color( 0.14, 0.16, 0.13 ), Color( 4.1, 2.3, 3.1 ),
                Color( 0.2, 0.2, 0.2 ), Color( 1, 1, 1 ), true, false );

  Vector floorcenter( 0, 0, 0, NULL, 0, 0, 0, 1, 1, 1 );

  Vector sphere0center( 20, 0, 5 );
  Vector sphere1center( frand( -1, 1 ), frand( -1, 1 ), frand( 0, 1 ) );
  Vector sphere2center( frand( -1, 1 ), frand( -1, 1 ), frand( 0, 1 ) );

  Vector paraboloid0center( 0, -5, 0, NULL, 0, 0, 0.5*M_PI );
  Vector paraboloid1center( frand( -1, 1 ), frand( -1, 1 ) );
  Vector paraboloid2center( frand( -1, 1 ), frand( -1, 1 ) );

  Vector tube0center( 0, 18.28, 0, NULL, 0, 0, 0, 1, 1, 1 );
  Vector tube1center( frand( 0, 1 ), frand( 0, 1 ), frand( 0.25, 0.75 ) );
  Vector tube2center( frand( 0, 1 ), frand( 0, 1 ), frand( 0.25, 0.75 ) );

  Floor floor( &floorcenter, &floormaterial );

  Sphere sphere0( &sphere0center, &gold, 5 );
  Sphere sphere1( &sphere1center, &gold, 5 );
  sphere0.createChild( &sphere1 );
  Sphere sphere2( &sphere2center, &gold, 5 );
  sphere1.createChild( &sphere2 );

  Paraboloid paraboloid0( &paraboloid0center, &silver, sqrt(20) );
  Paraboloid paraboloid1( &paraboloid1center, &silver, sqrt(20) );
  paraboloid0.createChild( &paraboloid1 );
  Paraboloid paraboloid2( &paraboloid2center, &silver, sqrt(20) );
  paraboloid1.createChild( &paraboloid2 );

  Tube tube0( &tube0center, &glass, 5, 20 );
  Tube tube1( &tube1center, &glass, 5, 20 );
  tube0.createChild( &tube1 );
  Tube tube2( &tube2center, &glass, 5, 20 );
  tube1.createChild( &tube2 );
  
  model.addObject( &floor );
  model.addObject( &sphere0 );
  model.addObject( &sphere1 );
  model.addObject( &sphere2 );
  model.addObject( &paraboloid0 );
  model.addObject( &paraboloid1 );
  model.addObject( &paraboloid2 );
  model.addObject( &tube0 );
  model.addObject( &tube1 );
  model.addObject( &tube2 );

  camera.render();

  glutPostRedisplay();
}

void display( ) {
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

