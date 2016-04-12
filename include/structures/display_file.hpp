#ifndef GTKMM_APP_DISPLAY_FILE
#define GTKMM_APP_DISPLAY_FILE

#include <map>
#include <list>
#include <string>
#include "drawable_object.hpp"
#include "line.hpp"

class DisplayFile
{
public:
  DisplayFile();
  virtual ~DisplayFile();
  void addObject(DrawableObject* object);
  DrawableObject* getObjectByName(string name);
  void removeObjectByName(string name);
  std::list<string> getNamesList();
  std::list<DrawableObject*> getObjects();

protected:
  std::map<string, DrawableObject*> objectsMap;
  void destroyMap();

};

#endif
