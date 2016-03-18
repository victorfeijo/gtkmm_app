#include "draw_options_box.h"

DrawOptionsBox::DrawOptionsBox(const Glib::ustring& title,
                               gint spacing,
                               Gtk::ButtonBoxStyle layout)
: Gtk::Frame(title),
  button_add_object("Add Object"),
  button_zoom_in("Zoom in"),
  button_zoom_out("Zoom out"),
  button_close("Close")
{
  Gtk::ButtonBox* bbox = Gtk::manage( new Gtk::ButtonBox(Gtk::ORIENTATION_VERTICAL) );
  bbox->set_border_width(10);
  add(*bbox);

  bbox->set_layout(layout);
  bbox->set_spacing(spacing);

  bbox->add(button_add_object);
  bbox->add(button_zoom_in);
  bbox->add(button_zoom_out);
  bbox->add(button_close);
}

DrawOptionsBox::~DrawOptionsBox()
{
}
