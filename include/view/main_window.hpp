#ifndef GTKMM_APP_MAIN_WINDOW
#define GTKMM_APP_MAIN_WINDOW

/* Include any library as need to use other's components such as
 * gtkmm/button or gtkmm/frame.
 */
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/frame.h>
#include <gtkmm/viewport.h>
#include <gtkmm/adjustment.h>
#include <gtkmm/scrolledwindow.h>
#include <glibmm/refptr.h>
#include "viewport.hpp"
#include "view_window.hpp"
#include "log_text_view.hpp"


class MainWindow : public Gtk::Window
{

public:
  MainWindow();
  virtual ~MainWindow();
  Viewport* getViewport();
  LogTextView* getLogTextView();

protected:
  /* Add here any components or frames
   */
  Gtk::Box main_box, drawable_box, left_box, down_box;
  Gtk::Frame left_frame, right_frame, down_frame;

  Viewport viewport;
  Gtk::ScrolledWindow scrolled_log;
  LogTextView log_text_view;

};
#endif // GTKMM_APP_MAIN_WINDOW
