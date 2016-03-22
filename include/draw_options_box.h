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
  void on_button_move_up();
  MainWindow* mainWindow;
  Gtk::Button button_add_object, button_move_up, button_move_down,
              button_move_left, button_move_right, button_zoom_in,
              button_zoom_out, button_close;
  Gtk::Grid grid_move;
  AddObjectWindow* add_object_window;
  void on_button_add_object();
};
#endif // GTKMM_APP_DRAW_OPTIONS_BOX
