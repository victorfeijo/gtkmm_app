#ifndef GTKMM_APP_WIREFRAME
#define GTKMM_APP_WIREFRAME

#include "drawable_object.h"
#include "coordinate.h"

using namespace std;

class WireFrame : public DrawableObject
{
public:
  WireFrame(string name, list<Coordinate*> Coordinates);
  ~WireFrame();
  virtual list<Coordinate*> getCoordinates();
};
#endif // GTKMM_APP_WIREFRAME
