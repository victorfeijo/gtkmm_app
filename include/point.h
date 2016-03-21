#ifndef GTKMM_APP_POINT
#define GTKMM_APP_POINT

#include "drawable_object.h"
#include "coordenate.h"

using namespace std;

class Point : public DrawableObject
{
public:
  Point(string name, Coordenate* point_cord);
  ~Point();
  virtual list<Coordenate*> getCoordenates();
};
#endif // GTKMM_APP_POINT
