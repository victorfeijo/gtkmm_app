#include "transform_object_window.hpp"

TransformObjectWindow::TransformObjectWindow(MainWindow* mainWindow, DrawableObject* object)
    : mainWindow(mainWindow),
      object(object),
      label_translation_x("Translate X:"),
      label_translation_y("Translate Y:"),
      label_translation_z("Translate Z:"),
      label_scale_sx("Scale X:"),
      label_scale_sy("Scale Y:"),
      label_scale_sz("Scale Z:"),
      label_rotate_axis("Rotate around:"),
      label_rotate_x("Point X:"),
      label_rotate_y("Point Y:"),
      label_rotate_z("Point Z:"),
      label_rotate_degree("Angle to rotate:"),
      label_rotate_point("Reference point:"),
      label_rotate_axis_x1("Axis X\u2081"),
      label_rotate_axis_y1("Axis Y\u2081"),
      label_rotate_axis_z1("Axis Z\u2081"),
      label_rotate_axis_x2("Axis X\u2082"),
      label_rotate_axis_y2("Axis Y\u2082"),
      label_rotate_axis_z2("Axis Z\u2082"),
      m_vbox(Gtk::ORIENTATION_VERTICAL),
      button_close("Close"),
      button_add_translation("Translate"),
      button_add_scale("Scale"),
      button_add_rotate("Rotate")
{
  set_title("Transform Object");
  set_border_width(12);
  set_resizable(false);

  add(m_vbox);

  m_vbox.pack_start(m_notebook);
  m_vbox.pack_start(button_close, Gtk::PACK_SHRINK);

  //Add translation grid
  translation_grid.set_column_homogeneous(true);
  translation_grid.set_row_spacing(10);
  translation_grid.set_column_spacing(10);
  translation_grid.attach(label_translation_x, 1, 1, 1, 1);
  translation_grid.attach(label_translation_y, 1, 2, 1, 1);
  translation_grid.attach(label_translation_z, 1, 3, 1, 1);
  translation_grid.attach(translation_x_field, 2, 1, 1, 1);
  translation_grid.attach(translation_y_field, 2, 2, 1, 1);
  translation_grid.attach(translation_z_field, 2, 3, 1, 1);
  translation_grid.attach(button_add_translation, 1, 4, 2, 1);
  translation_grid.set_border_width(10);

  //Add scale grid
  scale_grid.set_column_homogeneous(true);
  scale_grid.set_row_spacing(10);
  scale_grid.set_column_spacing(10);
  scale_grid.attach(label_scale_sx, 1, 1, 1, 1);
  scale_grid.attach(label_scale_sy, 1, 2, 1, 1);
  scale_grid.attach(label_scale_sz, 1, 3, 1, 1);
  scale_grid.attach(scale_sx_field, 2, 1, 1, 1);
  scale_grid.attach(scale_sy_field, 2, 2, 1, 1);
  scale_grid.attach(scale_sz_field, 2, 3, 1, 1);
  scale_grid.attach(button_add_scale, 1, 4, 2, 1);
  scale_grid.set_border_width(10);

  //Add rotate grid
  rotate_axis.append("X Axis");
  rotate_axis.append("Y Axis");
  rotate_axis.append("Z Axis");
  rotate_axis.append("Custom Axis");
  rotate_axis.set_active(0);
  rotate_axis.signal_changed().connect(
    sigc::mem_fun(*this, &TransformObjectWindow::on_rotate_axis_changed));
    rotate_grid.set_column_homogeneous(true);
  rotate_point.append("Object Center");
  rotate_point.append("World Center");
  rotate_point.append("Custom Point");
  rotate_point.set_active(0);
  rotate_point.signal_changed().connect(
    sigc::mem_fun(*this, &TransformObjectWindow::on_rotate_point_changed));
  rotate_grid.set_row_spacing(10);
  rotate_grid.set_column_spacing(10);
  rotate_grid.attach(label_rotate_degree, 1, 1, 2, 1);
  rotate_grid.attach(rotate_degree_field, 3, 1, 2, 1);
  rotate_grid.attach(label_rotate_axis, 1, 2, 2, 1);
  rotate_grid.attach(rotate_axis, 3, 2, 2, 1);
  rotate_grid.attach(label_rotate_point, 1, 6, 2, 1);
  rotate_grid.attach(rotate_point, 3, 6, 2, 1);
  rotate_grid.attach(button_add_rotate, 1, 10, 4, 1);
  rotate_grid.set_border_width(10);

  button_close.signal_clicked().connect(sigc::mem_fun(*this,
    &TransformObjectWindow::on_button_close));

  button_add_translation.signal_clicked().connect(sigc::mem_fun(*this,
    &TransformObjectWindow::on_button_translate));

  button_add_scale.signal_clicked().connect(sigc::mem_fun(*this,
    &TransformObjectWindow::on_button_scale));

  button_add_rotate.signal_clicked().connect(sigc::mem_fun(*this,
    &TransformObjectWindow::on_button_rotate));

  m_notebook.append_page(translation_grid, "Translate");
  m_notebook.append_page(scale_grid, "Scale");
  m_notebook.append_page(rotate_grid, "Rotate");

  set_type_hint(Gdk::WINDOW_TYPE_HINT_DIALOG);
  set_modal();
  set_transient_for(*mainWindow);

  show_all_children();
}

