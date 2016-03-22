#ifndef GTKMM_APP_ADD_OBJECT_WINDOW
#define GTKMM_APP_ADD_OBJECT_WINDOW

/* Include any library as need to use other's components such as
 * gtkmm/button or gtkmm/frame.
 */
#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/notebook.h>
#include <gtkmm/box.h>
#include <string>
#include <iostream>
#include "point.h"
#include "rect.h"
#include "wireframe.h"
#include "main_window.h"
#include "coordinate.h"

class AddObjectWindow : public Gtk::Window
{
public:
  AddObjectWindow(MainWindow* mainWindow);
  ~AddObjectWindow();
protected:
  /* Add here any components or frames
   */
  MainWindow* mainWindow;
  Gtk::Grid point_grid, rect_grid, wire_grid;
  Gtk::Notebook m_notebook;
  Gtk::Box m_vbox;
  Gtk::Button button_add_coordenate, button_save_rect, button_close,
              button_save_wire, button_save_point;
  Gtk::Entry point_name_field, point_x_field, point_y_field;
  Gtk::Entry rect_name_field, rect_x1_field, rect_x2_field, rect_y1_field, rect_y2_field;
  Gtk::Entry wire_name_field, wire_x_field, wire_y_field;
  Gtk::Label point_x_label, point_y_label;
  Gtk::Label rect_x1_label, rect_x2_label, rect_y1_label, rect_y2_label;
  Gtk::Label wire_x_label, wire_y_label, info_label;

  void on_button_add_Coordinate();
  void on_button_close();
  void on_button_save_point();
  void on_button_save_rect();
  void on_button_save_polygon();
};
#endif //GTKMM_APP_ADD_OBJECT_WINDOW
