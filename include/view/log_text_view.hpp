#ifndef GTKMM_APP_LOG_TEXT_VIEW
#define GTKMM_APP_LOG_TEXT_VIEW

/* Include any library as need to use other's components such as
 * gtkmm/button or gtkmm/frame.
 */

 #include <gtkmm/textview.h>
 #include <gtkmm/textbuffer.h>
 #include <gtkmm/adjustment.h>
 #include <string>
 #include <fstream>
 #include <ctime>

 using namespace std;

 class LogTextView : public Gtk::TextView
 {
 public:
   LogTextView(string path_log_file);
   ~LogTextView();
   void add_log_line(string line);
 protected:
   Glib::RefPtr<Gtk::TextBuffer> log_text_buffer;
   string path_log_file;
   fstream logfile;
   void add_line_file(string line);
 };
 #endif // GTKMM_APP_LOG_TEXT_VIEW
