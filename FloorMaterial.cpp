struct FloorMaterial : Material {
  DiffuseBlinn m1;
  DiffuseBlinn m2;
  float shine;

  FloorMaterial(  )
    : m1( Color( 0, 0, 0 ), Color( 1, 1, 1 ) ),
      m2( Color( 1, 1, 1 ), Color( 1, 1, 1 ) )
  {
    shine = 64;
  }

  Color bounce( const Intersection& in, Light** lights, int s )
  {
    Material* m = getMaterialAt( in.p );
    return m->bounce( in, lights, s );
  }

  Material* getMaterialAt( const Vector& v )
  {
    float x = fabs( fmod( v.px, 10 ) );
    float y = fabs( fmod( v.py, 10 ) );

    bool b = ( ( x < 5 ) ^ ( y < 5 ) ^ ( v.px < 0 ) ^ ( v.py < 0 ) );

    Material* m = ( b ? (Material*) &m1 : (Material*) &m2  );

    return m;
  }
};
