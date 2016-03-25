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
#include "point.hpp"
#include "line.hpp"
#include "wireframe.hpp"
#include "main_window.hpp"
#include "coordinate.hpp"

class AddObjectWindow : public Gtk::Window
{
public:
  AddObjectWindow(MainWindow* mainWindow);
  ~AddObjectWindow();
protected:
  /* Add here any components or frames
   */
  MainWindow* mainWindow;
  std::list<Coordinate*> wire_cord_list;
  Gtk::Grid point_grid, line_grid, wire_grid;
  Gtk::Notebook m_notebook;
  Gtk::Box m_vbox;
  Gtk::Button button_add_coordenate, button_save_line, button_close,
              button_save_wire, button_save_point;
  Gtk::Entry point_name_field, point_x_field, point_y_field;
  Gtk::Entry line_name_field, line_x1_field, line_x2_field, line_y1_field, line_y2_field;
  Gtk::Entry wire_name_field, wire_x_field, wire_y_field;
  Gtk::Label point_x_label, point_y_label;
  Gtk::Label line_x1_label, line_x2_label, line_y1_label, line_y2_label;
  Gtk::Label wire_x_label, wire_y_label, info_label;

  void on_button_add_coordinate();
  void on_button_close();
  void on_button_save_point();
  void on_button_save_line();
  void on_button_save_polygon();
};
#endif //GTKMM_APP_ADD_OBJECT_WINDOW
