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
      log_text_view("logs/log_file.txt")
{
  set_border_width(15);
  set_title("Main Window");
  set_default_size(700, 550);
  // set_resizable(false);
  add(main_box);

  main_box.pack_start(drawable_box, Gtk::PACK_EXPAND_WIDGET);

  drawable_box.pack_start(left_frame, Gtk::PACK_SHRINK);

  left_frame.set_border_width(5);

  left_box.set_border_width(10);
  left_frame.add(left_box);

  // Adding the draw options box to left frame
  left_box.pack_start(
    *Gtk::manage(new DrawOptionsBox("Draw Options", 10, Gtk::BUTTONBOX_START, this)),
    Gtk::PACK_EXPAND_WIDGET
  );

  // viewport
  drawable_box.pack_start(right_frame, Gtk::PACK_EXPAND_WIDGET);
  right_frame.set_border_width(5);
  right_frame.add(viewport);
  viewport.show();

  //Log
  scrolled_log.add(log_text_view);
  scrolled_log.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
  scrolled_log.set_size_request(0, 75);
  down_frame.set_border_width(5);
  down_frame.add(scrolled_log);
  main_box.pack_start(down_frame, Gtk::PACK_SHRINK);
  // show all components
  show_all_children();
}

Viewport* MainWindow::getViewport()
{
  return &this->viewport;
}

LogTextView* MainWindow::getLogTextView()
{
  return &this->log_text_view;
}

MainWindow::~MainWindow()
{
}
