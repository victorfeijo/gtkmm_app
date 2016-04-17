#include "view_window.hpp"

ViewWindow::ViewWindow(int Xwmin, int Ywmin, int Xwmax, int Ywmax)
    : Xwmin(Xwmin),
      Ywmin(Ywmin),
      Xwmax(Xwmax),
      Ywmax(Ywmax),
      rotationAngle(0),
      clippingType(clipping_type::POINT)
{
}

void ViewWindow::zoom_in(double scale)
{
  if (scale < 1)
  {
    return;
  }
  else
  {
    double width = this->Xwmax - this->Xwmin;
    double height = this->Ywmax - this->Ywmin;
    double newXwmin = Xwmin + (width - (width / scale)) / 2;
    double newXwmax = Xwmax - (width - (width / scale)) / 2;
    double newYwmin = Ywmin + (height - (height / scale)) / 2;
    double newYwmax = Ywmax - (height - (height/ scale)) / 2;
    if ((newXwmax - newXwmin) < MIN_WIDTH || (newYwmax - newYwmin) < MIN_HEIGHT)
    {
      return;
    }
    else{
      this->Xwmin = newXwmin;
      this->Xwmax = newXwmax;
      this->Ywmin = newYwmin;
      this->Ywmax = newYwmax;
    }
  }
}

void ViewWindow::zoom_out(double scale)
{
  if (scale < 1)
  {
    return;
  }
  else
  {
    double width = this->Xwmax - this->Xwmin;
    double height = this->Ywmax - this->Ywmin;
    double newXwmin = Xwmin - ((width * scale) - width) / 2;
    double newXwmax = Xwmax + ((width * scale) - width) / 2;
    double newYwmin = Ywmin - ((height * scale) - height) / 2;
    double newYwmax = Ywmax + ((height * scale) - height) / 2;
    if ((newXwmax - newXwmin) > MAX_WIDTH || (newYwmax - newYwmin) > MAX_HEIGHT)
    {
      return;
    }
    else{
      this->Xwmin = newXwmin;
      this->Xwmax = newXwmax;
      this->Ywmin = newYwmin;
      this->Ywmax = newYwmax;
    }
  }
}

void ViewWindow::move_up(int length)
{
  Coordinate viewUp = this->viewUp();
  this->Ywmin += viewUp.gety() * length;
  this->Ywmax += viewUp.gety() * length;
  this->Xwmin += viewUp.getx() * length;
  this->Xwmax += viewUp.getx() * length;
}

void ViewWindow::move_down(int length)
{
  Coordinate viewUp = this->viewUp();
  this->Ywmin -= viewUp.gety() * length;
  this->Ywmax -= viewUp.gety() * length;
  this->Xwmin -= viewUp.getx() * length;
  this->Xwmax -= viewUp.getx() * length;
}

void ViewWindow::move_left(int length)
{
  Coordinate viewUp = this->viewUp();
  this->Ywmin += viewUp.getx() * length;
  this->Ywmax += viewUp.getx() * length;
  this->Xwmin -= viewUp.gety() * length;
  this->Xwmax -= viewUp.gety() * length;
}

void ViewWindow::move_right(int length)
{
  Coordinate viewUp = this->viewUp();
  this->Ywmin -= viewUp.getx() * length;
  this->Ywmax -= viewUp.getx() * length;
  this->Xwmin += viewUp.gety() * length;
  this->Xwmax += viewUp.gety() * length;
}

double ViewWindow::getXwmin()
{
  return this->Xwmin;
}

double ViewWindow::getYwmin()
{
  return this->Ywmin;
}

double ViewWindow::getXwmax()
{
  return this->Xwmax;
}

double ViewWindow::getYwmax()
{
  return this->Ywmax;
}

void ViewWindow::setXwmin(double Xwmin)
{
  this->Xwmin = Xwmin;
}

void ViewWindow::setYwmin(double Ywmin)
{
  this->Ywmin = Ywmin;
}

void ViewWindow::setXwmax(double Xwmax)
{
  this->Xwmax = Xwmax;
}

void ViewWindow::setYwmax(double Ywmax)
{
  this->Ywmax = Ywmax;
}

DisplayFile* ViewWindow::getDisplayFile()
{
  return &this->displayFile;
}

ViewWindow::~ViewWindow()
{
}

Coordinate ViewWindow::getCenter()
{
  return Coordinate((Xwmax+Xwmin)/2, (Ywmin+Ywmax)/2);
}

void ViewWindow::rotate(int angle)
{
  this->rotationAngle += angle;
}

int ViewWindow::getRotation()
{
  return this->rotationAngle;
}

Coordinate ViewWindow::viewUp()
{
  Matrix<double> up(1,3);
  up.set(0, 0, 0);
  up.set(0, 1, 1);
  up.set(0, 2, 0);

  double angleRad = -this->rotationAngle * M_PI / 180;
  Matrix<double> angle(3,3);
  angle.set(0, 0, cos(angleRad));
  angle.set(0, 1, -sin(angleRad));
  angle.set(1, 0, sin(angleRad));
  angle.set(1, 1, cos(angleRad));
  angle.set(2, 2, 1);

  Matrix<double> upRotated = up * angle;

  return Coordinate(upRotated.get(0,0), upRotated.get(0,1));
}

clipping_type ViewWindow::getClippingType()
{
  return clippingType;
}
void ViewWindow::setClippingType(clipping_type clippingType)
{
  this->clippingType = clippingType;
}
