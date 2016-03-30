#include "log_text_view.hpp"

LogTextView::LogTextView(string path_log_file)
    : path_log_file(path_log_file)
{
  set_border_width(10);
  set_editable(false);
  log_text_buffer = Gtk::TextBuffer::create();
  time_t result_time = time(NULL);
  log_text_buffer->set_text(ctime(&result_time));
  this->set_buffer(log_text_buffer);
  this->add_line_file(ctime(&result_time));
}

LogTextView::~LogTextView()
{
}

void LogTextView::add_log_line(string line)
{
  Glib::ustring actual_text = log_text_buffer->get_text();
  log_text_buffer->set_text(line + actual_text);
  this->set_buffer(log_text_buffer);
  this->add_line_file(line);
}

void LogTextView::add_line_file(string line)
{
  logfile.open(path_log_file);
  logfile.seekg(0, ios::end);
  logfile << line;
  logfile.close();
}
