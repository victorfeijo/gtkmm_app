#ifndef GTKMM_APP_LIST_OBJECTS_WINDOW
#define GTKMM_APP_LIST_OBJECTS_WINDOW

#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm/button.h>
#include <gtkmm/comboboxtext.h>
#include <string>
#include <list>
#include "main_window.hpp"

class ListObjectsWindow : public Gtk::Window
{
public:
  ListObjectsWindow(MainWindow* mainWindow);
  ~ListObjectsWindow();
protected:
  MainWindow* mainWindow;
  std::string selected_object;
  Gtk::ComboBoxText objects_list;
  Gtk::Grid m_grid;
  Gtk::Button button_delete, button_close;

  void on_button_delete();
  void on_list_select();
  void on_button_close();
};
#endif //GTKMM_APP_ADD_OBJECT_WINDOW
