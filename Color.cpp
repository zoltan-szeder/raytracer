struct Color {
public:
  float r, g, b;

  Color( float r0 = 0, float g0 = 0, float b0 = 0 ) {
	  r = r0; g = g0; b = b0;
  }

  Color operator*( float a ) {
	  return Color( r * a, g * a, b * a );
  }

  Color operator*( const Color& c ) {
	  return Color( r * c.r, g * c.g, b * c.b );
  }

  Color operator/( const Color& c ) {
	  return Color( r / c.r, g / c.g, b / c.b );
  }

  Color operator+( const Color& c ) {
 	  return Color( r + c.r, g + c.g, b + c.b );
  }

  Color operator-()
  {
    return Color( -r, -g, -b );
  }

  Color operator-( float a )
  {
    return Color( r-a, g-a, b-a );
  }

  Color operator-( const Color& c )
  {
    return Color( r-c.r, g-c.g, b-c.b );
  }

  Color& operator+=( const Color& c ) {
 	  r += c.r;
    g += c.g;
    b += c.b;
    return *this;
  }

  Color operator^( float p )
  {
    return Color( pow( r, p ), pow( g, p ), pow( b, p ) );
  }

  Color saturate( float min, float max ){
    return Color( fmin( fmax( r, min ), max ), fmin( fmax( g, min ), max ), fmin( fmax( b, min ), max ));
  }
};
