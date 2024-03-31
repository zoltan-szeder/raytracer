struct Circle : Object
{
  float r;

  Circle( Vector* p, Material* m, float r0 )
    : Object( p, m )
  {
    r = r0;
  }

  Intersection intersect( Ray* ray )
  {
    Vector N( 0, 0, 1 );

    if( ray->v.pz == 0 )
    {
      return Intersection();
    }

    float l = -ray->p.pz/ray->v.pz;

    Vector p = ray->p + ray->v*l;

    if( p.abs() > r )
    {
       return Intersection();
    }

    if( ray->p.pz < 0 )
    {
      N.pz = -1;
    }

    return Intersection( ray->v.normalize(), p, N );
  }
};
