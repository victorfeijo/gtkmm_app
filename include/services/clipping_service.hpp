#ifndef GTKMM_APP_CLIPPING_SERVICE
#define GTKMM_APP_CLIPPING_SERVICE

#include "drawable_object.hpp"
#include "clipping_type.hpp"

class ViewWindow;

class ClippingService {
public:
  ClippingService();
  ~ClippingService();
  void clip(ViewWindow* window, DrawableObject *object);
  void clipPoint(ViewWindow* window, DrawableObject *object);
  bool isCordOnWindow(Coordinate cord, ViewWindow *window);
};

#endif
