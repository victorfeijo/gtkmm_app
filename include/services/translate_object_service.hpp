#ifndef GTKMM_APP_TRANSLATE_OBJECT_SERVICE
#define GTKMM_APP_TRANSLATE_OBJECT_SERVICE

#include <list>
#include "drawable_object.hpp"
#include "matrix.hpp"
#include "transform_type.hpp"

class TranslateObjectService
{
public:
  TranslateObjectService();
  ~TranslateObjectService();
  void translate(DrawableObject *object, int dx, int dy, int dz = 0, transform_type type = ON_WORLD);
};

#endif
