#ifndef GTKMM_APP_CLIPPING_SERVICE
#define GTKMM_APP_CLIPPING_SERVICE

#include "drawable_object.hpp"
#include "clipping_type.hpp"

#define INSIDE 0  // 0000
#define LEFT   1  // 0001
#define RIGHT  2  // 0010
#define BOTTOM 4  // 0100
#define TOP    8  // 1000

class ViewWindow;

class ClippingService {
public:
  ClippingService();
  ~ClippingService();
  void clip(ViewWindow* window, DrawableObject *object);
  void clipPoint(ViewWindow* window, DrawableObject *object);
  void clipCohenSutherland(ViewWindow* window, DrawableObject *object);
  int calcRegionCode(ViewWindow* window, Coordinate cord);
  bool isCordOnWindow(Coordinate cord, ViewWindow *window);
};

#endif
