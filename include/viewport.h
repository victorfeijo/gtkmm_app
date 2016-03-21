#ifndef GTKMM_APP_VIEWPORT
#define GTKMM_APP_VIEWPORT

#include <gtkmm/drawingarea.h>
#include <gdkmm/rgba.h>
#include <cairomm/context.h>
#include "view_window.h"

class Viewport : public Gtk::DrawingArea
{

public:
  Viewport();
  virtual ~Viewport();
  int* convertCordinate(int* cord);
  ViewWindow * getViewWindow();
  // void update();

protected:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
  // const Cairo::RefPtr<Cairo::Context> * cr;
  ViewWindow * viewWindow;
  int Xvpmin, Yvpmin, Xvpmax, Yvpmax;

};

#endif
