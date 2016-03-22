#ifndef GTKMM_APP_VIEWPORT
#define GTKMM_APP_VIEWPORT

#include <gtkmm/drawingarea.h>
#include <gdkmm/rgba.h>
#include <cairomm/context.h>
#include <list>
#include "view_window.h"
#include "coordinate.h"

class Viewport : public Gtk::DrawingArea
{

public:
  Viewport();
  virtual ~Viewport();
  ViewWindow * getViewWindow();
  // void update(); // CALL FUNCTION queue_draw() INSTEAD

protected:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
  Gtk::Allocation* allocation;
  ViewWindow* viewWindow = NULL;
  int Xvpmin, Yvpmin, Xvpmax, Yvpmax;
  void updateAllocation(Gtk::Allocation allocation);
  Coordinate convertCoordinateFromWindow(Coordinate cord);

};

#endif
