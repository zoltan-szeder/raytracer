struct Sphere : Object {
public:
  float rad;

  Sphere( Vector* p0, Material* m0, float rad0 = 1 ) : Object( p0, m0 )
  {
    rad = rad0;
  }

  Intersection intersect( Ray* r )
  {
    float a = r->v.px*r->v.px + r->v.py*r->v.py + r->v.pz*r->v.pz;
    float b = 2.0*( r->p.px*r->v.px + r->p.py*r->v.py + r->p.pz*r->v.pz );
    float c = r->p.px*r->p.px + r->p.py*r->p.py + r->p.pz*r->p.pz - rad*rad;

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
    
    Vector n = r->p + r->v*l;
    return Intersection( r->v, n, n.normalize() );
  }

  void createChild( Sphere* sphere )
  {
    Vector* v = sphere->p;
    Vector n = v->normalize();

    *v = n*1.5*rad;

    *v = p->deconvert( v );

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

    sphere->rad = rad/2.0;

  }

};


