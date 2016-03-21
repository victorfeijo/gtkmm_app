#ifndef GTKMM_APP_POINT
#define GTKMM_APP_POINT

#include "drawable_object.h"
#include "coordenate.h"

using namespace std;

class Point : public DrawableObject
{
public:
  Point(list<Coordenate> view_cords, string name);
  ~Point();
  list<Coordenate> getCoordenates();
};
#endif // GTKMM_APP_POINT
