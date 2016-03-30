#ifndef GTKMM_APP_DRAWABLE_OBJECT
#define GTKMM_APP_DRAWABLE_OBJECT

 /*This class represent's a object such as line or polygon
 * to be drawed on the view port.
 * Include any library as need to use other's components.
 */
#include <list>
#include <string>
#include "coordinate.hpp"
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
  virtual string getType() = 0;
  void setCoordinates(list<Coordinate*> Coordinates)
  {
    this->Coordinates = Coordinates;
  }
protected:
  string name;
  list<Coordinate*> Coordinates;
};
#endif // GTKMM_APP_DRAWABLE_OBJECT
