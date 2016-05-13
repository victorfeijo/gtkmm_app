#include "main_window.hpp"
#include "draw_actions_box.hpp"
#include "draw_control_box.hpp"

MainWindow::MainWindow()
    : main_box(Gtk::ORIENTATION_VERTICAL),
      drawable_box(Gtk::ORIENTATION_HORIZONTAL),
      control_box(Gtk::ORIENTATION_VERTICAL),
      actions_box(Gtk::ORIENTATION_VERTICAL),
      vp_frame("Viewport"),
      down_frame("Log"),
      viewport(),
      log_text_view("logs/log_file.txt")
{
  set_border_width(15);
  set_title("Main Window");
  set_default_size(850, 600);

  add(main_box);

  main_box.pack_start(drawable_box, Gtk::PACK_EXPAND_WIDGET);


  // left_frame.set_border_width(5);

  // left_frame.add(left_box);

  // Adding the control box to the right
  control_box.set_border_width(5);
  control_box.pack_start(
    *Gtk::manage(new DrawControlBox("Control", 10, Gtk::BUTTONBOX_START, this)),
    Gtk::PACK_EXPAND_WIDGET
  );
  drawable_box.pack_start(control_box, Gtk::PACK_SHRINK);


  // viewport
  drawable_box.pack_start(vp_frame, Gtk::PACK_EXPAND_WIDGET);
  vp_frame.set_border_width(5);
  vp_frame.add(viewport);
  viewport.show();

  // Adding the actions box to the right
  actions_box.set_border_width(5);
  actions_box.pack_start(
    *Gtk::manage(new DrawActionsBox("Actions", 10, Gtk::BUTTONBOX_START, this)),
    Gtk::PACK_EXPAND_WIDGET
  );
  drawable_box.pack_start(actions_box, Gtk::PACK_SHRINK);

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
