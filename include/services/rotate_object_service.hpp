#ifndef GTKMM_APP_ROTATE_OBJECT_SERVICE
#define GTKMM_APP_ROTATE_OBJECT_SERVICE

#include "drawable_object.hpp"

class RotateObjectService
{
public:
  RotateObjectService();
  ~RotateObjectService();
  void rotate(DrawableObject *object);
};

#endif
