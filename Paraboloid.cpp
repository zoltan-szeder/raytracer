struct Paraboloid : Object {
public:
  float h;
  Circle cap;
  Vector top;

  Paraboloid( Vector* p0, Material* m0, float r0 = 2 )
    : Object( p0, m0 ),
      cap( p0, m0, r0 ),
      top( 0, 0, r0*r0 )
  {
    h = r0*r0;
  }

  Intersection intersect( Ray* r )
  {
    Ray capr = r->convert( &top );
    Intersection capi = cap.intersect( &capr );
    if( capi.v )
    {
      return capi.deconvert( &top );
    }

    float a = r->v.px*r->v.px + r->v.py*r->v.py;
    float b = 2.0*( r->p.px*r->v.px + r->p.py*r->v.py) - r->v.pz;
    float c = r->p.px*r->p.px + r->p.py*r->p.py - r->p.pz;

    float d = b*b - 4*a*c;

    if( d < 0 )
    {
      return Intersection();
    }

    float l1 = ( -b + sqrt(d) )/( 2*a );
    float l2 = ( -b - sqrt(d) )/( 2*a );
    float l;

    if( l1 < ZERO && l2 < ZERO )
    {
      return Intersection();
    }
    else if( l1 < ZERO )
    {
      l = l2;
    }
    else if( l2 < ZERO )
    {
      l = l1;
    }
    else {
      l = fmin( l1, l2 );
    }

    Vector p = r->p + r->v*l;

    if( p.pz > h )
    {
      return Intersection();
    }

    float dist = sqrt( p.px*p.px + p.py*p.py );
    float z = -1/( 2*dist );

    Vector n = p;

    n.pz = 0;
    n = n.normalize();
    n.pz = z;
    n = n.normalize();

    return Intersection( r->v.normalize(), p, n );
  }

  void createChild( Paraboloid* parab )
  {
    Vector* v = parab->p;
    v->pz = 0;
    *v = v->normalize() * frand( sqrt( h ) / 2, sqrt( h ) );
    float r = v->abs();
    v->pz = r*r;

    Vector n( v->px, v->py );
    n = n.normalize();
    n.pz = -1.0/(2.0*r);
    n = n.normalize();

    *v = p->deconvert( v );
    n = p->deconvertdir( &n );
    n = n.normalize();

    v->rz = ( n.py >= 0 ? acos( n.px ) : -acos( n.px ) );
    float sinphi = sqrt( 1 - n.px*n.px );
    if( sinphi > ZERO )
    {   
      float pz = n.pz/sinphi;
      v->ry = acos( pz );
    }   
    else
    {   
      v->ry = ( n.px > 0 ? M_PI/2 : -M_PI/2 );
    }

    v->parent = NULL;

    parab->h = h / 2;
    parab->cap.r = sqrt( parab->h );
    parab->top.pz = parab->h;
  }

};


