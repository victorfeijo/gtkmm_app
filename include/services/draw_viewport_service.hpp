#ifndef GTKMM_APP_DRAW_VIEWPORT_SERVICE
#define GTKMM_APP_DRAW_VIEWPORT_SERVICE

#define BORDER 10
#define DEFAULT_ZOOM 2
#define RED 0.8, 0, 0
#define BLACK 0, 0, 0
#define WHITE 1, 1, 1
#define COP_Z -1250

#include <cairomm/context.h>
#include <gtkmm/drawingarea.h>
#include "coordinate.hpp"
#include "rotate_object_service.hpp"
#include "clipping_service.hpp"

using namespace std;

class Viewport;

class DrawViewportService
{
public:
  DrawViewportService();
  ~DrawViewportService();
  void draw(const Cairo::RefPtr<Cairo::Context>& cr, Viewport* viewport);
private:
  Coordinate convertFromWindowToViewport(Coordinate cord, Viewport* viewport);
  void updateViewportAllocation(Gtk::Allocation newAllocation, Viewport* viewport);
  void applyPerspective(DrawableObject* object, Coordinate windowCenter);
  RotateObjectService rotate_service;
  ClippingService clipping_service;
};

#endif
