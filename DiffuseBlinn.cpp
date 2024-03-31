struct DiffuseBlinn : Material {
  Color cd;
  Color cs;
  float shine;

  DiffuseBlinn( const Color& cd0, const Color& cs0, const float shine0 = 64 )
  {
    cd = cd0;
    cs = cs0;
    shine = shine0;
  }

  Color bounce( const Intersection& in, Light** lights, const int s )
  {
    Color color;
    for( int i = 0; i < s; i++ )
    {
      Lightning l = lights[i]->light( in, shine );
      color += cd*l.a + cd*l.d + cs*l.s;
    }
    return color.saturate( 0, 1 );
  }
};
