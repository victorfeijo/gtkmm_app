#ifndef GTKMM_APP_DRAWABLE_OBJECT
#define GTKMM_APP_DRAWABLE_OBJECT

 /*This class represent's a object such as rect or polygon
 * to be drawed on the view port.
 * Include any library as need to use other's components.
 */
#include <list>
#include <string>
#include "coordenate.h"
using namespace std;

class DrawableObject
{
public:
  DrawableObject(string name, list<Coordenate> coordenates)
  : name(name), coordenates(coordenates) {}
  ~DrawableObject() {}
  std::string getName()
  {
    return name;
  }
  virtual list<Coordenate> getCoordenates() const = 0;
protected:
  string name;
  list<Coordenate> coordenates;
};
#endif // GTKMM_APP_DRAWABLE_OBJECT
