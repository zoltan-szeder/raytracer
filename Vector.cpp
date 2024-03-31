struct Vector
{
  float px, py, pz;
  float rx, ry, rz;
  float sx, sy, sz;

  Vector* parent;


  Vector( const float px = 0, const float py = 0, const float pz = 0, 
    Vector* parent = NULL,
    const float rx = 0, const float ry = 0, const float rz = 0,
    const float sx = 1, const float sy = 1, const float sz = 1 )
  {
    this->px = px;
    this->py = py;
    this->pz = pz;

    this->rx = rx;
    this->ry = ry;
    this->rz = rz;

    this->sx = sx;
    this->sy = sy;
    this->sz = sz;

    this->parent = parent;
  }

  Vector( const Vector& v )
  {
    *this=v;
  }

  Vector operator+( const Vector& v ) const
  {
    Vector vr( *this );
    vr.px += v.px;
    vr.py += v.py;
    vr.pz += v.pz;
    return vr;
  }

  Vector operator-(  ) const
  {
    Vector v( *this );
    v.px = -v.px;
    v.py = -v.py;
    v.pz = -v.pz;
    return v;
  }

  Vector operator-( const Vector& v ) const
  {
    return *this + ( -v );
  }

  Vector operator*( const float s ) const
  {
    Vector v = *this;
    v.px = px*s;
    v.py = py*s;
    v.pz = pz*s;
    return v;
  }

  Vector operator%( const Vector& v ) const
  {
    Vector n;
    n.px = py * v.pz - pz * v.py;
    n.py = pz * v.px - px * v.pz;
    n.pz = px * v.py - py * v.px;
    return n;
  }

  float operator*( const Vector& v ) const
  {
    return px*v.px + py*v.py + pz*v.pz;
  }

  Vector operator/( const float s ) const
  {
    Vector v = *this;
    v.px = px/s;
    v.py = py/s;
    v.pz = pz/s;
    return v;
  }

  Vector& operator=( const Vector& v )
  {
    px = v.px;
    py = v.py;
    pz = v.pz;

    rx = v.rx;
    ry = v.ry;
    rz = v.rz;

    sx = v.sx;
    sy = v.sy;
    sz = v.sz;
    parent = v.parent;

    return *this;
  }

  Vector& operator+=( const Vector& v )
  {
    px += v.px;
    py += v.py;
    pz += v.pz;

    return *this;
  }

  Vector deconvert( const Vector* v = NULL ) const
  {
    if( v )
    {
      Vector v2 = *v;
      v2 = scale( v2, this->sx, this->sy, this->sz );
      v2 = rotatex( v2, this->rx );
      v2 = rotatey( v2, this->ry );
      v2 = rotatez( v2, this->rz );
      v2 = translate( v2, *this );
      v2.parent = v->parent;
      if( parent )
      {
        return parent->deconvert( &v2 );
      }
      else
      {
        return v2;
      }
    }
    else
    {
      if( parent )
      {
        return parent->deconvert( this );
      }
      else
      {
        return Vector( *this );
      }
    }
  }

  Vector deconvertdir( const Vector* v = NULL ) const
  {
    if( v )
    {
      Vector v2 = *v;
      v2 = scale( v2, this->sx, this->sy, this->sz );
      v2 = rotatex( v2, this->rx );
      v2 = rotatey( v2, this->ry );
      v2 = rotatez( v2, this->rz );
      v2.parent = v->parent;
      if( parent )
      {
        return parent->deconvert( &v2 );
      }
      else
      {
        return v2;
      }
    }
    else
    {
      if( parent )
      {
        return parent->deconvert( this );
      }
      else
      {
        return Vector( *this );
      }
    }
  }

  Vector convert( const Vector* v = NULL ) const
  {
    if( v )
    {
      Vector v2;
      if( parent )
      {
        v2 = parent->convert( v );
      }
      else
      {
        v2 = *v;
      }
      v2 = translate( v2, -*this );
      v2 = rotatez( v2, -this->rz );
      v2 = rotatey( v2, -this->ry );
      v2 = rotatex( v2, -this->rx );
      v2 = scale( v2, 1.0/this->sx, 1.0/this->sy, 1.0/this->sz );
      v2.parent = v->parent;
      return v2;
    }
    else
    {
      if( parent )
      {
        return parent->convert( this );
      }
      else
      {
        return *this;
      }
    }
  }

  Vector convertdir( const Vector* v = NULL ) const
  {
    if( v ) 
    {   
      Vector v2; 
      if( parent )
      {   
        v2 = parent->convert( v );
      }   
      else
      {   
        v2 = *v; 
      }   
      v2 = rotatez( v2, -this->rz );
      v2 = rotatey( v2, -this->ry );
      v2 = rotatex( v2, -this->rx );
      v2 = scale( v2, 1.0/this->sx, 1.0/this->sy, 1.0/this->sz );
      v2.parent = v->parent;
      return v2; 
    }   
    else
    {   
      if( parent )
      {   
        return parent->convert( this );
      }   
      else
      {   
        return *this;
      }   
    }   
  }

  Vector normalize(  ) const
  {
    return *this/abs();
  }

  float abs(  ) const
  {
    return sqrt( px*px + py*py + pz*pz );
  }

  static Vector scale( Vector v, 
    const float x, const float y, const float z )
  {
    v.px = v.px * x;
    v.py = v.py * y;
    v.pz = v.pz * z;
    return v;
  }

  static Vector rotate( Vector v, 
    const float alpha, const float beta, const float gamma )
  {
    v = rotatex( v, alpha );
    v = rotatey( v, beta );
    v = rotatez( v, gamma );
    return v;
  }

  static Vector translate( Vector v, const Vector& t )
  {
    v += t;
    return v;
  }

  static Vector rotatex( const Vector& v, const float alpha )
  {
    if( fabs( alpha ) < ZERO )
    {
      return v;
    }
    return Vector(
      v.px,
      v.py * cos( alpha ) + v.pz * -sin( alpha ),
      v.py * sin( alpha ) + v.pz *  cos( alpha ) );
  }

  static Vector rotatey( const Vector& v, const float beta )
  {
    if( fabs( beta ) < ZERO )
    {
      return v;
    }
    return Vector(
      v.px *  cos( beta ) + v.pz * sin( beta ),
      v.py,
      v.px * -sin( beta ) + v.pz * cos( beta ) );
  }

  static Vector rotatez( const Vector& v, const float gamma )
  {
    if( fabs( gamma ) < ZERO )
    {
      return v;
    }
    return Vector(
      v.px * cos( gamma ) + v.py * -sin( gamma ),
      v.px * sin( gamma ) + v.py *  cos( gamma ),
      v.pz );
  }
};
