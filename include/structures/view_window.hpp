#ifndef GTKMM_APP_VIEW_WINDOW
#define GTKMM_APP_VIEW_WINDOW

#include "display_file.hpp"
#include "rotate_object_service.hpp"
#include "clipping_type.hpp"

#define MIN_WIDTH 15
#define MIN_HEIGHT 15
#define MAX_HEIGHT 50000000
#define MAX_WIDTH 50000000

class ViewWindow
{

public:
  ViewWindow(int Xwmin, int Ywmin, int Xwmax, int Ywmax);
  virtual ~ViewWindow();
  void zoom_in(double scale = 1.5);
  void zoom_out(double scale = 1.5);
  void move_up(int length = 10);
  void move_down(int length = 10);
  void move_left(int length = 10);
  void move_right(int length = 10);
  DisplayFile* getDisplayFile();
  double getXwmin();
  double getYwmin();
  double getXwmax();
  double getYwmax();
  void setXwmin(double Xwmin);
  void setYwmin(double Ywmin);
  void setXwmax(double Xwmax);
  void setYwmax(double Ywmax);
  Coordinate getCenter();
  void rotate(int angle);
  int getRotation();
  clipping_type getClippingType();
  void setClippingType(clipping_type clippingType);

protected:
  DisplayFile displayFile;
  double Xwmin, Ywmin, Xwmax, Ywmax;
  int rotationAngle;
  Coordinate viewUp();
  RotateObjectService rotateService;
  clipping_type clippingType;
  
};

#endif
