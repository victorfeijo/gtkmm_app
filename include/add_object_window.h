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

class AddObjectWindow : public Gtk::Window
{
public:
  AddObjectWindow();
  ~AddObjectWindow();
protected:
  /* Add here any components or frames
   */
  Gtk::Grid m_grid;
  Gtk::Button button_add_Coordinate, button_finish;
  Gtk::Entry x_field, y_field;
  Gtk::Label x_label, y_label, info_label;

  void on_button_add_Coordinate();
  void on_button_finish();
};
#endif //GTKMM_APP_ADD_OBJECT_WINDOW
