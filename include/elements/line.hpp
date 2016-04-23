#ifndef GTKMM_APP_RECT
#define GTKMM_APP_RECT

#include "drawable_object.hpp"
#include "coordinate.hpp"

using namespace std;

class Line : public DrawableObject
{
public:
  Line(string name, Coordinate line_cord1, Coordinate line_cord2);
  ~Line();
  virtual string getTypeName();
  virtual object_type getType();
  virtual void resetWindowCoordinates();
};
#endif // GTKMM_APP_RECT
