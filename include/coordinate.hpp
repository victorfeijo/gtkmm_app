#ifndef GTKMM_APP_COORDINATE
#define GTKMM_APP_COORDINATE

class Coordinate
{
public:
  Coordinate(int x, int y)
  : cord_x(x), cord_y(y)
  {}
  ~Coordinate() {}
  int getx()
  {
    return cord_x;
  }
  int gety()
  {
    return cord_y;
  }
protected:
  int cord_x;
  int cord_y;
};
#endif // GTKMM_APP_Coordinate
