#ifndef GTKMM_APP_VIEW_WINDOW
#define GTKMM_APP_VIEW_WINDOW

class ViewWindow
{
public:
  ViewWindow(int Xwmin, int Ywmin, int Xwmax, int Ywmax);
  virtual ~ViewWindow();
  void zoom_in(float scale);
  void zoom_out(float scale);
  void move_up(unsigned int length);
  void move_down(unsigned int length);
  void move_left(unsigned int length);
  void move_right(unsigned int length);
  int getXwmin();
  int getYwmin();
  int getXwmax();
  int getYwmax();

protected:
  int Xwmin, Ywmin, Xwmax, Ywmax;

};

#endif
