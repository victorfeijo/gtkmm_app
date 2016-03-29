#ifndef GTKMM_APP_TRANSFORM_OBJECT_WINDOW
#define GTKMM_APP_TRANSFORM_OBJECT_WINDOW

#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm/button.h>
#include <gtkmm/notebook.h>
#include <gtkmm/box.h>
#include <gtkmm/entry.h>
#include <string>
#include "drawable_object.hpp"
#include "main_window.hpp"
#include "coordinate.hpp"
#include "translate_object_service.hpp"
#include "scale_object_service.hpp"

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
  TranslateObjectService* translate_service;
  ScaleObjectService* scale_service;
  Gtk::Grid translation_grid, scale_grid, rotate_grid;
  Gtk::Label label_translation_x, label_translation_y;
  Gtk::Entry translation_x_field, translation_y_field;
  Gtk::Label label_scale_sx, label_scale_sy;
  Gtk::Entry scale_sx_field, scale_sy_field;
  Gtk::Notebook m_notebook;
  Gtk::Box m_vbox;
  Gtk::Button button_close, button_add_translation, button_add_scale;

  void on_button_close();
  void on_button_translate();
  void on_button_scale();
};

#endif
