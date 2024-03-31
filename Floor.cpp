struct Floor : Object 
{
public:

  Floor( Vector* p0, Material* m0 ) : Object( p0, m0 )
  {
  }

  Intersection intersect( Ray* r )
  {
    Vector N( 0, 0, 1 );
    if( r->v*N > 0 || r->p.pz < ZERO )
    {
      return Intersection();
    }

    float l = -r->p.pz/r->v.pz;

    return Intersection( r->v, r->p + r->v*l, N );
  }
};
