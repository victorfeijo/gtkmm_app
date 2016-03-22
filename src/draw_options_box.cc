#include "draw_options_box.h"
#include <iostream>

DrawOptionsBox::DrawOptionsBox(const Glib::ustring& title,
                               gint spacing,
                               Gtk::ButtonBoxStyle layout,
                               MainWindow* mainWindow
                              )
    : Gtk::Frame(title),
      mainWindow(mainWindow),
      button_add_object("Add Object"),
      button_move_up("\u2227"),
      button_move_down("\u2228"),
      button_move_left("<"),
      button_move_right(">"),
      button_zoom_in("Zoom in"),
      button_zoom_out("Zoom out"),
      button_close("Close"),
      button_list_objects("List Objects")
{
  Gtk::ButtonBox* bbox = Gtk::manage( new Gtk::ButtonBox(Gtk::ORIENTATION_VERTICAL) );
  bbox->set_border_width(10);
  add(*bbox);

  bbox->set_layout(layout);
  bbox->set_spacing(spacing);

  button_move_up.signal_clicked().connect(sigc::mem_fun(*this, &DrawOptionsBox::on_button_move_up));
  button_move_down.signal_clicked().connect(sigc::mem_fun(*this, &DrawOptionsBox::on_button_move_down));
  button_move_left.signal_clicked().connect(sigc::mem_fun(*this, &DrawOptionsBox::on_button_move_left));
  button_move_right.signal_clicked().connect(sigc::mem_fun(*this, &DrawOptionsBox::on_button_move_right));
  button_zoom_in.signal_clicked().connect(sigc::mem_fun(*this, &DrawOptionsBox::on_button_zoom_in));
  button_zoom_out.signal_clicked().connect(sigc::mem_fun(*this, &DrawOptionsBox::on_button_zoom_out));

  grid_move.set_column_homogeneous(true);
  grid_move.attach(button_move_up, 2, 1, 1, 1);
  grid_move.attach(button_move_left, 1, 2, 1, 1);
  grid_move.attach(button_move_right, 3, 2, 1, 1);
  grid_move.attach(button_move_down, 2, 3, 1, 1);

  bbox->add(grid_move);
  bbox->add(button_zoom_in);
  bbox->add(button_zoom_out);
  bbox->add(button_add_object);
  bbox->add(button_list_objects);
  bbox->add(button_close);

  button_add_object.signal_clicked().connect(sigc::mem_fun(*this,
    &DrawOptionsBox::on_button_add_object));

  button_list_objects.signal_clicked().connect(sigc::mem_fun(*this,
    &DrawOptionsBox::on_button_list_objects));
}

void DrawOptionsBox::on_button_move_up()
{
  this->mainWindow->getViewport()->getViewWindow()->move_up();
  this->mainWindow->getViewport()->queue_draw();
}

void DrawOptionsBox::on_button_move_down()
{
  this->mainWindow->getViewport()->getViewWindow()->move_down();
  this->mainWindow->getViewport()->queue_draw();
}

void DrawOptionsBox::on_button_move_left()
{
  this->mainWindow->getViewport()->getViewWindow()->move_left();
  this->mainWindow->getViewport()->queue_draw();
}

void DrawOptionsBox::on_button_move_right()
{
  this->mainWindow->getViewport()->getViewWindow()->move_right();
  this->mainWindow->getViewport()->queue_draw();
}

void DrawOptionsBox::on_button_zoom_in()
{
  this->mainWindow->getViewport()->getViewWindow()->zoom_in();
  this->mainWindow->getViewport()->queue_draw();
}

void DrawOptionsBox::on_button_zoom_out()
{
  this->mainWindow->getViewport()->getViewWindow()->zoom_out();
  this->mainWindow->getViewport()->queue_draw();
}

DrawOptionsBox::~DrawOptionsBox()
{
}

void DrawOptionsBox::on_button_add_object()
{
  add_object_window = new AddObjectWindow(this->mainWindow);
  add_object_window->show();
}

void DrawOptionsBox::on_button_list_objects()
{
  list_objects_window = new ListObjectsWindow(this->mainWindow);
  list_objects_window->show();
}
