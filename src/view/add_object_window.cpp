#include "add_object_window.hpp"

AddObjectWindow::AddObjectWindow(MainWindow* mainWindow)
    : mainWindow(mainWindow),
      m_vbox(Gtk::ORIENTATION_VERTICAL),
      button_add_coordenate("Add Coordenate"),
      button_save_line("Save Line"),
      button_save_wire("Save Polygon"),
      button_save_point("Save Point"),
      button_save_curve("Save Curve"),
      button_close("Close"),
      point_x_label("Coordinate X: "),
      point_y_label("Coordinate Y: "),
      line_x1_label("Coordinate X\u2081: "),
      line_x2_label("Coordinate X\u2082: "),
      line_y1_label("Coordinate Y\u2081: "),
      line_y2_label("Coordinate Y\u2082: "),
      wire_x_label("Coordinate X: "),
      wire_y_label("Coordinate Y: "),
      info_label("Insert a Coordinate:")
{
  set_title("Add Object");
  set_border_width(12);
  set_resizable(false);

  add(m_vbox);

  m_notebook.set_border_width(0);
  m_vbox.pack_start(m_notebook);
  m_vbox.pack_start(button_close, Gtk::PACK_SHRINK);

  //Add point grid
  point_grid.set_column_homogeneous(true);
  point_grid.set_row_spacing(10);
  point_name_field.set_placeholder_text("Name");
  point_grid.attach(point_name_field, 1, 1, 2, 1);
  point_grid.attach(point_x_label, 1, 2, 1, 1);
  point_grid.attach(point_x_field, 2, 2, 1, 1);
  point_grid.attach(point_y_label, 1, 3, 1, 1);
  point_grid.attach(point_y_field, 2, 3, 1, 1);
  point_grid.attach(button_save_point, 1, 4, 2, 1);
  point_grid.set_border_width(10);

  //Add line grid
  line_grid.set_column_homogeneous(true);
  line_grid.set_row_spacing(10);
  line_name_field.set_placeholder_text("Name");
  line_grid.attach(line_name_field, 1, 1, 4, 1);
  line_grid.attach(line_x1_label, 1, 2, 1, 1);
  line_grid.attach(line_x1_field, 2, 2, 1, 1);
  line_grid.attach(line_x2_label, 1, 3, 1, 1);
  line_grid.attach(line_x2_field, 2, 3, 1, 1);
  line_grid.attach(line_y1_label, 3, 2, 1, 1);
  line_grid.attach(line_y1_field, 4, 2, 1, 1);
  line_grid.attach(line_y2_label, 3, 3, 1, 1);
  line_grid.attach(line_y2_field, 4, 3, 1, 1);
  line_grid.attach(button_save_line, 1, 4, 4, 1);
  line_grid.set_border_width(10);

  //Add polygon grid
  wire_grid.set_column_homogeneous(true);
  wire_grid.set_row_spacing(10);
  wire_grid.set_column_spacing(10);
  wire_name_field.set_placeholder_text("Name");
  wire_grid.attach(wire_name_field, 1, 1, 1, 1);
  wire_grid.attach(info_label, 2, 1, 1, 1);
  wire_grid.attach(wire_x_label, 1, 2, 1, 1);
  wire_grid.attach(wire_x_field, 2, 2, 1, 1);
  wire_grid.attach(wire_y_label, 1, 3, 1, 1);
  wire_grid.attach(wire_y_field, 2, 3, 1, 1);
  wire_grid.attach(button_add_coordenate, 1, 4, 1, 1);
  wire_grid.attach(button_save_wire, 2, 4, 1, 1);
  wire_grid.set_border_width(10);

  //Add curve grid
  curve_grid.set_column_homogeneous(true);
  curve_grid.set_row_spacing(10);
  curve_grid.set_column_spacing(10);
  curve_grid.attach(button_save_curve, 1, 1, 1, 1);

  button_close.signal_clicked().connect(sigc::mem_fun(*this,
    &AddObjectWindow::on_button_close) );

  button_save_point.signal_clicked().connect(sigc::mem_fun(*this,
    &AddObjectWindow::on_button_save_point) );

  button_save_line.signal_clicked().connect(sigc::mem_fun(*this,
    &AddObjectWindow::on_button_save_line) );

  button_add_coordenate.signal_clicked().connect(sigc::mem_fun(*this,
    &AddObjectWindow::on_button_add_coordinate) );

  button_save_wire.signal_clicked().connect(sigc::mem_fun(*this,
    &AddObjectWindow::on_button_save_polygon) );

  button_save_curve.signal_clicked().connect(sigc::mem_fun(*this,
    &AddObjectWindow::on_button_save_curve) );

  m_notebook.append_page(point_grid, "Point");
  m_notebook.append_page(line_grid, "Line");
  m_notebook.append_page(wire_grid, "Polygon");
  m_notebook.append_page(curve_grid, "Curve");

  set_type_hint(Gdk::WINDOW_TYPE_HINT_DIALOG);
  set_modal();
  set_transient_for(*mainWindow);

  show_all_children();
}

