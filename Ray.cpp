struct Ray
{
public:
  Vector p;
  Vector v;

  Ray( const Vector& p0, const Vector& v0 )
  {
    p = p0;
    v = v0;
  }

  Ray convert( Vector* vec )
  {
    return Ray( vec->convert( &p ), vec->convertdir( &v ) );
  }

  Ray deconvert( Vector* vec )
  {
    return Ray( vec->deconvert( &p ), vec->deconvertdir( &v ) );
  }
};
