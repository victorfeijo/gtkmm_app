#ifndef GTKMM_APP_VIEW_WINDOW
#define GTKMM_APP_VIEW_WINDOW

#include "display_file.hpp"

#define MIN_WIDTH 15
#define MIN_HEIGHT 15
#define MAX_HEIGHT 50000000
#define MAX_WIDTH 50000000

class ViewWindow
{

  friend class Viewport;

public:
  ViewWindow(int Xwmin, int Ywmin, int Xwmax, int Ywmax);
  virtual ~ViewWindow();
  void zoom_in(float scale = 1.5);
  void zoom_out(float scale = 1.5);
  void move_up(int length = 10);
  void move_down(int length = 10);
  void move_left(int length = 10);
  void move_right(int length = 10);
  DisplayFile* getDisplayFile();

protected:
  DisplayFile displayFile;
  float Xwmin, Ywmin, Xwmax, Ywmax;
  float getXwmin();
  float getYwmin();
  float getXwmax();
  float getYwmax();
  void setXwmin(float Xwmin);
  void setYwmin(float Ywmin);
  void setXwmax(float Xwmax);
  void setYwmax(float Ywmax);

};

#endif
