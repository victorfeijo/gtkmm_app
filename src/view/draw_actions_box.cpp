#include "draw_actions_box.hpp"

DrawActionsBox::DrawActionsBox(const Glib::ustring& title,
                               gint spacing,
                               Gtk::ButtonBoxStyle layout,
                               MainWindow* mainWindow
                              )
    : Gtk::Frame(title),
      mainWindow(mainWindow),
      button_add_object("Add Object"),
      button_open_object("Open Objects"),
      button_close("Close"),
      button_list_objects("List Objects"),
      button_save_object("Save Objects"),
      button_reset("Reset"),
      button_settings("Settings"),
      add_object_window(nullptr),
      choose_file_window(nullptr),
      list_objects_window(nullptr),
      settings_window(nullptr),
      resetTime(0),
      closeTime(0)
{
  Gtk::ButtonBox* bbox = Gtk::manage( new Gtk::ButtonBox(Gtk::ORIENTATION_VERTICAL) );
  bbox->set_border_width(10);
  add(*bbox);

  bbox->set_layout(layout);
  bbox->set_spacing(5);

  bbox->add(button_add_object);
  bbox->add(button_open_object);
  bbox->add(button_save_object);
  bbox->add(button_list_objects);
  bbox->add(button_reset);
  bbox->add(button_settings);
  bbox->add(button_close);

  button_add_object.signal_clicked().connect(sigc::mem_fun(*this,
    &DrawActionsBox::on_button_add_object));

  button_open_object.signal_clicked().connect(sigc::mem_fun(*this,
    &DrawActionsBox::on_button_open_object));

  button_list_objects.signal_clicked().connect(sigc::mem_fun(*this,
    &DrawActionsBox::on_button_list_objects));

  button_reset.signal_clicked().connect(sigc::mem_fun(*this,
    &DrawActionsBox::on_button_reset));

  button_close.signal_clicked().connect(sigc::mem_fun(*this,
    &DrawActionsBox::on_button_close));

  button_save_object.signal_clicked().connect(sigc::mem_fun(*this,
      &DrawActionsBox::on_button_save_object));

  button_settings.signal_clicked().connect(sigc::mem_fun(*this,
      &DrawActionsBox::on_button_settings));

}

DrawActionsBox::~DrawActionsBox()
{
  delete add_object_window;
  delete list_objects_window;
}

void DrawActionsBox::on_button_add_object()
{
  delete add_object_window;
  add_object_window = new AddObjectWindow(this->mainWindow);
  add_object_window->show();
}

void DrawActionsBox::on_button_settings()
{
  delete settings_window;
  settings_window = new SettingsWindow(this->mainWindow);
  settings_window->show();
}

void DrawActionsBox::on_button_open_object()
{
  delete choose_file_window;
  choose_file_window = new ChooseFileWindow(this->mainWindow, Gtk::FILE_CHOOSER_ACTION_OPEN);
  std::string file_path = choose_file_window->get_file_path();
  if (file_path.length() > 0)
  {
    std::list<DrawableObject*> objects_list = rw_object_service.read(file_path);
    for (DrawableObject* object : objects_list)
    {
      this->mainWindow->getViewport()->getViewWindow()->getDisplayFile()->addObject(object);
    }
    this->mainWindow->getViewport()->queue_draw();
    mainWindow->getLogTextView()->add_log_line("Objects loaded from [" + file_path + "]\n");
  }
  else
  {
    mainWindow->getLogTextView()->add_log_line("No file selected\n");
  }
}

void DrawActionsBox::on_button_list_objects()
{
  delete list_objects_window;
  list_objects_window = new ListObjectsWindow(this->mainWindow);
  list_objects_window->show();
}

void DrawActionsBox::on_button_reset()
{
  unsigned long int timeNow = duration_cast< milliseconds >(
    system_clock::now().time_since_epoch()
  ).count();
  if (resetTime > timeNow - RESET_INTERVAL)
  {
    this->mainWindow->getViewport()->resetWindow();
    this->mainWindow->getViewport()->queue_draw();
    mainWindow->getLogTextView()->add_log_line("Window reseted.\n");
  }
  else
  {
    resetTime = timeNow;
  }
}

void DrawActionsBox::on_button_close()
{
  unsigned long int timeNow = duration_cast< milliseconds >(
    system_clock::now().time_since_epoch()
  ).count();
  if (closeTime > timeNow - RESET_INTERVAL)
  {
    exit(0);
  }
  else
  {
    closeTime = timeNow;
  }
}

void DrawActionsBox::on_button_save_object()
{
  delete choose_file_window;
  choose_file_window = new ChooseFileWindow(this->mainWindow, Gtk::FILE_CHOOSER_ACTION_SAVE);
  choose_file_window->set_do_overwrite_confirmation();
  std::string file_path = choose_file_window->get_file_path();
  if (file_path.length() > 0)
  {
    std::list<DrawableObject*> objects_list = this->mainWindow->getViewport()->
                               getViewWindow()->getDisplayFile()->getObjects();
    rw_object_service.write(objects_list, file_path);
    mainWindow->getLogTextView()->add_log_line("Objects saved to [" + file_path + "]\n");
  }
  else
  {
    mainWindow->getLogTextView()->add_log_line("No file selected\n");
  }
}
