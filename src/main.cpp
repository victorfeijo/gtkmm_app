#include "main_window.hpp"
#include <gtkmm/application.h>
#include <list>
#include <string>

int main (int argc, char *argv[])
{
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv);

  MainWindow mainwindow;

  //Shows the window and returns when it is closed.
  return app->run(mainwindow);
}
