#include "main_window.hpp"
#include "draw_options_box.hpp"

MainWindow::MainWindow()
    : main_box(Gtk::ORIENTATION_VERTICAL),
      drawable_box(Gtk::ORIENTATION_HORIZONTAL),
      left_box(Gtk::ORIENTATION_VERTICAL),
      left_frame("Buttons"),
      right_frame("Viewport"),
      down_frame("Log Bar"),
      viewport(),
      log_text_view("logs/trab12.txt")
{
  set_border_width(15);
  set_title("Main Window");
  set_default_size(700, 500);
  // set_resizable(false);
  add(main_box);

  main_box.pack_start(drawable_box, Gtk::PACK_SHRINK, 10);

  drawable_box.pack_start(left_frame, Gtk::PACK_SHRINK, 10);

  left_box.set_border_width(10);
  left_frame.add(left_box);

  // Adding the draw options box to left frame
  left_box.pack_start(
    *Gtk::manage(new DrawOptionsBox("Draw Options", 10, Gtk::BUTTONBOX_START, this)),
    Gtk::PACK_EXPAND_WIDGET
  );

  // viewport
  drawable_box.pack_start(right_frame, Gtk::PACK_EXPAND_WIDGET, 10);
  right_frame.add(viewport);
  viewport.show();

  //Log
  main_box.pack_start(down_frame, Gtk::PACK_EXPAND_WIDGET, 10);
  scrolled_log.add(log_text_view);
  scrolled_log.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
  down_frame.add(scrolled_log);
  // show all components
  log_text_view.add_log_line("test\n");
  show_all_children();
}

Viewport* MainWindow::getViewport()
{
  return &this->viewport;
}

MainWindow::~MainWindow()
{
}