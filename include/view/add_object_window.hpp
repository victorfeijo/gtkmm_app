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
#include <gtkmm/checkbutton.h>
#include <string>
#include "curve_2d.hpp"
#include "point.hpp"
#include "line.hpp"
#include "wireframe.hpp"
#include "main_window.hpp"
#include "coordinate.hpp"
#include "vector.hpp"
#include "object_3d.hpp"

using namespace std;

class AddObjectWindow : public Gtk::Window
{
public:
  AddObjectWindow(MainWindow* mainWindow);
  ~AddObjectWindow();
protected:
  /* Add here any components or frames
   */
  MainWindow* mainWindow;
  list<Coordinate> wire_cord_list;
  list<Coordinate> spline_cord_list;
  list<Vector> curve_vector_list;
  list<Coordinate> object3d_cord_list;
  Gtk::Grid point_grid, line_grid, wire_grid, curve_grid, spline_grid, object3d_grid;
  Gtk::Notebook m_notebook;
  Gtk::Box m_vbox;
  Gtk::CheckButton check_type_of_vector;
  Gtk::Button button_add_wire_coordinate, button_add_vector, button_save_object3d,
              button_add_spline_coordinate,  button_save_line, button_save_wire,
              button_save_point, button_save_curve, button_save_spline, button_close,
              button_add_line3d;
  Gtk::Entry point_name_field, point_x_field, point_y_field, point_z_field;
  Gtk::Entry line_name_field, line_x1_field, line_x2_field, line_y1_field, line_y2_field,
             line_z1_field, line_z2_field;
  Gtk::Entry wire_name_field, wire_x_field, wire_y_field, wire_z_field;
  Gtk::Entry curve_name_field, curve_x1_field, curve_y1_field, curve_x2_field, curve_y2_field,
             curve_z1_field, curve_z2_field;
  Gtk::Entry spline_name_field, spline_x_field, spline_y_field, spline_z_field;
  Gtk::Entry object3d_name_field, object3d_x1_field, object3d_y1_field, object3d_x2_field,
             object3d_y2_field, object3d_z1_field, object3d_z2_field;
  Gtk::Label point_x_label, point_y_label, point_z_label;
  Gtk::Label line_x1_label, line_x2_label, line_y1_label, line_y2_label,
             line_z1_label, line_z2_label;
  Gtk::Label wire_x_label, wire_y_label, wire_z_label, info_wire_label;
  Gtk::Label curve_x1_label, curve_y1_label, curve_x2_label, curve_y2_label, 
             curve_z1_label, curve_z2_label, info_curve_label;
  Gtk::Label spline_x_label, spline_y_label, spline_z_label, info_spline_label;
  Gtk::Label object3d_x1_label, object3d_y1_label, object3d_x2_label, object3d_y2_label, 
             object3d_z1_label, object3d_z2_label, info_object3d_label;

  void on_button_add_wire_coordinate();
  void on_button_add_vector();
  void on_button_add_line3d();
  void on_button_add_spline_coordinate();
  void on_button_close();
  void on_button_save_point();
  void on_button_save_line();
  void on_button_save_polygon();
  void on_button_save_curve();
  void on_button_save_spline();
  void on_button_save_object3d();
};
#endif //GTKMM_APP_ADD_OBJECT_WINDOW
