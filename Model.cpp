#define MAXOBJECTS 10
#define MAXLIGHTS 4

struct Model {
public:
  Object* objects[MAXOBJECTS];
  int p;

  Light* lights[MAXLIGHTS];
  int lp;

  Model()
  {
    p = 0;
    lp = 0;
  }

  void addObject( Object* o )
  {
    objects[p] = o;
    p++;
  }

  Object* getObject( int i )
  {
    if( i < 0 || i >= p )
    {
      return NULL;
    }
    return objects[i];
  }

  void addLight( Light* l )
  {
    lights[lp] = l;
    lp++;
  }

  Light** getLights()
  {
    return lights;
  }

  int getLightsNum()
  {
    return lp;
  }

  Intersection intersect( Ray* r, Object** o )
  {
    Intersection min( false );

    for( int i = 0; i < p; i++ )
    {
      Object* ob = objects[i];
      Vector* v = ob->getPosition();
      Ray rc = r->convert( v );
      Intersection in = ob->intersect( &rc );
      if( ! in.v )
      {
        continue;
      }
      Intersection inc = in.deconvert( v );
      if( ! min.v || ( min.p - r->p ).abs() > ( inc.p - r->p ).abs() )
      {
        min = inc;
        *o = ob;
      }
    }
    return min;
  }
  
};

