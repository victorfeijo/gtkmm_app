#include "add_object_window.h"

AddObjectWindow::AddObjectWindow()
: button_add_Coordinate("Add a Coordinate"),
  button_finish("Finish"),
  x_label("Coordinate X : "),
  y_label("Coordinate Y : "),
  info_label("Insert a Coordinate"),
  x_field(),
  y_field()
{
  set_title("Add Coordinate");
  set_border_width(12);

  m_grid.set_column_homogeneous(true);

  m_grid.attach(x_label, 1, 1, 1, 1);
  m_grid.attach(x_field, 2, 1, 1, 1);
  m_grid.attach(y_label, 1, 2, 1, 1);
  m_grid.attach(y_field, 2, 2, 1, 1);
  m_grid.attach(info_label, 1, 3, 1, 1);
  m_grid.attach(button_add_Coordinate, 1, 4, 1, 1);
  m_grid.attach(button_finish, 2, 4, 1, 1);

  button_finish.signal_clicked().connect(sigc::mem_fun(*this,
    &AddObjectWindow::on_button_finish) );

  add(m_grid);
  show_all_children();
}

AddObjectWindow::~AddObjectWindow()
{
}

void AddObjectWindow::on_button_add_Coordinate()
{

}

void AddObjectWindow::on_button_finish()
{
  //
  hide();
}
