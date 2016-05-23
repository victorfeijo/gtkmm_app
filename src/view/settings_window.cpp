#include "settings_window.hpp"

SettingsWindow::SettingsWindow(MainWindow* mainWindow)
    : mainWindow(mainWindow),
      button_close("Close"),
      settings_vbox(Gtk::ORIENTATION_VERTICAL)
{
  // MUST BE IN THE SAME ORDER THAN THE ENUMERATOR:
  this->clipping_options.append("None");
  this->clipping_options.append("Point");
  this->clipping_options.append("Cohen-Sutherland (line)");
  this->clipping_options.append("Liang-Barsky (line)");
  this->clipping_options.append("Sutherland–Hodgman (polygon/curve)");
  this->clipping_options.append("Point + Cohen-Sutherland");
  this->clipping_options.append("Point + Liang-Barsky");
  this->clipping_options.append("Point + Cohen-Sutherland + Sutherland–Hodgman");
  this->clipping_options.append("Point + Liang-Barsky + Sutherland–Hodgman");
  this->clipping_options.append("Point + Sutherland–Hodgman");
  this->clipping_options.append("Cohen-Sutherland + Sutherland–Hodgman");
  this->clipping_options.append("Liang-Barsky + Sutherland–Hodgman");

  this->clipping_options.set_active(this->mainWindow->getViewport()->
                                    getViewWindow()->getClippingType());

  this->fill_options.append("Outline");
  this->fill_options.append("Fill");

  this->fill_options.set_active(this->mainWindow->getViewport()->getFill());

  set_title("Settings");
  set_border_width(10);
  set_resizable(false);

  clipping_options.set_border_width(10);
  fill_options.set_border_width(10);
  m_notebook.append_page(clipping_options, "Clipping");
  m_notebook.append_page(fill_options, "Polygon");

  settings_vbox.pack_start(m_notebook);
  settings_vbox.pack_start(button_close, Gtk::PACK_SHRINK);

  add(settings_vbox);

  clipping_options.signal_changed().connect(
      sigc::mem_fun(*this, &SettingsWindow::on_clipping_changed));
  fill_options.signal_changed().connect(
      sigc::mem_fun(*this, &SettingsWindow::on_fill_changed));
  button_close.signal_clicked().connect(
      sigc::mem_fun(*this, &SettingsWindow::on_button_close));

  set_type_hint(Gdk::WINDOW_TYPE_HINT_DIALOG);
  set_modal();
  set_transient_for(*mainWindow);

  show_all_children();
}

void SettingsWindow::on_clipping_changed()
{
  clipping_type selected = (clipping_type)clipping_options.get_active_row_number();
  this->mainWindow->getViewport()->getViewWindow()->setClippingType(selected);
  this->mainWindow->getViewport()->queue_draw();
  this->mainWindow->getLogTextView()->add_log_line("Clipping set to " +
      (string)clipping_options.get_active_text() + "\n");
}

void SettingsWindow::on_fill_changed()
{
  bool fill = (bool) fill_options.get_active_row_number();
  this->mainWindow->getViewport()->setFill(fill);
  this->mainWindow->getViewport()->queue_draw();
}

SettingsWindow::~SettingsWindow()
{
}

void SettingsWindow::on_button_close()
{
  hide();
}
