#include "transform_object_window.hpp"

TransformObjectWindow::TransformObjectWindow(MainWindow* mainWindow, DrawableObject* object)
    : mainWindow(mainWindow),
      object(object),
      m_vbox(Gtk::ORIENTATION_VERTICAL),
      button_close("Close"),
      label_translation_x("Translate x : "),
      label_translation_y("Translate y : "),
      button_add_translation("Translate")
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
  translation_grid.attach(label_translation_y, 1, 1, 1, 1);
  translation_grid.attach(label_translation_x, 1, 2, 1, 1);
  translation_grid.attach(translation_x_field, 2, 1, 1, 1);
  translation_grid.attach(translation_y_field, 2, 2, 1, 1);
  button_add_translation.set_border_width(10);
  translation_grid.attach(button_add_translation, 2, 3, 1, 1);


  //Add scale grid
  scale_grid.set_column_homogeneous(true);
  scale_grid.set_row_spacing(10);

  //Add polygon grid
  rotate_grid.set_column_homogeneous(true);
  rotate_grid.set_row_spacing(10);

  button_close.signal_clicked().connect(sigc::mem_fun(*this,
    &TransformObjectWindow::on_button_close));

  button_add_translation.signal_clicked().connect(sigc::mem_fun(*this,
    &TransformObjectWindow::on_button_translate));

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
  //TODO
}
