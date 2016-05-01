#ifndef GTKMM_APP_SETTINGS_WINDOW
#define GTKMM_APP_SETTINGS_WINDOW

#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm/button.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/notebook.h>
#include <string>
#include <list>
#include "main_window.hpp"
#include "clipping_type.hpp"

class SettingsWindow : public Gtk::Window
{
public:
  SettingsWindow(MainWindow* mainWindow);
  ~SettingsWindow();
protected:
  MainWindow* mainWindow;
  Gtk::Notebook m_notebook;
  Gtk::ComboBoxText clipping_options, curve_options;
  Gtk::Button button_close;
  Gtk::Box settings_vbox;

  void on_button_close();
  void on_clipping_changed();
  void on_curve_changed();

};
#endif
