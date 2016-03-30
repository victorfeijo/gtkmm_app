#ifndef GTKMM_APP_WIREFRAME
#define GTKMM_APP_WIREFRAME

#include "drawable_object.hpp"
#include "coordinate.hpp"

using namespace std;

class WireFrame : public DrawableObject
{
public:
  WireFrame(string name, list<Coordinate*> Coordinates);
  ~WireFrame();
  virtual list<Coordinate*> getCoordinates();
  virtual string getType();
};
#endif // GTKMM_APP_WIREFRAME
