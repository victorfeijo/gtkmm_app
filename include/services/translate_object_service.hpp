#ifndef GTKMM_APP_TRANSLATE_OBJECT_SERVICE
#define GTKMM_APP_TRANSLATE_OBJECT_SERVICE

#include "drawable_object.hpp"
#include "matrix.hpp"
#include <list>

class TranslateObjectService
{
public:
  TranslateObjectService();
  ~TranslateObjectService();
  void translate(DrawableObject *object, int dx, int dy);
};

#endif
