#ifndef GTKMM_CHOOSE_FILE_WINDOW_H
#define GTKMM_CHOOSE_FILE_WINDOW_H

#include <gtkmm/buttonbox.h>
#include <gtkmm/filechooserdialog.h>
#include <gtkmm/button.h>
#include <gtkmm/filefilter.h>
#include <string>
#include "main_window.hpp"

class ChooseFileWindow : public Gtk::FileChooserDialog
{
public:
  ChooseFileWindow(MainWindow* mainWindow, Gtk::FileChooserAction file_chooser_action);
  virtual ~ChooseFileWindow();
  std::string get_file_path();

protected:
  MainWindow* mainWindow;
  std::string selected_path;
};

#endif //GTKMM_CHOOSE_FILE_WINDOW_H
