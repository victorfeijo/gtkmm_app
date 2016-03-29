#ifndef GTKMM_APP_SCALE_OBJECT_SERVICE
#define GTKMM_APP_SCALE_OBJECT_SERVICE

#include "drawable_object.hpp"

class ScaleObjectService
{
public:
  ScaleObjectService();
  ~ScaleObjectService();
  void scale(DrawableObject *object);
};

#endif
