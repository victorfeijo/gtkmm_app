#include "main_window.h"

MainWindow::MainWindow()
: main_box(Gtk::ORIENTATION_HORIZONTAL),
  left_box(Gtk::ORIENTATION_VERTICAL),
  right_box(Gtk::ORIENTATION_VERTICAL),
  left_frame("Buttons"),
  right_frame("View Port")
{
  set_border_width(15);
  set_title("Main Window");
  set_default_size(400, 400);
  add(main_box);

  main_box.pack_start(left_frame, Gtk::PACK_EXPAND_WIDGET, 10);

  left_box.set_border_width(10);
  left_frame.add(left_box);

  //add something to left box

  main_box.pack_start(right_frame, Gtk::PACK_EXPAND_WIDGET, 10);

  right_box.set_border_width(10);
  right_frame.add(right_box);

  //show all components
  show_all_children();

}

MainWindow::~MainWindow()
{
}
