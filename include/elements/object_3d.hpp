#ifndef GTKMM_APP_3D_OBJECT
#define GTKMM_APP_3D_OBJECT

#include "drawable_object.hpp"
#include "coordinate.hpp"

using namespace std;

class Object3D : public DrawableObject
{
public:
  Object3D(string name, list<Coordinate> coordinates);
  ~Object3D();
  virtual string getTypeName();
  virtual object_type getType();
  virtual void resetWindowCoordinates();
};
#endif // GTKMM_APP_3D_OBJECT
