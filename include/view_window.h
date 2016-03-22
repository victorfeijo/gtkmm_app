#ifndef GTKMM_APP_VIEW_WINDOW
#define GTKMM_APP_VIEW_WINDOW

#include "display_file.h"

class ViewWindow
{

  friend class Viewport;

public:
  ViewWindow(int Xwmin, int Ywmin, int Xwmax, int Ywmax);
  virtual ~ViewWindow();
  void zoom_in(float scale = 1.5);
  void zoom_out(float scale = 1.5);
  void move_up(unsigned int length = 10);
  void move_down(unsigned int length = 10);
  void move_left(unsigned int length = 10);
  void move_right(unsigned int length = 10);
  DisplayFile* getDisplayFile();

protected:
  DisplayFile displayFile;
  float Xwmin, Ywmin, Xwmax, Ywmax;
  int getXwmin();
  int getYwmin();
  int getXwmax();
  int getYwmax();
  void setXwmin(int Xwmin);
  void setYwmin(int Ywmin);
  void setXwmax(int Xwmax);
  void setYwmax(int Ywmax);

};

#endif
