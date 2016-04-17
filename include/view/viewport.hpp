#ifndef GTKMM_APP_VIEWPORT
#define GTKMM_APP_VIEWPORT

#include <gtkmm/drawingarea.h>
#include <gdkmm/rgba.h>
#include <cairomm/context.h>
#include <list>
#include "view_window.hpp"
#include "coordinate.hpp"
#include "draw_viewport_service.hpp"
#include "clipping_type.hpp"

class Viewport : public Gtk::DrawingArea
{

public:
  Viewport();
  virtual ~Viewport();
  ViewWindow * getViewWindow();
  int getXvpmin();
  int getYvpmin();
  int getXvpmax();
  int getYvpmax();
  void setXvpmin(int Xvpmin);
  void setYvpmin(int Yvpmin);
  void setXvpmax(int Xvpmax);
  void setYvpmax(int Yvpmax);

protected:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
  ViewWindow* viewWindow;
  int Xvpmin, Yvpmin, Xvpmax, Yvpmax;

};

#endif
