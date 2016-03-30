#include "list_objects_window.hpp"

ListObjectsWindow::ListObjectsWindow(MainWindow* mainWindow)
    : mainWindow(mainWindow),
      selected_object(""),
      objects_list(),
      m_grid(),
      button_transform("Trasform"),
      button_delete("Delete"),
      button_close("Close")
{

  std::list<std::string> names = this->mainWindow->getViewport()->getViewWindow()
                                 ->getDisplayFile()->getNamesList();
  for(std::list<std::string>::iterator it = names.begin(); it != names.end(); ++it)
  {
    this->objects_list.append(*it);
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
  show_all_children();
}

ListObjectsWindow::~ListObjectsWindow()
{
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
    transform_object_window = new TransformObjectWindow(this->mainWindow, object);
    transform_object_window->show();
    hide();
  }
}

void ListObjectsWindow::on_button_close()
{
  hide();
}
