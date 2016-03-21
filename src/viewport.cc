#include "viewport.h"

                                #include <iostream>

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

  // this->viewWindow->move_up(2);
  this->updateAllocation(this->get_allocation());

  // TODO cr = &cr;
  cr->set_line_width(2);


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

  // draw point at (10, 20) using window:
  int* point = this->convertCordinate(new int[2]{300, 200});
  cr->move_to(point[0],point[1]);
  cr->line_to(point[0]+1,point[1]+1);

  // draw line using window:
  int* line1 = this->convertCordinate(new int[2]{100, 230});
  int* line2 = this->convertCordinate(new int[2]{400, -60});
  cr->move_to(line1[0],line1[1]);
  cr->line_to(line2[0]+1,line2[1]+1);
//NOTE END TEST

  cr->stroke();

  return true;
}

int* Viewport::convertCordinate(int* cord) {
  int Xw = cord[0];
  int Xvp = ((this->Xvpmax - this->Xvpmin) /
             (this->viewWindow->getXwmax() - this->viewWindow->getXwmin()))
            * (Xw - this->viewWindow->getXwmin()) + this->Xvpmin;

            std::cout << Xw << " > " << Xvp << std::endl;
  int Yw = cord[1];
  int Yvp = (this->Yvpmax - this->Yvpmin) -
            (((this->Yvpmax - this->Yvpmin) /
              (this->viewWindow->getYwmax() - this->viewWindow->getYwmin()))
             * (Yw - this->viewWindow->getYwmin()) + this->Yvpmin);

            std::cout << Yw << " >> " << Yvp << std::endl;
  return new int[2] {Xvp, Yvp};
}

ViewWindow * Viewport::getViewWindow()
{
  return this->viewWindow;
}

void Viewport::updateAllocation(Gtk::Allocation allocation)
{

  if (this->Xvpmax != allocation.get_width() ||
      this->Yvpmax != allocation.get_height())
  {
    int widthDiff = allocation.get_width() - this->Xvpmax;
    int heightDiff = allocation.get_height() - this->Yvpmax;

    if (this->Xvpmax != 0)
    {
      this->viewWindow->setXwmax(this->viewWindow->getXwmax() +
                                 this->Xvpmax / (this->viewWindow->getXwmax()
                                  - this->viewWindow->getXwmin())
                                 * widthDiff);
    }
    else
    {
      this->viewWindow->setXwmax(widthDiff);
    }

    if (this->Yvpmax != 0)
    {
      this->viewWindow->setYwmin(this->viewWindow->getYwmin() -
                                 this->Yvpmax / (this->viewWindow->getYwmax()
                                  - this->viewWindow->getYwmin())
                                 * heightDiff);
    }
    else
    {
      this->viewWindow->setYwmax(heightDiff);
    }
    this->Xvpmax += widthDiff;
    this->Yvpmax += heightDiff;

    std::cout << ">>>>>>>>>>>" << this->viewWindow->getYwmin() << '|' << this->viewWindow->getXwmax() << std::endl;
  }

}

Viewport::~Viewport()
{
}
