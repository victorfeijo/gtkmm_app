#include "draw_control_box.hpp"

DrawControlBox::DrawControlBox(const Glib::ustring& title,
                               gint spacing,
                               Gtk::ButtonBoxStyle layout,
                               MainWindow* mainWindow
                              )
    : Gtk::Frame(title),
      mainWindow(mainWindow),
      button_move_up("\u2227"),
      button_move_down("\u2228"),
      button_move_left("<"),
      button_move_right(">"),
      button_zoom_in("+"),
      button_zoom_out("-"),
      button_rotate_x1("\u2909"),
      button_rotate_x2("\u2908"),
      button_rotate_y1("\u21F7"),
      button_rotate_y2("\u21F8"),
      button_rotate_z1("\u21BA"),
      button_rotate_z2("\u21BB"),
      entry_move_length(),
      entry_zoom_scale()
{
  Gtk::ButtonBox* bbox = Gtk::manage( new Gtk::ButtonBox(Gtk::ORIENTATION_VERTICAL) );
  bbox->set_border_width(10);
  add(*bbox);

  bbox->set_layout(layout);
  bbox->set_spacing(5);

  button_move_up.signal_clicked().connect(sigc::mem_fun(*this, &DrawControlBox::on_button_move_up));
  button_move_down.signal_clicked().connect(sigc::mem_fun(*this, &DrawControlBox::on_button_move_down));
  button_move_left.signal_clicked().connect(sigc::mem_fun(*this, &DrawControlBox::on_button_move_left));
  button_move_right.signal_clicked().connect(sigc::mem_fun(*this, &DrawControlBox::on_button_move_right));

  entry_move_length.set_width_chars(1);
  entry_move_length.set_text(DEFAULT_MOVE_LENGTH);

  grid_move.set_column_homogeneous(true);
  grid_move.attach(button_move_up, 2, 1, 1, 1);
  grid_move.attach(button_move_left, 1, 2, 1, 1);
  grid_move.attach(entry_move_length, 2, 2, 1, 1);
  grid_move.attach(button_move_right, 3, 2, 1, 1);
  grid_move.attach(button_move_down, 2, 3, 1, 1);

  bbox->add(grid_move);

  button_zoom_in.signal_clicked().connect(sigc::mem_fun(*this, &DrawControlBox::on_button_zoom_in));
  button_zoom_out.signal_clicked().connect(sigc::mem_fun(*this, &DrawControlBox::on_button_zoom_out));

  entry_zoom_scale.set_width_chars(1);
  char array[4];
  sprintf(array, "%f", DEFAULT_ZOOM_SCALE);
  array[3] = '\0';
  entry_zoom_scale.set_text(array);

  button_rotate_x1.signal_clicked().connect(sigc::mem_fun(*this, &DrawControlBox::on_button_rotate_x1));
  button_rotate_x2.signal_clicked().connect(sigc::mem_fun(*this, &DrawControlBox::on_button_rotate_x2));
  button_rotate_y1.signal_clicked().connect(sigc::mem_fun(*this, &DrawControlBox::on_button_rotate_y1));
  button_rotate_y2.signal_clicked().connect(sigc::mem_fun(*this, &DrawControlBox::on_button_rotate_y2));
  button_rotate_z1.signal_clicked().connect(sigc::mem_fun(*this, &DrawControlBox::on_button_rotate_z1));
  button_rotate_z2.signal_clicked().connect(sigc::mem_fun(*this, &DrawControlBox::on_button_rotate_z2));

  entry_rotation_angle.set_width_chars(1);
  entry_rotation_angle.set_text("10");

  grid_rotation.set_column_homogeneous(true);
  grid_rotation.attach(entry_rotation_angle, 2, 1, 1, 3);
  grid_rotation.attach(button_rotate_x1, 1, 1, 1, 1);
  grid_rotation.attach(button_rotate_x2, 3, 1, 1, 1);
  grid_rotation.attach(button_rotate_y1, 1, 2, 1, 1);
  grid_rotation.attach(button_rotate_y2, 3, 2, 1, 1);
  grid_rotation.attach(button_rotate_z1, 1, 3, 1, 1);
  grid_rotation.attach(button_rotate_z2, 3, 3, 1, 1);

  bbox->add(grid_rotation);

  grid_zoom.set_column_homogeneous(true);
  grid_zoom.attach(button_zoom_out, 1, 1, 1, 1);
  grid_zoom.attach(entry_zoom_scale, 2, 1, 1, 1);
  grid_zoom.attach(button_zoom_in, 3, 1, 1, 1);

  bbox->add(grid_zoom);
}

void DrawControlBox::on_button_move_up()
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

void DrawControlBox::on_button_move_down()
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

void DrawControlBox::on_button_move_left()
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

void DrawControlBox::on_button_move_right()
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

void DrawControlBox::on_button_zoom_in()
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

void DrawControlBox::on_button_zoom_out()
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

int DrawControlBox::getAngle()
{
  float rotation_angle = atoi(entry_rotation_angle.get_text().raw().c_str());
  if (rotation_angle == 0)
  {
    entry_rotation_angle.set_text("10");
  }
  return rotation_angle;
}

void DrawControlBox::on_button_rotate_x1()
{
  float rotation_angle = getAngle();
  this->mainWindow->getViewport()->getViewWindow()->rotateX(rotation_angle);
  this->mainWindow->getViewport()->queue_draw();
}

void DrawControlBox::on_button_rotate_x2()
{
  float rotation_angle = getAngle();
  this->mainWindow->getViewport()->getViewWindow()->rotateX(-1*rotation_angle);
  this->mainWindow->getViewport()->queue_draw();
}

void DrawControlBox::on_button_rotate_y1()
{
  float rotation_angle = getAngle();
  this->mainWindow->getViewport()->getViewWindow()->rotateY(rotation_angle);
  this->mainWindow->getViewport()->queue_draw();
}

void DrawControlBox::on_button_rotate_y2()
{
  float rotation_angle = getAngle();
  this->mainWindow->getViewport()->getViewWindow()->rotateY(-1*rotation_angle);
  this->mainWindow->getViewport()->queue_draw();
}

void DrawControlBox::on_button_rotate_z1()
{
  float rotation_angle = getAngle();
  this->mainWindow->getViewport()->getViewWindow()->rotateZ(rotation_angle);
  this->mainWindow->getViewport()->queue_draw();
}

void DrawControlBox::on_button_rotate_z2()
{
  float rotation_angle = getAngle();
  this->mainWindow->getViewport()->getViewWindow()->rotateZ(-1*rotation_angle);
  this->mainWindow->getViewport()->queue_draw();
}

DrawControlBox::~DrawControlBox()
{
}