AddObjectWindow::~AddObjectWindow()
{
}

void AddObjectWindow::on_button_save_point()
{
  std::string name = point_name_field.get_text().raw();
  if (name.empty())
  {
    point_name_field.grab_focus();
    return;
  }
  std::string x_string = point_x_field.get_text().raw();
  std::string y_string = point_y_field.get_text().raw();
  int x_cord = atoi(x_string.c_str());
  int y_cord = atoi(y_string.c_str());
  Coordinate point_cord = Coordinate(x_cord, y_cord);
  Point *point = new Point(name, point_cord);
  this->mainWindow->getViewport()->getViewWindow()->getDisplayFile()->addObject(point);
  this->mainWindow->getViewport()->queue_draw();

  mainWindow->getLogTextView()->add_log_line(
    "Point named [" + name + "] was added with ("
        + to_string((int)x_cord) + ", " + to_string((int)y_cord) + ")\n"
  );

  close();
}

void AddObjectWindow::on_button_save_line()
{
  std::string name = line_name_field.get_text().raw();
  if (name.empty())
  {
    line_name_field.grab_focus();
    return;
  }
  std::string x1_string = line_x1_field.get_text().raw();
  std::string y1_string = line_y1_field.get_text().raw();
  std::string x2_string = line_x2_field.get_text().raw();
  std::string y2_string = line_y2_field.get_text().raw();
  int x1_cord = atoi(x1_string.c_str());
  int y1_cord = atoi(y1_string.c_str());
  int x2_cord = atoi(x2_string.c_str());
  int y2_cord = atoi(y2_string.c_str());
  Coordinate point_cord1 = Coordinate(x1_cord, y1_cord);
  Coordinate point_cord2 = Coordinate(x2_cord, y2_cord);
  Line *line = new Line(name, point_cord1, point_cord2);
  this->mainWindow->getViewport()->getViewWindow()->getDisplayFile()->addObject(line);
  this->mainWindow->getViewport()->queue_draw();

  mainWindow->getLogTextView()->add_log_line(
    "Line named [" + name + "] was added with (" + to_string((int)x1_cord)+ ", "
        + to_string((int)y1_cord) + ") and " + "(" + to_string((int)x2_cord) + ", "
        + to_string((int)y2_cord) + ")\n"
  );

  close();
}

void AddObjectWindow::on_button_save_polygon()
{
  if (!wire_cord_list.empty())
  {
    std::string name = wire_name_field.get_text().raw();
    if (name.empty())
    {
      wire_name_field.grab_focus();
      return;
    }
    WireFrame *wire = new WireFrame(name, wire_cord_list);
    this->mainWindow->getViewport()->getViewWindow()->getDisplayFile()->addObject(wire);
    this->mainWindow->getViewport()->queue_draw();

    std::string polygon_string_cord = "";
    while(!wire_cord_list.empty())
    {
      Coordinate cord = wire_cord_list.back();
      wire_cord_list.pop_back();
      polygon_string_cord += "(" + to_string((int)cord.getx()) + ", " +
          to_string((int)cord.gety()) + ") ";
    }

    mainWindow->getLogTextView()->add_log_line(
      "A polygon named [" + name + "] was added with " + polygon_string_cord + "\n"
    );

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
  Coordinate wire_cord = Coordinate(x_cord, y_cord);
  wire_cord_list.push_back(wire_cord);

  wire_x_field.set_text("");
  wire_y_field.set_text("");

  info_label.set_text("Added X : " + std::to_string(x_cord) +
                      " Y : " + std::to_string(y_cord));
}

void AddObjectWindow::on_button_save_curve()
{
  //TODO
}

void AddObjectWindow::on_button_close()
{
  close();
}
