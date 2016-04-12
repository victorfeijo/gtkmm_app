#ifndef GTKMM_APP_DRAW_VIEWPORT_SERVICE
#define GTKMM_APP_DRAW_VIEWPORT_SERVICE

#include <cairomm/context.h>
#include <gtkmm/drawingarea.h>
#include "coordinate.hpp"
#include "rotate_object_service.hpp"

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
  RotateObjectService rotate_service;
};

#endif
