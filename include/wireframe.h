#ifndef GTKMM_APP_WIREFRAME
#define GTKMM_APP_WIREFRAME

#include "drawable_object.h"
#include "coordenate.h"

using namespace std;

class WireFrame : public DrawableObject
{
public:
  WireFrame(string name, list<Coordenate*> coordenates);
  ~WireFrame();
  virtual list<Coordenate*> getCoordenates();
};
#endif // GTKMM_APP_WIREFRAME
