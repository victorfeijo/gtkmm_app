#ifndef GTKMM_APP_SIMPLE_WINDOW
#define GTKMM_APP_SIMPLE_WINDOW

/* Include any library as need to use other's components such as
 * gtkmm/button or gtkmm/frame.
 */
#include <gtkmm/window.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/grid.h>
#include <gtkmm/button.h>
#include <string>
#include "draw_options_box.hpp"

class SimpleWindow : public Gtk::Window
{
public:
  SimpleWindow(std::string label_text, std::string window_title);
  ~SimpleWindow();
  std::string get_text();
protected:
  std::string selected_path;
  std::string window_title;
  Gtk::Grid grid;
  Gtk::Label label;
  Gtk::Entry text_entry;
  Gtk::Button ok_button, cancel_button;
};
#endif //GTKMM_APP_SIMPLE_WINDOW
