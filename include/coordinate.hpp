#ifndef GTKMM_APP_COORDINATE
#define GTKMM_APP_COORDINATE

class Coordinate
{
public:
  Coordinate(long int x, long int y)
  : cord_x(x), cord_y(y)
  {}
  ~Coordinate() {}
  long int getx()
  {
    return cord_x;
  }
  long int gety()
  {
    return cord_y;
  }
protected:
  long int cord_x;
  long int cord_y;
};
#endif // GTKMM_APP_Coordinate
