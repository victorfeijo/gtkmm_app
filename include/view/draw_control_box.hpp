#ifndef GTKMM_APP_DRAW_CONTROL_BOX
#define GTKMM_APP_DRAW_CONTROL_BOX

/* Include any library as need to use other's components such as
 * gtkmm/button or gtkmm/frame.
 */
#include <gtkmm/frame.h>
#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/grid.h>
#include <string>
#include "main_window.hpp"
#include "view_window.hpp"
#include "add_object_window.hpp"
#include "choose_file_window.hpp"
#include "list_objects_window.hpp"
#include "settings_window.hpp"
#include "rw_object_service.hpp"

#define DEFAULT_MOVE_LENGTH "10"
#define DEFAULT_ZOOM_SCALE 1.5

class DrawControlBox : public Gtk::Frame
{

public:
  DrawControlBox(const Glib::ustring& title,
                 gint spacing,
                 Gtk::ButtonBoxStyle layout,
                 MainWindow* mainWindow
               );
  virtual ~DrawControlBox();
  void save_object(std::string file_path);

protected:
  MainWindow* mainWindow;
  Gtk::Button button_move_up, button_move_down, button_move_left,
              button_move_right, button_move_in, button_move_out,
              button_zoom_in, button_zoom_out, button_rotate_x1,
              button_rotate_x2, button_rotate_y1, button_rotate_y2,
              button_rotate_z1, button_rotate_z2;
  Gtk::Grid grid_move, grid_zoom, grid_rotation;
  Gtk::Entry entry_move_length, entry_zoom_scale, entry_rotation_angle;

  void on_button_move_up();
  void on_button_move_down();
  void on_button_move_left();
  void on_button_move_right();
  void on_button_move_in();
  void on_button_move_out();
  void on_button_zoom_in();
  void on_button_zoom_out();
  void on_button_rotate_x1();
  void on_button_rotate_x2();
  void on_button_rotate_y1();
  void on_button_rotate_y2();
  void on_button_rotate_z1();
  void on_button_rotate_z2();
  int getAngle();
};
#endif // GTKMM_APP_DRAW_CONTROL_BOX
