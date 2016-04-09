#ifndef GTKMM_APP_POINT
#define GTKMM_APP_POINT

#include "drawable_object.hpp"
#include "coordinate.hpp"

using namespace std;

class Point : public DrawableObject
{
public:
  Point(string name, Coordinate point_cord);
  ~Point();
  virtual string getType();
};
#endif // GTKMM_APP_POINT
