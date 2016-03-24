#include "add_object_window.hpp"

AddObjectWindow::AddObjectWindow(MainWindow* mainWindow)
: mainWindow(mainWindow),
  m_vbox(Gtk::ORIENTATION_VERTICAL),
  button_add_coordenate("Add Coordenate"),
  button_save_point("Save Point"),
  button_save_rect("Save Rect"),
  button_save_wire("Save Polygon"),
  button_close("Close"),
  point_x_label("Coordinate X : "),
  point_y_label("Coordinate Y : "),
  rect_x1_label("Coordinate X1 : "),
  rect_y1_label("Coordinate Y1 : "),
  rect_x2_label("Coordinate X2 : "),
  rect_y2_label("Coordinate Y2 : "),
  wire_x_label("Coordinate X : "),
  wire_y_label("Coordinate Y : "),
  info_label("Insert a Coordinate :"),
  point_name_field(), point_x_field(), point_y_field(),
  rect_name_field(), rect_x1_field(), rect_x2_field(),
  wire_name_field(), rect_y1_field(), rect_y2_field(),
  wire_x_field(), wire_y_field()
{
  set_title("Add Object");
  set_border_width(12);

  add(m_vbox);

  m_notebook.set_border_width(10);
  m_vbox.pack_start(m_notebook);
  m_vbox.pack_start(button_close, Gtk::PACK_SHRINK);

  //Add point grid
  point_grid.set_column_homogeneous(true);
  point_grid.set_row_spacing(10);
  point_name_field.set_text("Name");
  point_grid.attach(point_name_field, 1, 1, 2, 1);
  point_grid.attach(point_x_label, 1, 2, 1, 1);
  point_grid.attach(point_x_field, 2, 2, 1, 1);
  point_grid.attach(point_y_label, 1, 3, 1, 1);
  point_grid.attach(point_y_field, 2, 3, 1, 1);
  point_grid.attach(button_save_point, 1, 4, 2, 1);

  //Add rect grid
  rect_grid.set_column_homogeneous(true);
  rect_grid.set_row_spacing(10);
  rect_name_field.set_text("Name");
  rect_grid.attach(rect_name_field, 1, 1, 4, 1);
  rect_grid.attach(rect_x1_label, 1, 2, 1, 1);
  rect_grid.attach(rect_x1_field, 2, 2, 1, 1);
  rect_grid.attach(rect_x2_label, 3, 2, 1, 1);
  rect_grid.attach(rect_x2_field, 4, 2, 1, 1);
  rect_grid.attach(rect_y1_label, 1, 3, 1, 1);
  rect_grid.attach(rect_y1_field, 2, 3, 1, 1);
  rect_grid.attach(rect_y2_label, 3, 3, 1, 1);
  rect_grid.attach(rect_y2_field, 4, 3, 1, 1);
  rect_grid.attach(button_save_rect, 1, 4, 4, 1);

  //Add polygon grid
  wire_grid.set_column_homogeneous(true);
  wire_grid.set_row_spacing(10);
  wire_name_field.set_text("Name");
  wire_grid.attach(wire_name_field, 1, 1, 1, 1);
  wire_grid.attach(info_label, 2, 1, 1, 1);
  wire_grid.attach(wire_x_label, 1, 2, 1, 1);
  wire_grid.attach(wire_x_field, 2, 2, 1, 1);
  wire_grid.attach(wire_y_label, 1, 3, 1, 1);
  wire_grid.attach(wire_y_field, 2, 3, 1, 1);
  wire_grid.attach(button_add_coordenate, 1, 4, 1, 1);
  wire_grid.attach(button_save_wire, 2, 4, 1, 1);

  button_close.signal_clicked().connect(sigc::mem_fun(*this,
    &AddObjectWindow::on_button_close) );

  button_save_point.signal_clicked().connect(sigc::mem_fun(*this,
    &AddObjectWindow::on_button_save_point) );

  button_save_rect.signal_clicked().connect(sigc::mem_fun(*this,
    &AddObjectWindow::on_button_save_rect) );

  button_add_coordenate.signal_clicked().connect(sigc::mem_fun(*this,
    &AddObjectWindow::on_button_add_coordinate) );

  button_save_wire.signal_clicked().connect(sigc::mem_fun(*this,
    &AddObjectWindow::on_button_save_polygon) );

  m_notebook.append_page(point_grid, "Point");
  m_notebook.append_page(rect_grid, "Rect");
  m_notebook.append_page(wire_grid, "Polygon");

  show_all_children();
}

AddObjectWindow::~AddObjectWindow()
{
}

void AddObjectWindow::on_button_save_point()
{
  std::string name = point_name_field.get_text().raw();
  std::string x_string = point_x_field.get_text().raw();
  std::string y_string = point_y_field.get_text().raw();
  int x_cord = atoi(x_string.c_str());
  int y_cord = atoi(y_string.c_str());
  Coordinate *point_cord = new Coordinate(x_cord, y_cord);
  Point *point = new Point(name, point_cord);
  this->mainWindow->getViewport()->getViewWindow()->getDisplayFile()->addObject(point);
  this->mainWindow->getViewport()->queue_draw();
  close();
}

void AddObjectWindow::on_button_save_rect()
{
  std::string name = rect_name_field.get_text().raw();
  std::string x1_string = rect_x1_field.get_text().raw();
  std::string y1_string = rect_y1_field.get_text().raw();
  std::string x2_string = rect_x2_field.get_text().raw();
  std::string y2_string = rect_y2_field.get_text().raw();
  int x1_cord = atoi(x1_string.c_str());
  int y1_cord = atoi(y1_string.c_str());
  int x2_cord = atoi(x2_string.c_str());
  int y2_cord = atoi(y2_string.c_str());
  Coordinate *point_cord1 = new Coordinate(x1_cord, y1_cord);
  Coordinate *point_cord2 = new Coordinate(x2_cord, y2_cord);
  Rect *rect = new Rect(name, point_cord1, point_cord2);
  this->mainWindow->getViewport()->getViewWindow()->getDisplayFile()->addObject(rect);
  this->mainWindow->getViewport()->queue_draw();
  close();
}

void AddObjectWindow::on_button_save_polygon()
{
  if (!wire_cord_list.empty())
  {
    std::string name = wire_name_field.get_text().raw();
    WireFrame *wire = new WireFrame(name, wire_cord_list);
    this->mainWindow->getViewport()->getViewWindow()->getDisplayFile()->addObject(wire);
    this->mainWindow->getViewport()->queue_draw();

    while(!wire_cord_list.empty())
    {
      wire_cord_list.pop_back();
    }

    close();
  }
  else
  {
    return ;
  }
}

void AddObjectWindow::on_button_add_coordinate()
{
  std::string x_string = wire_x_field.get_text().raw();
  std::string y_string = wire_y_field.get_text().raw();
  int x_cord = atoi(x_string.c_str());
  int y_cord = atoi(y_string.c_str());
  Coordinate *wire_cord = new Coordinate(x_cord, y_cord);
  wire_cord_list.push_back(wire_cord);

  wire_x_field.set_text("");
  wire_y_field.set_text("");

  info_label.set_text("Added X : " + x_string + " Y : " + y_string);
}

void AddObjectWindow::on_button_close()
{
  close();
}
