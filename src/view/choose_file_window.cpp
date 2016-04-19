#include "choose_file_window.hpp"

ChooseFileWindow::ChooseFileWindow(MainWindow* mainWindow, Gtk::FileChooserAction file_chooser_action)
    : Gtk::FileChooserDialog("Select a wavefront file", file_chooser_action),
      mainWindow(mainWindow),
      selected_path("")
{

  add_button("_Cancel", Gtk::RESPONSE_CANCEL);
  add_button("Select", Gtk::RESPONSE_OK);

  set_type_hint(Gdk::WINDOW_TYPE_HINT_DIALOG);
  set_modal();
  set_transient_for(*mainWindow);

  auto filter_obj = Gtk::FileFilter::create();
  filter_obj->set_name("Wavefront .obj files");
  filter_obj->add_pattern("*.obj");
  filter_obj->add_pattern("*.OBJ");
  add_filter(filter_obj);
}

ChooseFileWindow::~ChooseFileWindow()
{
}

std::string ChooseFileWindow::get_file_path()
{
  if (get_action() == Gtk::FILE_CHOOSER_ACTION_SAVE)
  {
    set_create_folders();
    signal_selection_changed().connect(sigc::mem_fun(
        *this, &ChooseFileWindow::on_change_filename));
  }
  int result = run();
  switch(result)
  {
    case(Gtk::RESPONSE_OK):
    {
      hide();
      return this->get_filename();
    }
    default:
    {
      hide();
      return "";
    }
  }
}

void ChooseFileWindow::on_change_filename()
{
  string filename = (string) get_current_name();
  if (!(ends_with(filename, ".obj") || ends_with(filename, ".OBJ")))
  {
    set_current_name(filename + ".obj");
  }
}

bool ChooseFileWindow::ends_with(std::string str, std::string end)
{
    return (str.length() >= end.length() &&
           str.substr(str.length() - end.length()).compare(end) == 0);
}
