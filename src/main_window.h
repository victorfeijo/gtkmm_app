#ifndef GTKMM_APP_MAIN_WINDOW
#define GTKMM_APP_MAIN_WINDOW

/* Include any library as need to use other's components such as
 * gtkmm/button or gtkmm/frame.
 */
#include <gtkmm/window.h>

class MainWindow : public Gtk::Window
{

public:
  MainWindow();
  virtual ~MainWindow();

protected:
  /* Add here any components or frames
   */
};
#endif // GTKMM_APP_MAIN_WINDOW
