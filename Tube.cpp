struct Tube : Object {
public:
  float rad;
  float h;

  Circle cap;
  Vector top;
  Vector bottom;

  Tube( Vector* p0, Material* m0, float rad0 = 0.5, float h0 = 1 )
    : Object( p0, m0 ),
      cap( p0, m0, rad0 ),
      top( 0, 0, h0 ),
      bottom( 0, 0, 0, NULL, 0, M_PI, 0, 1, 1, 1 )
  {
    rad = rad0;
    h = h0;
  }

  Intersection intersect( Ray* r )
  {
    Ray capr = r->convert( &top );
    Intersection capt = cap.intersect( &capr );
    Intersection capi;
    float capl;
    if( capt.v )
    {
      capi = capt.deconvert( &top );
      capl = ( capi.p - r->p ).abs();
    }

    capr = r->convert( &bottom );
    capt = cap.intersect( &capr );
    capt = capt.deconvert( &bottom );
    float capl2 = ( capt.p - r->p ).abs();
    if( capt.v && capl > capl2 )
    {
      capi = capt;
      capl = capl2;
    }

    float a = r->v.px*r->v.px + r->v.py*r->v.py;
    float b = 2.0*( r->p.px*r->v.px + r->p.py*r->v.py);
    float c = r->p.px*r->p.px + r->p.py*r->p.py - rad*rad;

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

    Vector n( p.px, p.py );
    n = n.normalize();

    if( p.pz > h || p.pz < ZERO )
    {
      l = fmax( l1, l2 );
      p = r->p + r->v*l;

      n = Vector( -p.px, -p.py );
      n = n.normalize();
    }

    float length = p.abs();

    if( capi.v && capl < length )
    {
      return capi;
    }

    if( p.pz > h || p.pz < ZERO )
    {
      return Intersection();
    }

    return Intersection( r->v.normalize(), p, n);
  }

  void createChild( Tube* tube )
  {
    Vector* v = tube->p;

    Vector n = *v;
    n.pz = 0;
    n = n.normalize();

    v->px = n.px*rad;
    v->py = n.py*rad;
    v->pz = v->pz*h;

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

    tube->rad = rad/2;
    tube->h = h/2;
    tube->cap.r = tube->rad;
    tube->top.pz = tube->h;
  }
};


