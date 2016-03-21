#include "view_window.h"

ViewWindow::ViewWindow(int Xwmin, int Ywmin, int Xwmax, int Ywmax)
    : Xwmin(Xwmin),
      Ywmin(Ywmin),
      Xwmax(Xwmax),
      Ywmax(Ywmax)
{
}

void ViewWindow::zoom_in(float scale)
{
  if (scale < 1)
  {
    return;
  }
  else
  {
    int width = this->Xwmax - this->Xwmin;
    int height = this->Ywmax - this->Ywmin;
    this->Xwmin += (width - (width / scale)) / 2;
    this->Xwmax -= (width - (width / scale)) / 2;
    this->Ywmin += (height - (height / scale)) / 2;
    this->Ywmax -= (height - (height/ scale)) / 2;
  }
}

void ViewWindow::zoom_out(float scale)
{
  if (scale < 1)
  {
    return;
  }
  else
  {
    int width = this->Xwmax - this->Xwmin;
    int height = this->Ywmax - this->Ywmin;
    this->Xwmin -= ((width * scale) - width) / 2;
    this->Xwmax += ((width * scale) - width) / 2;
    this->Ywmin -= ((height * scale) - height) / 2;
    this->Ywmax += ((height * scale) - height) / 2;
  }
}

void ViewWindow::move_up(unsigned int length)
{
  this->Ywmin -= length;
  this->Ywmax -= length;
}

void ViewWindow::move_down(unsigned int length)
{
  this->Ywmin += length;
  this->Ywmax += length;
}

void ViewWindow::move_left(unsigned int length)
{
  this->Xwmin -= length;
  this->Xwmax -= length;
}

void ViewWindow::move_right(unsigned int length)
{
  this->Xwmin += length;
  this->Xwmax += length;
}

int ViewWindow::getXwmin()
{
  return this->Xwmin;
}

int ViewWindow::getYwmin()
{
  return this->Ywmin;
}

int ViewWindow::getXwmax()
{
  return this->Xwmax;
}

int ViewWindow::getYwmax()
{
  return this->Ywmax;
}

void ViewWindow::setXwmin(int Xwmin)
{
  this->Xwmin = Xwmin;
}

void ViewWindow::setYwmin(int Ywmin)
{
  this->Ywmin = Ywmin;
}

void ViewWindow::setXwmax(int Xwmax)
{
  this->Xwmax = Xwmax;
}

void ViewWindow::setYwmax(int Ywmax)
{
  this->Ywmax = Ywmax;
}

ViewWindow::~ViewWindow()
{
}
