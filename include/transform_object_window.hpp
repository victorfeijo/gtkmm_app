#ifndef GTKMM_APP_TRANSFORM_OBJECT_WINDOW
#define GTKMM_APP_TRANSFORM_OBJECT_WINDOW

#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm/button.h>
#include <gtkmm/notebook.h>
#include <gtkmm/box.h>
#include <string>
#include "drawable_object.hpp"
#include "main_window.hpp"
#include "coordinate.hpp"

class TransformObjectWindow : public Gtk::Window
{
public:
  TransformObjectWindow(MainWindow* mainWindow, DrawableObject* object);
  ~TransformObjectWindow();
protected:
  /* Add here any components or frames
   */
  MainWindow* mainWindow;
  DrawableObject* object;
  Gtk::Grid translation_grid, scale_grid, rotate_grid;
  Gtk::Notebook m_notebook;
  Gtk::Box m_vbox;
  Gtk::Button button_close;

  void on_button_close();
};

#endif
