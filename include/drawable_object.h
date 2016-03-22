#ifndef GTKMM_APP_DRAWABLE_OBJECT
#define GTKMM_APP_DRAWABLE_OBJECT

 /*This class represent's a object such as rect or polygon
 * to be drawed on the view port.
 * Include any library as need to use other's components.
 */
#include <list>
#include <string>
#include "coordinate.h"
using namespace std;

class DrawableObject
{
public:
  DrawableObject(string name)
  : name(name) {}
  DrawableObject(string name, list<Coordinate*> Coordinates)
  : name(name), Coordinates(Coordinates) {}
  ~DrawableObject() {}
  std::string getName()
  {
    return name;
  }
  virtual list<Coordinate*> getCoordinates() = 0;
protected:
  string name;
  list<Coordinate*> Coordinates;
};
#endif // GTKMM_APP_DRAWABLE_OBJECT
