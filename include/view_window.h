#ifndef GTKMM_APP_VIEW_WINDOW
#define GTKMM_APP_VIEW_WINDOW

class ViewWindow
{

  friend class Viewport;

public:
  ViewWindow(int Xwmin, int Ywmin, int Xwmax, int Ywmax);
  virtual ~ViewWindow();
  void zoom_in(float scale = 2);
  void zoom_out(float scale = 2);
  void move_up(unsigned int length = 10);
  void move_down(unsigned int length = 10);
  void move_left(unsigned int length = 10);
  void move_right(unsigned int length = 10);

protected:
  int Xwmin, Ywmin, Xwmax, Ywmax;
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
