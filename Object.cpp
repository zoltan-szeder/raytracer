struct Object {
public:
  Material* m;
  Vector* p;

  Object( Vector* p0, Material* m0)
  {
    p = p0;
    m = m0;
  }

  Vector* getPosition()
  {
    return p;
  }

  Material* getMaterial()
  {
    return m;
  }

  virtual Intersection intersect( Ray* r ) = 0;
};
