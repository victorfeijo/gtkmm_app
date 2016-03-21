#ifndef GTKMM_APP_DISPLAY_FILE
#define GTKMM_APP_DISPLAY_FILE

#include <map>
#include <list>
#include <string>
#include "objects.h"

class DisplayFile
{
public:
  DisplayFile();
  virtual ~DisplayFile();
  void addObject(DrawbleObject object);
  DrawbleObject getObjectByName(string name);
  void removeObject(DrawableObject object);
  void removeObjectByName(string name);
  std::list<string> getNamesList();

protected:
  std::map<string, DrawbleObject> objects;

};

#endif
