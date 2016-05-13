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
  double getXvpmin();
  double getYvpmin();
  double getXvpmax();
  double getYvpmax();
  void setXvpmin(double Xvpmin);
  void setYvpmin(double Yvpmin);
  void setXvpmax(double Xvpmax);
  void setYvpmax(double Yvpmax);
  bool getFill();
  void setFill(bool fill);
  void resetWindow();

protected:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
  ViewWindow* viewWindow;
  double Xvpmin, Yvpmin, Xvpmax, Yvpmax;
  bool fillPolygon;

};

#endif
