/* To compile
 * g++ main_window.cc draw_options_box.cc main.cc -o app.o $(pkg-config gtkmm-3.0 --cflags --libs) -std=c++11
 */

#include "main_window.h"
#include <gtkmm/application.h>

int main (int argc, char *argv[])
{
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv);

  MainWindow mainwindow;

  //Shows the window and returns when it is closed.
  return app->run(mainwindow);
}
