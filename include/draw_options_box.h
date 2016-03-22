#ifndef GTKMM_APP_DRAW_OPTIONS_BOX
#define GTKMM_APP_DRAW_OPTIONS_BOX

/* Include any library as need to use other's components such as
 * gtkmm/button or gtkmm/frame.
 */
#include <gtkmm/frame.h>
#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/grid.h>
#include "main_window.h"
#include "view_window.h"
#include "add_object_window.h"
#include "list_objects_window.h"

class DrawOptionsBox : public Gtk::Frame
{

public:
  DrawOptionsBox(const Glib::ustring& title,
                 gint spacing,
                 Gtk::ButtonBoxStyle layout,
                 MainWindow* mainWindow
                );
  virtual ~DrawOptionsBox();

protected:
  MainWindow* mainWindow;
  Gtk::Button button_add_object, button_move_up, button_move_down,
              button_move_left, button_move_right, button_zoom_in,
              button_zoom_out, button_close, button_list_objects;
  Gtk::Grid grid_move;
  AddObjectWindow* add_object_window;
  ListObjectsWindow* list_objects_window;
  void on_button_add_object();
  void on_button_list_objects();
  void on_button_move_up();
  void on_button_move_down();
  void on_button_move_left();
  void on_button_move_right();
  void on_button_zoom_in();
  void on_button_zoom_out();
};
#endif // GTKMM_APP_DRAW_OPTIONS_BOX