void TransformObjectWindow::on_rotate_point_changed()
{
  if (rotate_point.get_active_row_number() == 2)
  {
    if (label_rotate_x.get_parent() == NULL)
    {
      rotate_grid.attach(label_rotate_x, 1, 7, 2, 1);
      rotate_grid.attach(label_rotate_y, 1, 8, 2, 1);
      rotate_grid.attach(label_rotate_z, 1, 9, 2, 1);
      rotate_grid.attach(rotate_x_field, 3, 7, 2, 1);
      rotate_grid.attach(rotate_y_field, 3, 8, 2, 1);
      rotate_grid.attach(rotate_z_field, 3, 9, 2, 1);
      label_rotate_x.show();
      label_rotate_y.show();
      label_rotate_z.show();
      rotate_x_field.show();
      rotate_y_field.show();
      rotate_z_field.show();
    }
  }
  else
  {
    if (label_rotate_x.get_parent() != NULL)
    {
      rotate_grid.remove(label_rotate_x);
      rotate_grid.remove(rotate_x_field);
      rotate_grid.remove(label_rotate_y);
      rotate_grid.remove(rotate_y_field);
      rotate_grid.remove(label_rotate_z);
      rotate_grid.remove(rotate_z_field);
    }
  }
}

void TransformObjectWindow::on_rotate_axis_changed()
{
  if (rotate_axis.get_active_row_number() == 3)
  {
    if (label_rotate_axis_x1.get_parent() == NULL)
    {
      rotate_grid.attach(label_rotate_axis_x1, 1, 3, 1, 1);
      rotate_grid.attach(label_rotate_axis_y1, 1, 4, 1, 1);
      rotate_grid.attach(label_rotate_axis_z1, 1, 5, 1, 1);
      rotate_grid.attach(rotate_axis_x1_field, 2, 3, 1, 1);
      rotate_grid.attach(rotate_axis_y1_field, 2, 4, 1, 1);
      rotate_grid.attach(rotate_axis_z1_field, 2, 5, 1, 1);
      rotate_grid.attach(label_rotate_axis_x2, 3, 3, 1, 1);
      rotate_grid.attach(label_rotate_axis_y2, 3, 4, 1, 1);
      rotate_grid.attach(label_rotate_axis_z2, 3, 5, 1, 1);
      rotate_grid.attach(rotate_axis_x2_field, 4, 3, 1, 1);
      rotate_grid.attach(rotate_axis_y2_field, 4, 4, 1, 1);
      rotate_grid.attach(rotate_axis_z2_field, 4, 5, 1, 1);
      rotate_grid.remove(label_rotate_point);
      rotate_grid.remove(rotate_point);
      label_rotate_axis_x1.show();
      label_rotate_axis_y1.show();
      label_rotate_axis_z1.show();
      rotate_axis_x1_field.show();
      rotate_axis_y1_field.show();
      rotate_axis_z1_field.show();
      label_rotate_axis_x2.show();
      label_rotate_axis_y2.show();
      label_rotate_axis_z2.show();
      rotate_axis_x2_field.show();
      rotate_axis_y2_field.show();
      rotate_axis_z2_field.show();
      if (label_rotate_x.get_parent() != NULL)
      {
        rotate_grid.remove(label_rotate_x);
        rotate_grid.remove(label_rotate_y);
        rotate_grid.remove(label_rotate_z);
        rotate_grid.remove(rotate_x_field);
        rotate_grid.remove(rotate_y_field);
        rotate_grid.remove(rotate_z_field);
      }
    }
  }
  else
  {
    if (label_rotate_point.get_parent() == NULL)
    {
      rotate_grid.remove(label_rotate_axis_x1);
      rotate_grid.remove(label_rotate_axis_y1);
      rotate_grid.remove(label_rotate_axis_z1);
      rotate_grid.remove(rotate_axis_x1_field);
      rotate_grid.remove(rotate_axis_y1_field);
      rotate_grid.remove(rotate_axis_z1_field);
      rotate_grid.remove(label_rotate_axis_x2);
      rotate_grid.remove(label_rotate_axis_y2);
      rotate_grid.remove(label_rotate_axis_z2);
      rotate_grid.remove(rotate_axis_x2_field);
      rotate_grid.remove(rotate_axis_y2_field);
      rotate_grid.remove(rotate_axis_z2_field);
      rotate_grid.attach(label_rotate_point, 1, 6, 2, 1);
      rotate_grid.attach(rotate_point, 3, 6, 2, 1);
      rotate_point.set_active(0);
      label_rotate_point.show();
      rotate_point.show();
    }
  }
}


