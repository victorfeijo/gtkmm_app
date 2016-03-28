#ifndef GTKMM_APP_COORDINATE
#define GTKMM_APP_COORDINATE

class Coordinate
{
public:
  Coordinate(long int x, long int y)
      : cord_x(x), cord_y(y), cord_z(0) {}
  Coordinate(long int x, long int y, long int z)
      : cord_x(x), cord_y(y), cord_z(z) {}
  ~Coordinate() {}
  long int getx()
  {
    return cord_x;
  }
  long int gety()
  {
    return cord_y;
  }
  long int getz()
  {
    return cord_z;
  }
protected:
  long int cord_x, cord_y, cord_z;
};
#endif // GTKMM_APP_Coordinate
