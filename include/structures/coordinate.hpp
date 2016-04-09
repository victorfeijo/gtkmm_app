#ifndef GTKMM_APP_COORDINATE
#define GTKMM_APP_COORDINATE

class Coordinate
{
public:
  Coordinate(double x, double y)
      : cord_x(x), cord_y(y), cord_z(1) {}
  Coordinate(double x, double y, double z)
      : cord_x(x), cord_y(y), cord_z(z) {}
  ~Coordinate() {}
  double getx()
  {
    return cord_x;
  }
  double gety()
  {
    return cord_y;
  }
  double getz()
  {
    return cord_z;
  }
protected:
  double cord_x, cord_y, cord_z;
};
#endif // GTKMM_APP_Coordinate
