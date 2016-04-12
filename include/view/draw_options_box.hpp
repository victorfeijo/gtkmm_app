#ifndef GTKMM_APP_DRAW_OPTIONS_BOX
#define GTKMM_APP_DRAW_OPTIONS_BOX

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
#include "rw_object_service.hpp"

#define DEFAULT_MOVE_LENGTH "10"
#define DEFAULT_ZOOM_SCALE 1.5

class DrawOptionsBox : public Gtk::Frame
{

public:
  DrawOptionsBox(const Glib::ustring& title,
                 gint spacing,
                 Gtk::ButtonBoxStyle layout,
                 MainWindow* mainWindow
               );
  virtual ~DrawOptionsBox();
  void save_object(std::string file_path);

protected:
  MainWindow* mainWindow;
  Gtk::Button button_add_object, button_open_object, button_move_up,
              button_move_down, button_move_left, button_move_right,
              button_zoom_in, button_zoom_out, button_close,
              button_list_objects, button_save_object;
  Gtk::Grid grid_move, grid_zoom;
  AddObjectWindow* add_object_window;
  ChooseFileWindow* choose_file_window;
  ListObjectsWindow* list_objects_window;
  RwObjectService rw_object_service;
  Gtk::Entry entry_move_length, entry_zoom_scale;

  void on_button_add_object();
  void on_button_open_object();
  void on_button_save_object();
  void on_button_list_objects();
  void on_button_move_up();
  void on_button_move_down();
  void on_button_move_left();
  void on_button_move_right();
  void on_button_zoom_in();
  void on_button_zoom_out();
  void on_button_close();
};
#endif // GTKMM_APP_DRAW_OPTIONS_BOX
