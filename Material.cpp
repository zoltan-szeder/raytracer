struct Material {
  virtual Color bounce( const Intersection& in, Light** lights, int s ) = 0;
};

