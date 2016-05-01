#include "add_object_window.hpp"

AddObjectWindow::AddObjectWindow(MainWindow* mainWindow)
    : mainWindow(mainWindow),
      m_vbox(Gtk::ORIENTATION_VERTICAL),
      check_type_of_vector("Use coordinate"),
      button_add_coordenate("Add Coordenate"),
      button_add_vector("Add Vector"),
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
      info_wire_label("Insert a Coordinate:"),
      curve_x1_label("Vector X1: "),
      curve_x2_label("Vector X2: "),
      curve_y1_label("Vector Y1: "),
      curve_y2_label("Vector Y2: "),
      info_curve_label("Insert a Vector:")
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
  wire_grid.attach(info_wire_label, 2, 1, 1, 1);
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
  curve_name_field.set_placeholder_text("Name");
  curve_grid.attach(check_type_of_vector, 1, 1, 1, 1);
  curve_grid.attach(curve_name_field, 2, 1, 1, 1);
  curve_grid.attach(info_curve_label, 3, 1, 2, 1);
  curve_grid.attach(curve_x1_label, 1, 2, 1, 1);
  curve_grid.attach(curve_x1_field, 2, 2, 1, 1);
  curve_grid.attach(curve_x2_label, 3, 2, 1, 1);
  curve_grid.attach(curve_x2_field, 4, 2, 1, 1);
  curve_grid.attach(curve_y1_label, 1, 3, 1, 1);
  curve_grid.attach(curve_y1_field, 2, 3, 1, 1);
  curve_grid.attach(curve_y2_label, 3, 3, 1, 1);
  curve_grid.attach(curve_y2_field, 4, 3, 1, 1);
  curve_grid.attach(button_add_vector, 1, 4, 2, 1);
  curve_grid.attach(button_save_curve, 3, 4, 2, 1);
  curve_grid.set_border_width(10);

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

  button_add_vector.signal_clicked().connect(sigc::mem_fun(*this,
    &AddObjectWindow::on_button_add_vector) );

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

  info_wire_label.set_text("Added X : " + std::to_string(x_cord) +
                      " Y : " + std::to_string(y_cord));
}

void AddObjectWindow::on_button_add_vector()
{
  std::string x1_string = curve_x1_field.get_text().raw();
  std::string y1_string = curve_y1_field.get_text().raw();
  std::string x2_string = curve_x2_field.get_text().raw();
  std::string y2_string = curve_y2_field.get_text().raw();
  int x1_cord = atoi(x1_string.c_str());
  int y1_cord = atoi(y1_string.c_str());
  int x2_cord = atoi(x2_string.c_str());
  int y2_cord = atoi(y2_string.c_str());

  Coordinate begin(x1_cord, y1_cord);
  if (check_type_of_vector.get_active())
  {
    Coordinate end(x2_cord, y2_cord);
    Vector vector(begin, end);
    curve_vector_list.push_back(vector);
  }
  else 
  {
    Vector vector(begin, x2_cord, y2_cord);
    curve_vector_list.push_back(vector);
  }

  curve_x1_field.set_text("");
  curve_x2_field.set_text("");
  curve_y1_field.set_text("");
  curve_y2_field.set_text("");

  info_curve_label.set_text("Added X1 : " + std::to_string(x1_cord) +
                      " Y1 : " + std::to_string(y1_cord) + 
                      " X2 : " + std::to_string(x2_cord) +
                      " Y2 : " + std::to_string(y2_cord));
}

void AddObjectWindow::on_button_save_curve()
{
  if (curve_vector_list.size() > 1)
  {
    std::string name = curve_name_field.get_text().raw();
    if (name.empty())
    {
      curve_name_field.grab_focus();
      return;
    }

    Curve2D *curve = new Curve2D(name, curve_vector_list);
    this->mainWindow->getViewport()->getViewWindow()->getDisplayFile()->addObject(curve);
    this->mainWindow->getViewport()->queue_draw();

    std::string curve_string_cord = "";
    while(!curve_vector_list.empty())
    {
      Vector vec = curve_vector_list.back();
      curve_vector_list.pop_back();
      curve_string_cord += "(" + to_string((int)vec.getBegin().getx()) + ", " +
          to_string((int)vec.getBegin().gety()) + ") " + "(" + to_string((int)vec.getEnd().getx()) +
          ", " + to_string((int)vec.getEnd().gety()) + ") ";
    }

    mainWindow->getLogTextView()->add_log_line(
      "A curve named [" + name + "] was added with " + curve_string_cord + "\n"
    );

    close();
  }
  else 
  {
   info_curve_label.set_text("You need at least 2 vector's"); 
  }
}

void AddObjectWindow::on_button_close()
{
  close();
}
