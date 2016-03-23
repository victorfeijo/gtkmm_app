#ifndef GTKMM_APP_RECT
#define GTKMM_APP_RECT

#include "drawable_object.hpp"
#include "coordinate.hpp"

using namespace std;

class Rect : public DrawableObject
{
public:
  Rect(string name, Coordinate* rect_cord1, Coordinate* rect_cord2);
  ~Rect();
  virtual list<Coordinate*> getCoordinates();
};
#endif // GTKMM_APP_RECT
