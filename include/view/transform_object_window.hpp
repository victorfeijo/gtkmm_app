#ifndef GTKMM_APP_TRANSFORM_OBJECT_WINDOW
#define GTKMM_APP_TRANSFORM_OBJECT_WINDOW

#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm/button.h>
#include <gtkmm/notebook.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/box.h>
#include <gtkmm/entry.h>
#include <string>
#include "drawable_object.hpp"
#include "main_window.hpp"
#include "coordinate.hpp"
#include "translate_object_service.hpp"
#include "scale_object_service.hpp"
#include "rotate_object_service.hpp"
#include "vector.hpp"

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
  TranslateObjectService translate_service;
  ScaleObjectService scale_service;
  RotateObjectService rotate_service;
  Gtk::Grid translation_grid, scale_grid, rotate_grid;
  Gtk::Label label_translation_x, label_translation_y, label_translation_z,
             label_scale_sx, label_scale_sy, label_scale_sz, label_rotate_axis,
             label_rotate_x, label_rotate_y, label_rotate_z, label_rotate_degree,
             label_rotate_point, label_rotate_axis_x1, label_rotate_axis_y1,
             label_rotate_axis_z1, label_rotate_axis_x2, label_rotate_axis_y2,
             label_rotate_axis_z2;
  Gtk::Entry translation_x_field, translation_y_field, translation_z_field,
             scale_sx_field, scale_sy_field, scale_sz_field,
             rotate_x_field, rotate_y_field, rotate_z_field, rotate_degree_field,
             rotate_axis_x1_field, rotate_axis_y1_field, rotate_axis_z1_field,
             rotate_axis_x2_field, rotate_axis_y2_field, rotate_axis_z2_field;
  Gtk::Notebook m_notebook;
  Gtk::Box m_vbox;
  Gtk::ComboBoxText rotate_axis, rotate_point;
  Gtk::Button button_close, button_add_translation, button_add_scale,
              button_add_rotate;

  void on_button_close();
  void on_button_translate();
  void on_button_scale();
  void on_button_rotate();
  void on_rotate_axis_changed();
  void on_rotate_point_changed();
};

#endif
