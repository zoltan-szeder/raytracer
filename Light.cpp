struct Light {
public:
  virtual Lightning light( const Intersection& in, const float shine = 0 ) = 0;
};

