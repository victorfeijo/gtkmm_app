#ifndef GTKMM_APP_VIEWPORT
#define GTKMM_APP_VIEWPORT

#include <gtkmm/drawingarea.h>
#include <gdkmm/rgba.h>
#include <cairomm/context.h>
#include "world.h"

class Viewport : public Gtk::DrawingArea
{

public:
  Viewport();
  virtual ~Viewport();

protected:
  int XWmin, YWmin, XWmax, YWmax;
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

};

#endif
