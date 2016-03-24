#include "list_objects_window.hpp"

ListObjectsWindow::ListObjectsWindow(MainWindow* mainWindow)
    : mainWindow(mainWindow),
      selected_object(""),
      objects_list(),
      m_grid(),
      button_delete("Delete"),
      button_close("Close")
{

  std::list<std::string> names = this->mainWindow->getViewport()->getViewWindow()
                                 ->getDisplayFile()->getNamesList();
  for(std::list<std::string>::iterator it = names.begin(); it != names.end(); it++)
  {
    this->objects_list.append(*it);
  }

  set_title("List Objects");
  set_border_width(12);

  m_grid.set_column_homogeneous(true);

  m_grid.attach(objects_list, 1, 1, 2, 1);
  m_grid.attach(button_delete, 1, 2, 1, 1);
  m_grid.attach(button_close, 2, 2, 1, 1);
  // m_grid.attach(button_finish, 2, 4, 1, 1);
  //
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
    this->hide();
  }
}

void ListObjectsWindow::on_button_close()
{
  hide();
}
