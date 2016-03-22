#ifndef GTKMM_APP_ADD_OBJECT_WINDOW
#define GTKMM_APP_ADD_OBJECT_WINDOW

#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm/button.h>
#include <gtkmm/comboboxtext.h>
#include <string>

class AddObjectWindow : public Gtk::Window
{
public:
  AddObjectWindow();
  ~AddObjectWindow();
protected:
  std::string selected_object;
  Gtk::ComboBoxText objects_list;
  Gtk::Grid m_grid;
  Gtk::Button delete_object, close;
  Gtk::Entry x_field, y_field;
  Gtk::Label x_label, y_label, info_label;

  void on_button_delete();
  void on_button_close();
};
#endif //GTKMM_APP_ADD_OBJECT_WINDOW
