#include "viewport.hpp"

Viewport::Viewport()
    : viewWindow(new ViewWindow (0, 0, 0, 0)),
      Xvpmin(0),
      Yvpmin(0),
      Xvpmax(0),
      Yvpmax(0)
{
}

bool Viewport::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  DrawViewportService drawViewport;
  drawViewport.draw(cr, this);

  return true;
}

ViewWindow * Viewport::getViewWindow()
{
  return this->viewWindow;
}

double Viewport::getXvpmin()
{
  return this->Xvpmin;
}
double Viewport::getYvpmin()
{
  return this->Yvpmin;
}
double Viewport::getXvpmax()
{
  return this->Xvpmax;
}
double Viewport::getYvpmax()
{
  return this->Yvpmax;
}
void Viewport::setXvpmin(double Xvpmin)
{
  this->Xvpmin = Xvpmin;
}
void Viewport::setYvpmin(double Yvpmin)
{
  this->Yvpmin = Yvpmin;
}
void Viewport::setXvpmax(double Xvpmax)
{
  this->Xvpmax = Xvpmax;
}
void Viewport::setYvpmax(double Yvpmax)
{
  this->Yvpmax = Yvpmax;
}



Viewport::~Viewport()
{
}
