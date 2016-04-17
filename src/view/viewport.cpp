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

int Viewport::getXvpmin()
{
  return this->Xvpmin;
}
int Viewport::getYvpmin()
{
  return this->Yvpmin;
}
int Viewport::getXvpmax()
{
  return this->Xvpmax;
}
int Viewport::getYvpmax()
{
  return this->Yvpmax;
}
void Viewport::setXvpmin(int Xvpmin)
{
  this->Xvpmin = Xvpmin;
}
void Viewport::setYvpmin(int Yvpmin)
{
  this->Yvpmin = Yvpmin;
}
void Viewport::setXvpmax(int Xvpmax)
{
  this->Xvpmax = Xvpmax;
}
void Viewport::setYvpmax(int Yvpmax)
{
  this->Yvpmax = Yvpmax;
}



Viewport::~Viewport()
{
}
