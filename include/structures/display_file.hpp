#ifndef GTKMM_APP_DISPLAY_FILE
#define GTKMM_APP_DISPLAY_FILE

#include <map>
#include <list>
#include <string>
#include "drawable_object.hpp"
#include "line.hpp"

using namespace std;

class DisplayFile
{
public:
  DisplayFile();
  virtual ~DisplayFile();
  void addObject(DrawableObject* object);
  DrawableObject* getObjectByName(string name);
  void removeObjectByName(string name);
  list<string> getNamesList();
  list<DrawableObject*> getObjects();

protected:
  map<string, DrawableObject*> objectsMap;
  void destroyMap();

};

#endif
