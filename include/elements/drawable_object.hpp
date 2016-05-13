#ifndef GTKMM_APP_DRAWABLE_OBJECT
#define GTKMM_APP_DRAWABLE_OBJECT

 /*This class represent's a object such as line or polygon
 * to be drawed on the view port.
 * Include any library as need to use other's components.
 */
#include <list>
#include <string>
#include "coordinate.hpp"
#include "object_type.hpp"
using namespace std;

class DrawableObject
{
public:
  DrawableObject(string name);
  DrawableObject(string name, list<Coordinate> coordinates);
  ~DrawableObject();
  string getName();
  list<Coordinate> getCoordinatesWorld();
  list<Coordinate> getCoordinatesWindow();
  list<Coordinate> getCoordinatesClipped();
  virtual string getTypeName() = 0;
  virtual object_type getType() = 0;
  void setCoordinatesWorld(list<Coordinate> coordinates);
  void setCoordinatesWindow(list<Coordinate> coordinates);
  void setCoordinatesClipped(list<Coordinate> coordinates);
  Coordinate getCenterOnWorld();
  bool isInFrontOfWindow(double viewportZ);
  virtual void resetWindowCoordinates() = 0;

protected:
  string name;
  list<Coordinate> coordinatesWorld;
  list<Coordinate> coordinatesWindow;
  list<Coordinate> coordinatesClipped;
  void destroyList(list<Coordinate> coordinates);
};
#endif // GTKMM_APP_DRAWABLE_OBJECT
