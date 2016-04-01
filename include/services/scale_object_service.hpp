#ifndef GTKMM_APP_SCALE_OBJECT_SERVICE
#define GTKMM_APP_SCALE_OBJECT_SERVICE

#include "drawable_object.hpp"
#include <string>
#include <list>
#include <iostream>
#include "matrix.hpp"
#include "translate_object_service.hpp"

class ScaleObjectService
{
public:
  ScaleObjectService();
  ~ScaleObjectService();
  void scale(DrawableObject *object, int sx, int sy);
protected:
  TranslateObjectService translate_service;
};

#endif
