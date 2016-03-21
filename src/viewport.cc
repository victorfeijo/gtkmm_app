#include "viewport.h"

                          #include <iostream>

Viewport::Viewport()
    : Xvpmin(0), Yvpmin(0), Xvpmax(0), Yvpmax(0)
{
}

bool Viewport::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  // TODO cr = &cr;
  cr->set_line_width(2);

  if (this->viewWindow == NULL)
  {
    Gtk::Allocation allocation = this->get_allocation();
    this->Xvpmax = allocation.get_width();
    this->Yvpmax = allocation.get_height();
    if(this->Xvpmax > 10 && this->Yvpmax > 10)
    {
      this->viewWindow = new ViewWindow(this->Xvpmin, this->Yvpmin,
                                        this->Xvpmax, this->Yvpmax);
    }
  }
  else
  {
    Gtk::Allocation allocation = this->get_allocation();
    // TODO update viewport and viewwindow sizes
  }

  // paint white background
  cr->set_source_rgb(1, 1, 1);
  cr->paint();

  cr->set_source_rgb(0.8, 0, 0);
  // draw viewport corners
  cr->move_to(0,0);
  cr->line_to(this->Xvpmax,0);
  cr->line_to(this->Xvpmax,this->Yvpmax);
  cr->line_to(0,this->Yvpmax);
  cr->line_to(0,0);
  cr->stroke();

  // set color as black:
  cr->set_source_rgb(0, 0, 0);

  // TODO draw objects
  // FOREACH OBJECT
  //   cr->move_to(this->convertCordinates(OBJECT->FIRSTCORDINATE)
  //   FOREACH OBJECT->COORDINATE
  //     cr->line_to(this->convertCordinates(OBJECT_CORDINATE)
  //   endfor
  //   IF (OBJECT->CORDINATES->SIZE === 1)
  //     cr->line_to(this->convertCordinates(OBJECT_CORDINATE) + (1,1))
  //   endif
  //   cr->stroke();

//NOTE BEGIN TEST:
  const int width = this->Xvpmax;
  const int height = this->Yvpmax;
  // coordinates for the center of the window
  int xc, yc;
  xc = width / 2;
  yc = height / 2;

  // draw lines out from the center of the window
  cr->move_to(0, 0);
  cr->line_to(xc, yc);
  cr->line_to(0, height);
  cr->move_to(xc, yc);
  cr->line_to(width, yc);

  // draw point at (10, 20):
  cr->move_to(10,20);
  cr->line_to(11,21);
//NOTE END TEST

  cr->stroke();

  return true;
}

int* Viewport::convertCordinate(int* cord) {
  int Xw = cord[0];
  int Xvp = (Xw - this->viewWindow->getXwmin()) /
            (this->viewWindow->getXwmax() - this->viewWindow->getXwmin())
            * (this->Xvpmax - this->Xvpmin);

  int Yw = cord[1];
  int Yvp = (1 - (Yw - this->viewWindow->getYwmin()) /
                 (this->viewWindow->getYwmax() - this->viewWindow->getYwmin()))
            *  (this->Yvpmax - this->Yvpmin);

  return new int[2] {Xvp, Yvp};
}

ViewWindow * Viewport::getViewWindow()
{
  return this->viewWindow;
}

Viewport::~Viewport()
{
}
