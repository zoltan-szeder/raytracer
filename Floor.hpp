#include "Object.hpp"
#include "Intersection.hpp"
#include "Material.hpp"
#include "Vector.hpp"
#include "Ray.hpp"

struct Floor : Object 
{
public:
  Floor(Vector* p0, Material* m0);
  Intersection intersect(Ray* r);
};
