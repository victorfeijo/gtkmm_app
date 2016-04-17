#include "list_objects_window.hpp"

ListObjectsWindow::ListObjectsWindow(MainWindow* mainWindow)
    : mainWindow(mainWindow),
      selected_object(""),
      objects_list(),
      m_grid(),
      button_transform("Trasform"),
      button_delete("Delete"),
      button_close("Close"),
      transform_object_window(nullptr)
{

  std::list<std::string> names = this->mainWindow->getViewport()->getViewWindow()
                                 ->getDisplayFile()->getNamesList();
  for(string name : names)
  {
    this->objects_list.append(name);
  }

  set_title("List Objects");
  set_border_width(12);
  set_resizable(false);

  m_grid.set_column_homogeneous(true);

  // objects_list.set_border_width(10);
  m_grid.set_row_spacing(10);
  m_grid.attach(objects_list, 1, 1, 3, 1);
  m_grid.attach(button_transform, 1, 3, 1, 1);
  m_grid.attach(button_delete, 2, 3, 1, 1);
  m_grid.attach(button_close, 3, 3, 1, 1);

  button_transform.signal_clicked().connect(sigc::mem_fun(*this,
      &ListObjectsWindow::on_button_transform) );
  button_close.signal_clicked().connect(sigc::mem_fun(*this,
      &ListObjectsWindow::on_button_close) );
  button_delete.signal_clicked().connect(sigc::mem_fun(*this,
      &ListObjectsWindow::on_button_delete));

  add(m_grid);

  set_type_hint(Gdk::WINDOW_TYPE_HINT_DIALOG);
  set_modal();
  set_transient_for(*mainWindow);

  show_all_children();
}

ListObjectsWindow::~ListObjectsWindow()
{
  delete transform_object_window;
}

void ListObjectsWindow::on_button_delete()
{
  Glib::ustring name = objects_list.get_active_text();
  if(!(name.empty()))
  {
    this->mainWindow->getViewport()->getViewWindow()->getDisplayFile()
        ->removeObjectByName((string) name);
    this->mainWindow->getViewport()->queue_draw();
    this->mainWindow->getLogTextView()->add_log_line(
        "Object named [" + name + "] deleted\n");
    this->hide();
  }
}

void ListObjectsWindow::on_button_transform()
{
  Glib::ustring name = objects_list.get_active_text();
  if(!(name.empty()))
  {
    DrawableObject* object = this->mainWindow->getViewport()->getViewWindow()->
        getDisplayFile()->getObjectByName((string) name);
    delete transform_object_window;
    transform_object_window = new TransformObjectWindow(this->mainWindow, object);
    transform_object_window->show();
    hide();
  }
}

void ListObjectsWindow::on_button_close()
{
  hide();
}

std::list<DrawableObject*> ListObjectsWindow::get_drawable_objects()
{
  std::list<DrawableObject*> drawable_objects;
  std::list<std::string> names = this->mainWindow->getViewport()->getViewWindow()
                                 ->getDisplayFile()->getNamesList();
  while (!(names.empty()))
  {
    DrawableObject* object = this->mainWindow->getViewport()->getViewWindow()->
        getDisplayFile()->getObjectByName(names.front());
    names.pop_front();
    drawable_objects.push_back(object);
  }
  return drawable_objects;
}
