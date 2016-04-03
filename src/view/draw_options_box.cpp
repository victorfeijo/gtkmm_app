#include "draw_options_box.hpp"
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
      button_zoom_in("+"),
      button_zoom_out("-"),
      button_close("Close"),
      button_list_objects("List Objects"),
      entry_move_length(),
      entry_zoom_scale(),
      add_object_window(nullptr),
      list_objects_window(nullptr)
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

  entry_move_length.set_width_chars(1);
  entry_move_length.set_text(DEFAULT_MOVE_LENGTH);

  grid_move.set_column_homogeneous(true);
  grid_move.attach(button_move_up, 2, 1, 1, 1);
  grid_move.attach(button_move_left, 1, 2, 1, 1);
  grid_move.attach(entry_move_length, 2, 2, 1, 1);
  grid_move.attach(button_move_right, 3, 2, 1, 1);
  grid_move.attach(button_move_down, 2, 3, 1, 1);

  bbox->add(grid_move);

  button_zoom_in.signal_clicked().connect(sigc::mem_fun(*this, &DrawOptionsBox::on_button_zoom_in));
  button_zoom_out.signal_clicked().connect(sigc::mem_fun(*this, &DrawOptionsBox::on_button_zoom_out));

  entry_zoom_scale.set_width_chars(1);
  char array[4];
  sprintf(array, "%f", DEFAULT_ZOOM_SCALE);
  array[3] = '\0';
  entry_zoom_scale.set_text(array);

  grid_zoom.set_column_homogeneous(true);
  grid_zoom.attach(button_zoom_out, 1, 1, 1, 1);
  grid_zoom.attach(entry_zoom_scale, 2, 1, 1, 1);
  grid_zoom.attach(button_zoom_in, 3, 1, 1, 1);

  bbox->add(grid_zoom);

  bbox->add(button_add_object);
  bbox->add(button_list_objects);
  bbox->add(button_close);

  button_add_object.signal_clicked().connect(sigc::mem_fun(*this,
    &DrawOptionsBox::on_button_add_object));

  button_list_objects.signal_clicked().connect(sigc::mem_fun(*this,
    &DrawOptionsBox::on_button_list_objects));

  button_close.signal_clicked().connect(sigc::mem_fun(*this,
    &DrawOptionsBox::on_button_close));
}

void DrawOptionsBox::on_button_move_up()
{
  int move_length = atoi(entry_move_length.get_text().raw().c_str());
  if (move_length == 0)
  {
    entry_move_length.set_text(DEFAULT_MOVE_LENGTH);
  }
  else
  {
    this->mainWindow->getViewport()->getViewWindow()->move_up(move_length);
    this->mainWindow->getViewport()->queue_draw();
  }
}

void DrawOptionsBox::on_button_move_down()
{
  int move_length = atoi(entry_move_length.get_text().raw().c_str());
  if (move_length == 0)
  {
    entry_move_length.set_text(DEFAULT_MOVE_LENGTH);
  }
  else
  {
    this->mainWindow->getViewport()->getViewWindow()->move_down(move_length);
    this->mainWindow->getViewport()->queue_draw();
  }
}

void DrawOptionsBox::on_button_move_left()
{
  int move_length = atoi(entry_move_length.get_text().raw().c_str());
  if (move_length == 0)
  {
    entry_move_length.set_text(DEFAULT_MOVE_LENGTH);
  }
  else
  {
    this->mainWindow->getViewport()->getViewWindow()->move_left(move_length);
    this->mainWindow->getViewport()->queue_draw();
  }
}

void DrawOptionsBox::on_button_move_right()
{
  int move_length = atoi(entry_move_length.get_text().raw().c_str());
  if (move_length == 0)
  {
    entry_move_length.set_text(DEFAULT_MOVE_LENGTH);
  }
  else
  {
    this->mainWindow->getViewport()->getViewWindow()->move_right(move_length);
    this->mainWindow->getViewport()->queue_draw();
  }
}

void DrawOptionsBox::on_button_zoom_in()
{
  float zoom_scale = atof(entry_zoom_scale.get_text().raw().c_str());
  if (zoom_scale <=1)
  {
    char array[4];
    sprintf(array, "%f", DEFAULT_ZOOM_SCALE);
    array[3] = '\0';
    entry_zoom_scale.set_text(array);
  }
  else
  {
    this->mainWindow->getViewport()->getViewWindow()->zoom_in(zoom_scale);
    this->mainWindow->getViewport()->queue_draw();
  }
}

void DrawOptionsBox::on_button_zoom_out()
{
  float zoom_scale = atof(entry_zoom_scale.get_text().raw().c_str());
  if (zoom_scale <=1)
  {
    char array[4];
    sprintf(array, "%f", DEFAULT_ZOOM_SCALE);
    array[3] = '\0';
    entry_zoom_scale.set_text(array);
  }
  else
  {
    this->mainWindow->getViewport()->getViewWindow()->zoom_out(zoom_scale);
    this->mainWindow->getViewport()->queue_draw();
  }
}

DrawOptionsBox::~DrawOptionsBox()
{
  if (add_object_window != nullptr)
  {
    delete add_object_window;
  }
  if (list_objects_window != nullptr)
  {
    delete list_objects_window;
  }
}

void DrawOptionsBox::on_button_add_object()
{
  if (add_object_window != nullptr)
  {
    delete add_object_window;
  }
  add_object_window = new AddObjectWindow(this->mainWindow);
  add_object_window->show();
}

void DrawOptionsBox::on_button_list_objects()
{
  if (list_objects_window != nullptr)
  {
    delete list_objects_window;
  }
  list_objects_window = new ListObjectsWindow(this->mainWindow);
  list_objects_window->show();
}

void DrawOptionsBox::on_button_close()
{
  exit(0);
}
