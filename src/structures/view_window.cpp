#include "view_window.hpp"

ViewWindow::ViewWindow(int Xwmin, int Ywmin, int Xwmax, int Ywmax)
    : Xwmin(Xwmin),
      Ywmin(Ywmin),
      Xwmax(Xwmax),
      Ywmax(Ywmax),
      xVec(1,0,0),
      yVec(0,1,0),
      zVec(0,0,1),
      rotationX(0),
      rotationY(0),
      rotationZ(0),
      clippingType(clipping_type::DEFAULT_CLIPPING)
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
  this->Xwmin += yVec.getx() * length;
  this->Xwmax += yVec.getx() * length;
  this->Ywmin += yVec.gety() * length;
  this->Ywmax += yVec.gety() * length;
  this->windowZ += yVec.getz() * length;
}

void ViewWindow::move_down(int length)
{
  this->Xwmin -= yVec.getx() * length;
  this->Xwmax -= yVec.getx() * length;
  this->Ywmin -= yVec.gety() * length;
  this->Ywmax -= yVec.gety() * length;
  this->windowZ -= yVec.getz() * length;
}

void ViewWindow::move_left(int length)
{
  this->Xwmin -= xVec.getx() * length;
  this->Xwmax -= xVec.getx() * length;
  this->Ywmin -= xVec.gety() * length;
  this->Ywmax -= xVec.gety() * length;
  this->windowZ -= xVec.getz() * length;
}

void ViewWindow::move_right(int length)
{
  this->Xwmin += xVec.getx() * length;
  this->Xwmax += xVec.getx() * length;
  this->Ywmin += xVec.gety() * length;
  this->Ywmax += xVec.gety() * length;
  this->windowZ += xVec.getz() * length;
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

void ViewWindow::rotateX(int angle)
{
  double angleRad = angle * M_PI / 180;
  Matrix<double> rotateX(3,3);
  rotateX.set(0, 0, 1);
  rotateX.set(1, 1, cos(angleRad));
  rotateX.set(1, 2, -sin(angleRad));
  rotateX.set(2, 1, sin(angleRad));
  rotateX.set(2, 2, cos(angleRad));
  xVec = xVec.toMatrix() * rotateX;
  yVec = yVec.toMatrix() * rotateX;
  zVec = zVec.toMatrix() * rotateX;
  rotationX += angle;
}

void ViewWindow::rotateY(int angle)
{
  double angleRad = angle * M_PI / 180;
  Matrix<double> rotateY(3,3);
  rotateY.set(0, 0, cos(angleRad));
  rotateY.set(0, 2, sin(angleRad));
  rotateY.set(1, 1, 1);
  rotateY.set(2, 0, -sin(angleRad));
  rotateY.set(2, 2, cos(angleRad));
  xVec = xVec.toMatrix() * rotateY;
  yVec = yVec.toMatrix() * rotateY;
  zVec = zVec.toMatrix() * rotateY;
  rotationY += angle;
}

void ViewWindow::rotateZ(int angle)
{
  double angleRad = angle * M_PI / 180;
  Matrix<double> rotateZ(3,3);
  rotateZ.set(0, 0, cos(angleRad));
  rotateZ.set(0, 1, -sin(angleRad));
  rotateZ.set(1, 0, sin(angleRad));
  rotateZ.set(1, 1, cos(angleRad));
  rotateZ.set(2, 2, 1);
  xVec = xVec.toMatrix() * rotateZ;
  yVec = yVec.toMatrix() * rotateZ;
  zVec = zVec.toMatrix() * rotateZ;
  rotationZ += angle;
}

double ViewWindow::getRotationX()
{
  // double vx = zVec.getx();
  // double vy = zVec.gety();
  // double vz = zVec.getz();
  // double angleX = acos(vy / sqrt(vx*vx + vy*vy + vz*vz));
  // if (vz < 0)
  // {
  //   angleX *= -1;
  // }
  // return (M_PI / 2 - angleX) * 180 / M_PI;
  return rotationX;
}

double ViewWindow::getRotationY()
{
  // int angleX = getRotationX();
  // rotateX(angleX);
  // double vx = zVec.getx();
  // double vy = zVec.gety();
  // double vz = zVec.getz();
  // double angleY = acos(vx / sqrt(vx*vx + vy*vy + vz*vz));
  // if (vz < 0)
  // {
  //   angleY *= -1;
  // }
  // rotateX(-angleX);
  // return (M_PI / 2 - angleY) * 180 / M_PI;
  return rotationY;
}

double ViewWindow::getRotationZ()
{
  // int angleX = getRotationX();
  // int angleY = getRotationY();
  // rotateX(angleX);
  // rotateY(angleY);
  // double vx = yVec.getx();
  // double vy = yVec.gety();
  // double vz = yVec.getz();
  // double angleZ = acos(vx / sqrt(vx*vx + vy*vy + vz*vz));
  // if (vz < 0)
  // {
  //   angleZ *= -1;
  // }
  // rotateY(-angleY);
  // rotateX(-angleX);
  // return (M_PI / 2 - angleZ) * 180 / M_PI;
  return rotationZ;
}

clipping_type ViewWindow::getClippingType()
{
  return clippingType;
}
void ViewWindow::setClippingType(clipping_type clippingType)
{
  this->clippingType = clippingType;
}
