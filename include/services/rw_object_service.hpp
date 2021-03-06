#ifndef GTKMM_APP_RW_OBJECT_SERVICE
#define GTKMM_APP_RW_OBJECT_SERVICE

#include <list>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>
#include <locale>
#include "drawable_object.hpp"
#include "point.hpp"
#include "line.hpp"
#include "wireframe.hpp"
#include "curve_2d.hpp"
#include "object_3d.hpp"

using namespace std;

class RwObjectService
{
public:
  RwObjectService();
  ~RwObjectService();
  list<DrawableObject*> read(string file_path);
  void write(list<DrawableObject*> objects_list, string file_path);

protected:
  DrawableObject* addGroup(list<Coordinate> cord_list, string name);
};

#endif
