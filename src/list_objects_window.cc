#include "list_objects_window.h"

ListObjectsWindow::ListObjectsWindow()
: selected_object(""),
  objects_list(),
  m_grid(),
  button_delete("Delete"),
  button_close("Close")

{
  // objects_list.set_popup_fixed_width(false);
  // for(std::list<string>::iterator it = names.begin(); it != names.end(); it++)
  // {
  //   this->objects_list.append(*it);
  // }

  // set_title("List Objects");
  // set_border_width(12);

  // m_grid.set_column_homogeneous(true);

  // m_grid.attach(x_label, 1, 1, 1, 1);
  // m_grid.attach(x_field, 2, 1, 1, 1);
  // m_grid.attach(y_label, 1, 2, 1, 1);
  // m_grid.attach(y_field, 2, 2, 1, 1);
  // m_grid.attach(info_label, 1, 3, 1, 1);
  // m_grid.attach(button_add_Coordinate, 1, 4, 1, 1);
  // m_grid.attach(button_finish, 2, 4, 1, 1);
  //
  // button_finish.signal_clicked().connect(sigc::mem_fun(*this,
  //   &AddObjectWindow::on_button_finish) );

  // add(m_grid);
  // show_all_children();
}

ListObjectsWindow::~ListObjectsWindow()
{
}

void ListObjectsWindow::on_button_delete()
{

}

void ListObjectsWindow::on_button_close()
{
  hide();
}
