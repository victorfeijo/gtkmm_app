#include "simple_window.hpp"

SimpleWindow::SimpleWindow(std::string label_text, std::string window_title)
  : label(label_text),
    ok_button("Ok", Gtk::RESPONSE_OK),
    cancel_button("Cancel", Gtk::RESPONSE_CANCEL),
    window_title(window_title)
{
  set_title(window_title);
  set_border_width(12);
  set_resizable(false);
  add(grid);

  grid.set_column_homogeneous(true);
  grid.set_row_spacing(10);
  grid.attach(label, 1, 1, 1, 1);
  grid.attach(text_entry, 2, 1, 1, 1);
  grid.attach(cancel_button, 1, 2, 1, 1);
  grid.attach(ok_button, 2, 2, 1, 1);

}

SimpleWindow::~SimpleWindow()
{
}

std::string SimpleWindow::get_text()
{
  return this->selected_path;
}
