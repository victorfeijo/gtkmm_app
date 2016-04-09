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
  DrawableObject(string name, list<Coordinate> coordinates);
  ~DrawableObject();
  std::string getName();
  list<Coordinate> getCoordinatesWorld();
  list<Coordinate> getCoordinatesWindow();
  virtual string getType() = 0;
  void setCoordinatesWorld(list<Coordinate> coordinates);
  void setCoordinatesWindow(list<Coordinate> coordinates);
  Coordinate getCenterOnWorld();
  void copyFromWorldToWindow();

protected:
  string name;
  list<Coordinate> coordinatesWorld;
  list<Coordinate> coordinatesWindow;
  void destroyList(list<Coordinate> coordinates);
};
#endif // GTKMM_APP_DRAWABLE_OBJECT
