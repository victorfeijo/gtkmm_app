#ifndef GTKMM_APP_RW_OBJECT_SERVICE
#define GTKMM_APP_RW_OBJECT_SERVICE

#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "drawable_object.hpp"
#include "point.hpp"
#include "line.hpp"
#include "wireframe.hpp"

using namespace std;

class RwObjectService
{
public:
  RwObjectService();
  ~RwObjectService();
  list<DrawableObject*> read(string file_path);
  void write(list<DrawableObject*> objects_list, string file_path);
protected:
  vector<string> split(string str, char delimiter);
};

#endif
