#ifndef GTKMM_APP_CLIPPING_SERVICE
#define GTKMM_APP_CLIPPING_SERVICE

#include <tuple>
#include <cmath>
#include "drawable_object.hpp"
#include "clipping_type.hpp"

#define INSIDE 0  // 0000
#define LEFT   1  // 0001
#define RIGHT  2  // 0010
#define BOTTOM 4  // 0100
#define TOP    8  // 1000

using namespace std;

class ViewWindow;

class ClippingService {
public:
  ClippingService();
  ~ClippingService();
  void clip(ViewWindow* window, DrawableObject *object);
  void clipPoint(ViewWindow* window, DrawableObject *object);
  void clipCohenSutherland(ViewWindow* window, DrawableObject *object);
  void clipLiangBarsky(ViewWindow* window, DrawableObject *object);
  void clipSutherlandHodgman(ViewWindow* window, DrawableObject *object);
  int calcRegionCode(ViewWindow* window, Coordinate cord);
  Coordinate calcIntersection(Coordinate cord1, Coordinate cord2, ViewWindow *window, int regionCode);
  Coordinate alignToEdge(Coordinate cord, ViewWindow *window, int regionCode);
};

#endif
