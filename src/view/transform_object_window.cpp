#include "transform_object_window.hpp"

TransformObjectWindow::TransformObjectWindow(MainWindow* mainWindow, DrawableObject* object)
    : mainWindow(mainWindow),
      object(object),
      m_vbox(Gtk::ORIENTATION_VERTICAL),
      button_close("Close"),
      label_translation_x("Translate x : "),
      label_translation_y("Translate y : "),
      button_add_translation("Translate"),
      label_scale_sx("Scale Sx : "),
      label_scale_sy("Scale Sy : "),
      button_add_scale("Scale"),
      label_rotate_degree("Angle to rotate : "),
      label_rotate_x("Rotate point x : "),
      label_rotate_y("Rotate point y : "),
      button_add_rotate("Rotate")
{
  set_title("Transform Object");
  set_border_width(12);
  set_resizable(false);

  add(m_vbox);

  m_notebook.set_border_width(10);
  m_vbox.pack_start(m_notebook);
  m_vbox.pack_start(button_close, Gtk::PACK_SHRINK);

  //Add translation grid
  translation_grid.set_column_homogeneous(true);
  translation_grid.set_row_spacing(10);
  translation_grid.attach(label_translation_x, 1, 1, 1, 1);
  translation_grid.attach(label_translation_y, 1, 2, 1, 1);
  translation_grid.attach(translation_x_field, 2, 1, 1, 1);
  translation_grid.attach(translation_y_field, 2, 2, 1, 1);
  button_add_translation.set_border_width(10);
  translation_grid.attach(button_add_translation, 2, 3, 1, 1);

  //Add scale grid
  scale_grid.set_column_homogeneous(true);
  scale_grid.set_row_spacing(10);
  scale_grid.attach(label_scale_sx, 1, 1, 1, 1);
  scale_grid.attach(label_scale_sy, 1, 2, 1, 1);
  scale_grid.attach(scale_sx_field, 2, 1, 1, 1);
  scale_grid.attach(scale_sy_field, 2, 2, 1, 1);
  button_add_scale.set_border_width(10);
  scale_grid.attach(button_add_scale, 2, 3, 1, 1);

  //Add rotate grid
  rotate_grid.set_column_homogeneous(true);
  rotate_grid.set_row_spacing(10);
  rotate_grid.attach(label_rotate_degree, 1, 1, 1, 1);
  rotate_grid.attach(label_rotate_x, 1, 2, 1, 1);
  rotate_grid.attach(label_rotate_y, 1, 3, 1, 1);
  rotate_grid.attach(rotate_degree_field, 2, 1, 1, 1);
  rotate_grid.attach(rotate_x_field, 2, 2, 1, 1);
  rotate_grid.attach(rotate_y_field, 2, 3, 1, 1);
  button_add_rotate.set_border_width(10);
  rotate_grid.attach(button_add_rotate, 2, 4, 1, 1);

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

  show_all_children();
}

TransformObjectWindow::~TransformObjectWindow()
{
}

void TransformObjectWindow::on_button_close()
{
  close();
}

void TransformObjectWindow::on_button_translate()
{
  std::string dx_string = translation_x_field.get_text().raw();
  std::string dy_string = translation_y_field.get_text().raw();
  int dx = atoi(dx_string.c_str());
  int dy = atoi(dy_string.c_str());
  
  translate_service->translate(this->object, dx, dy);

  this->mainWindow->getViewport()->getViewWindow()->getDisplayFile()->addObject(this->object);
  this->mainWindow->getViewport()->queue_draw();

  this->mainWindow->getLogTextView()->add_log_line(
    this->object->getType() + " named : [" + this->object->getName() + "] was translated in ("
    + dx_string + ", " + dy_string + ")\n"
  );
  close();
}

void TransformObjectWindow::on_button_scale()
{
  //TODO
}

void TransformObjectWindow::on_button_rotate()
{
  //TODO
}
