#ifndef GTKMM_APP_ROTATE_OBJECT_SERVICE
#define GTKMM_APP_ROTATE_OBJECT_SERVICE

#include "drawable_object.hpp"
#include "coordinate.hpp"
#include "matrix.hpp"
#include "translate_object_service.hpp"
#include <math.h>

class RotateObjectService
{
public:
  RotateObjectService();
  ~RotateObjectService();
  void rotate(DrawableObject *object, int dx, int dy, int angle);
  void rotateCenterObject(DrawableObject *object, int angle);
  void rotateCenterWorld(DrawableObject *object, int angle);

protected:
  const double pi = 3.1415926535897;
  TranslateObjectService translate_service;
};

#endif
