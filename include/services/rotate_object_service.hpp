#ifndef GTKMM_APP_ROTATE_OBJECT_SERVICE
#define GTKMM_APP_ROTATE_OBJECT_SERVICE

#include <math.h>
#include "drawable_object.hpp"
#include "coordinate.hpp"
#include "matrix.hpp"
#include "translate_object_service.hpp"
#include "transform_type.hpp"

class RotateObjectService
{
public:
  RotateObjectService();
  ~RotateObjectService();
  void rotate(DrawableObject *object, int dx, int dy, int angle, transform_type type = ON_WORLD);
  void rotateCenterObject(DrawableObject *object, int angle);
  void rotateCenterWorld(DrawableObject *object, int angle);

protected:
  TranslateObjectService translate_service;
};

#endif
