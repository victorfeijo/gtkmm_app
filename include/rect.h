#ifndef GTKMM_APP_RECT
#define GTKMM_APP_RECT

#include "drawable_object.h"
#include "coordenate.h"

using namespace std;

class Rect : public DrawableObject
{
public:
  Rect(string name, Coordenate* rect_cord1, Coordenate* rect_cord2);
  ~Rect();
  virtual list<Coordenate*> getCoordenates();
};
#endif // GTKMM_APP_RECT