TransformObjectWindow::~TransformObjectWindow()
{
}

void TransformObjectWindow::on_button_close()
{
  hide();
}

void TransformObjectWindow::on_button_translate()
{
  std::string dx_string = translation_x_field.get_text().raw();
  std::string dy_string = translation_y_field.get_text().raw();
  std::string dz_string = translation_z_field.get_text().raw();
  int dx = atoi(dx_string.c_str());
  int dy = atoi(dy_string.c_str());
  int dz = atoi(dz_string.c_str());

  translate_service.translate(this->object, dx, dy, dz);

  this->mainWindow->getViewport()->queue_draw();

  this->mainWindow->getLogTextView()->add_log_line(
      this->object->getTypeName() + " named [" + this->object->getName() + "] was translated in ("
      + to_string(dx) + ", " + to_string(dy) + ", " + to_string(dz) + ")\n"
  );
  hide();
}

void TransformObjectWindow::on_button_scale()
{
  std::string sx_string = scale_sx_field.get_text().raw();
  std::string sy_string = scale_sy_field.get_text().raw();
  std::string sz_string = scale_sz_field.get_text().raw();
  float sx = atof(sx_string.c_str());
  float sy = atof(sy_string.c_str());
  float sz = atof(sz_string.c_str());

  scale_service.scale(this->object, sx, sy, sz);

  this->mainWindow->getViewport()->queue_draw();

  this->mainWindow->getLogTextView()->add_log_line(
      this->object->getTypeName() + " named [" + this->object->getName() + "] was scaled in ("
      + to_string(sx) + ", " + to_string(sy) + ", " + to_string(sz) + ")\n"
  );
  hide();
}

void TransformObjectWindow::on_button_rotate()
{
  int dx, dy, dz;
  string reference = " with reference ";
  if (rotate_point.get_active_row_number() == 0)
  {
    Coordinate center = object->getCenterOnWorld();
    dx = center.getx();
    dy = center.gety();
    dz = center.getz();
    reference += "on its center";
  }
  else if (rotate_point.get_active_row_number() == 1)
  {
    dx = 0;
    dy = 0;
    dz = 0;
    reference += "on world's center";
  }
  else
  {
    string dx_string = rotate_x_field.get_text().raw();
    string dy_string = rotate_y_field.get_text().raw();
    string dz_string = rotate_z_field.get_text().raw();
    dx = atoi(dx_string.c_str());
    dy = atoi(dy_string.c_str());
    dz = atoi(dz_string.c_str());
    reference += "(" + to_string(dx) + ", " + to_string(dy)
    + ", " + to_string(dz) + ")";
  }
  string angle_string = rotate_degree_field.get_text().raw();
  int angle = atoi(angle_string.c_str());
  string axis = rotate_axis.get_active_text();

  if (rotate_axis.get_active_row_number() == 0)
  {
    rotate_service.rotateX(this->object, dx, dy, dz, angle);
  }
  else if (rotate_axis.get_active_row_number() == 1)
  {
    rotate_service.rotateY(this->object, dx, dy, dz, angle);
  }
  else if (rotate_axis.get_active_row_number() == 2)
  {
    rotate_service.rotateZ(this->object, dx, dy, dz, angle);
  }
  else
  {
    string x1_string = rotate_axis_x1_field.get_text().raw();
    string y1_string = rotate_axis_y1_field.get_text().raw();
    string z1_string = rotate_axis_z1_field.get_text().raw();
    string x2_string = rotate_axis_x2_field.get_text().raw();
    string y2_string = rotate_axis_y2_field.get_text().raw();
    string z2_string = rotate_axis_z2_field.get_text().raw();
    int x1 = atoi(x1_string.c_str());
    int y1 = atoi(y1_string.c_str());
    int z1 = atoi(z1_string.c_str());
    Coordinate cord1(x1, y1, z1);
    int x2 = atoi(x2_string.c_str());
    int y2 = atoi(y2_string.c_str());
    int z2 = atoi(z2_string.c_str());
    Coordinate cord2(x2, y2, z2);
    Vector vec(cord1, cord2);
    rotate_service.rotateAxis(this->object, vec, angle);
    axis = "Axis [(" + to_string(x1) + ", " + to_string(y1)
    + ", " + to_string(z1) + "), (" + to_string(x2) + ", " + to_string(y2)
    + ", " + to_string(z2) + ")] ";
    reference = "";
  }

  this->mainWindow->getViewport()->queue_draw();

  this->mainWindow->getLogTextView()->add_log_line(
      this->object->getTypeName() + " named [" + this->object->getName() + "] was rotated in "
      + to_string(angle) + "º around " + axis + reference + "\n"
  );
  hide();
}
