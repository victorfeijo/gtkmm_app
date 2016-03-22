#ifndef GTKMM_APP_POINT
#define GTKMM_APP_POINT

#include "drawable_object.h"
#include "coordinate.h"

using namespace std;

class Point : public DrawableObject
{
public:
  Point(string name, Coordinate* point_cord);
  ~Point();
  virtual list<Coordinate*> getCoordinates();
};
#endif // GTKMM_APP_POINT
