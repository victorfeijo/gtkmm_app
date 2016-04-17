#include "choose_file_window.hpp"

ChooseFileWindow::ChooseFileWindow(MainWindow* mainWindow, Gtk::FileChooserAction file_chooser_action)
: Gtk::FileChooserDialog("Choose a wavefront file", file_chooser_action),
  mainWindow(mainWindow),
  selected_path("No file selected")
{

  add_button("_Cancel", Gtk::RESPONSE_CANCEL);
  add_button("Select", Gtk::RESPONSE_OK);

  set_transient_for(*mainWindow);

  auto filter_obj = Gtk::FileFilter::create();
  filter_obj->set_name("Wavefront .obj files");
  filter_obj->add_pattern("*.obj");
  filter_obj->add_pattern("*.OBJ");
  add_filter(filter_obj);

  int result = run();

  switch(result)
  {
    case(Gtk::RESPONSE_OK):
    {
      this->selected_path = get_filename();
      mainWindow->getLogTextView()->add_log_line(
        "The file : [ " + this->selected_path + " ] was selected.\n"
      );
      close();
      break;
    }
    case(Gtk::RESPONSE_CANCEL):
    {
      mainWindow->getLogTextView()->add_log_line("Canceled the file select.\n");
      close();
      break;
    }
    default:
    {
      mainWindow->getLogTextView()->add_log_line("Unexpected button clicked.\n");
      break;
    }
  }
}

ChooseFileWindow::~ChooseFileWindow()
{
}

std::string ChooseFileWindow::get_file_path()
{
  return this->selected_path;
}
