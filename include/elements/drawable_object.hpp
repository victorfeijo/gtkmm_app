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
  DrawableObject(string name);
  DrawableObject(string name, list<Coordinate*> coordinates);
  ~DrawableObject();
  std::string getName();
  virtual list<Coordinate*> getCoordinates() = 0;
  virtual string getType() = 0;
  void setCoordinates(list<Coordinate*> coordinates);
  Coordinate* getCenter();

protected:
  string name;
  list<Coordinate*> coordinates;
};
#endif // GTKMM_APP_DRAWABLE_OBJECT
