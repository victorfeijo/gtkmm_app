#include "view_window.hpp"

ViewWindow::ViewWindow(int Xwmin, int Ywmin, int Xwmax, int Ywmax)
    : Xwmin(Xwmin),
      Ywmin(Ywmin),
      Xwmax(Xwmax),
      Ywmax(Ywmax),
      rotationX(0),
      rotationY(0),
      rotationZ(0),
      clippingType(clipping_type::DEFAULT_CLIPPING)
{
}

void ViewWindow::zoom_in(double scale)
{
  if (scale < 1) { return; }

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

void ViewWindow::zoom_out(double scale)
{
  if (scale < 1) { return; }

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

void ViewWindow::move_up(int length)
{
  this->Xwmin += getYVec().getx() * length;
  this->Xwmax += getYVec().getx() * length;
  this->Ywmin += getYVec().gety() * length;
  this->Ywmax += getYVec().gety() * length;
  this->windowZ += getYVec().getz() * length;
}

void ViewWindow::move_down(int length)
{
  this->Xwmin -= getYVec().getx() * length;
  this->Xwmax -= getYVec().getx() * length;
  this->Ywmin -= getYVec().gety() * length;
  this->Ywmax -= getYVec().gety() * length;
  this->windowZ -= getYVec().getz() * length;
}

void ViewWindow::move_left(int length)
{
  this->Xwmin -= getXVec().getx() * length;
  this->Xwmax -= getXVec().getx() * length;
  this->Ywmin -= getXVec().gety() * length;
  this->Ywmax -= getXVec().gety() * length;
  this->windowZ -= getXVec().getz() * length;
}

void ViewWindow::move_right(int length)
{
  this->Xwmin += getXVec().getx() * length;
  this->Xwmax += getXVec().getx() * length;
  this->Ywmin += getXVec().gety() * length;
  this->Ywmax += getXVec().gety() * length;
  this->windowZ += getXVec().getz() * length;
}

void ViewWindow::move_out(int length)
{
  this->Xwmin -= getZVec().getx() * length;
  this->Xwmax -= getZVec().getx() * length;
  this->Ywmin -= getZVec().gety() * length;
  this->Ywmax -= getZVec().gety() * length;
  this->windowZ -= getZVec().getz() * length;
}

void ViewWindow::move_in(int length)
{
  this->Xwmin += getZVec().getx() * length;
  this->Xwmax += getZVec().getx() * length;
  this->Ywmin += getZVec().gety() * length;
  this->Ywmax += getZVec().gety() * length;
  this->windowZ += getZVec().getz() * length;
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
  return Coordinate((Xwmax+Xwmin)/2, (Ywmin+Ywmax)/2, windowZ);
}

Coordinate ViewWindow::rotateVecX(Coordinate vec, int angle)
{
  double angleRad = angle * M_PI / 180;
  Matrix<double> rotateX(3,3);
  rotateX.set(0, 0, 1);
  rotateX.set(1, 1, cos(angleRad));
  rotateX.set(1, 2, -sin(angleRad));
  rotateX.set(2, 1, sin(angleRad));
  rotateX.set(2, 2, cos(angleRad));

  return vec.toMatrix() * rotateX;
}

Coordinate ViewWindow::rotateVecY(Coordinate vec, int angle)
{
  double angleRad = angle * M_PI / 180;
  Matrix<double> rotateY(3,3);
  rotateY.set(0, 0, cos(angleRad));
  rotateY.set(0, 2, sin(angleRad));
  rotateY.set(1, 1, 1);
  rotateY.set(2, 0, -sin(angleRad));
  rotateY.set(2, 2, cos(angleRad));

  return vec.toMatrix() * rotateY;
}

Coordinate ViewWindow::rotateVecZ(Coordinate vec, int angle)
{
  double angleRad = angle * M_PI / 180;
  Matrix<double> rotateZ(3,3);
  rotateZ.set(0, 0, cos(angleRad));
  rotateZ.set(0, 1, -sin(angleRad));
  rotateZ.set(1, 0, sin(angleRad));
  rotateZ.set(1, 1, cos(angleRad));
  rotateZ.set(2, 2, 1);

  return vec.toMatrix() * rotateZ;
}

void ViewWindow::rotateX(int angle)
{
  rotationX += angle;
}

void ViewWindow::rotateY(int angle)
{
  rotationY += angle;
}

void ViewWindow::rotateZ(int angle)
{
  rotationZ += angle;
}

double ViewWindow::getRotationX()
{
  return rotationX;
}

double ViewWindow::getRotationY()
{
  return rotationY;
}

double ViewWindow::getRotationZ()
{
  return rotationZ;
}

Coordinate ViewWindow::getXVec()
{
  Coordinate xVec(1,0,0);
  xVec = rotateVecX(xVec, -getRotationX());
  xVec = rotateVecY(xVec, -getRotationY());
  xVec = rotateVecZ(xVec, -getRotationZ());

  return xVec;
}

Coordinate ViewWindow::getYVec()
{
  Coordinate yVec(0,1,0);
  yVec = rotateVecX(yVec, -getRotationX());
  yVec = rotateVecY(yVec, -getRotationY());
  yVec = rotateVecZ(yVec, -getRotationZ());

  return yVec;
}

Coordinate ViewWindow::getZVec()
{
  Coordinate zVec(0,0,1);
  zVec = rotateVecX(zVec, -getRotationX());
  zVec = rotateVecY(zVec, -getRotationY());
  zVec = rotateVecZ(zVec, -getRotationZ());

  return zVec;
}

clipping_type ViewWindow::getClippingType()
{
  return clippingType;
}
void ViewWindow::setClippingType(clipping_type clippingType)
{
  this->clippingType = clippingType;
}
