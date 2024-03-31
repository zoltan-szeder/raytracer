struct AmbientLight : Light {
public:
  Color ac;
  float ap;

  AmbientLight( const Color& ac0, const float ap0 = 1 )
  {
    ac = ac0;
    ap = ap0;
  }

  Lightning light( const Intersection&, const float )
  {
    return Lightning( ac*ap, Color(), Color() );
  }
};
