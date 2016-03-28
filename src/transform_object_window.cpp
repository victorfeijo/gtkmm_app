#include "transform_object_window.hpp"

TransformObjectWindow::TransformObjectWindow(MainWindow* mainWindow, DrawableObject* object)
    : mainWindow(mainWindow),
      object(object),
      m_vbox(Gtk::ORIENTATION_VERTICAL),
      button_close("Close")
{
  set_title("Transform Object");
  set_border_width(12);
  set_resizable(false);

  add(m_vbox);

  m_notebook.set_border_width(0);
  m_vbox.pack_start(m_notebook);
  m_vbox.pack_start(button_close, Gtk::PACK_SHRINK);

  //Add translation grid
  translation_grid.set_column_homogeneous(true);
  translation_grid.set_row_spacing(10);

  //Add scale grid
  scale_grid.set_column_homogeneous(true);
  scale_grid.set_row_spacing(10);

  //Add polygon grid
  rotate_grid.set_column_homogeneous(true);
  rotate_grid.set_row_spacing(10);

  button_close.signal_clicked().connect(sigc::mem_fun(*this,
    &TransformObjectWindow::on_button_close));

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
