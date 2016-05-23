#ifndef GTKMM_APP_DRAW_ACTIONS_BOX
#define GTKMM_APP_DRAW_ACTIONS_BOX

/* Include any library as need to use other's components such as
 * gtkmm/button or gtkmm/frame.
 */
#include <gtkmm/frame.h>
#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/grid.h>
#include <string>
#include <chrono>
#include "main_window.hpp"
#include "view_window.hpp"
#include "add_object_window.hpp"
#include "choose_file_window.hpp"
#include "list_objects_window.hpp"
#include "settings_window.hpp"
#include "rw_object_service.hpp"

#define RESET_INTERVAL 500

using namespace std::chrono;

class DrawActionsBox : public Gtk::Frame
{

public:
  DrawActionsBox(const Glib::ustring& title,
                 gint spacing,
                 Gtk::ButtonBoxStyle layout,
                 MainWindow* mainWindow
               );
  virtual ~DrawActionsBox();
  void save_object(std::string file_path);
  void on_button_close();

protected:
  MainWindow* mainWindow;
  Gtk::Button button_add_object, button_open_object, button_close,
              button_list_objects, button_save_object, button_reset,
              button_settings;

  AddObjectWindow* add_object_window;
  ChooseFileWindow* choose_file_window;
  ListObjectsWindow* list_objects_window;
  SettingsWindow* settings_window;
  RwObjectService rw_object_service;
  unsigned long int resetTime;
  unsigned long int closeTime;

  void on_button_add_object();
  void on_button_open_object();
  void on_button_save_object();
  void on_button_settings();
  void on_button_list_objects();
  void on_button_reset();
};
#endif // GTKMM_APP_DRAW_ACTIONS_BOX
