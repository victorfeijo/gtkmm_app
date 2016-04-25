#ifndef GTKMM_APP_WIREFRAME
#define GTKMM_APP_WIREFRAME

#include "drawable_object.hpp"
#include "coordinate.hpp"

using namespace std;

class WireFrame : public DrawableObject
{
public:
  WireFrame(string name, list<Coordinate> coordinates);
  ~WireFrame();
  virtual string getTypeName();
  virtual object_type getType();
  virtual void resetWindowCoordinates();
};
#endif // GTKMM_APP_WIREFRAME
