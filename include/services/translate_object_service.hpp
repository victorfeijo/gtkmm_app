#ifndef GTKMM_APP_TRANSLATE_OBJECT_SERVICE
#define GTKMM_APP_TRANSLATE_OBJECT_SERVICE

#include "drawable_object.hpp"

class TranslateObjectService
{
public:
  TranslateObjectService();
  ~TranslateObjectService();
  void translate(DrawableObject *object);
};

#endif
