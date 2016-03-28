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

  // resize viewwindow when viewport is resized
  this->updateAllocation(this->get_allocation());

  // paint white background
  cr->set_source_rgb(1, 1, 1);
  cr->paint();

  // draw origin
  cr->set_line_width(2);
  cr->set_source_rgb(0.4, 0.4, 1);
  Coordinate originOnWindow = convertCoordinateFromWindow(Coordinate(0, 0));
  cr->move_to(originOnWindow.getx()-5, originOnWindow.gety());
  cr->line_to(originOnWindow.getx()+5, originOnWindow.gety());
  cr->move_to(originOnWindow.getx(), originOnWindow.gety()-5);
  cr->line_to(originOnWindow.getx(), originOnWindow.gety()+5);
  cr->stroke();
  cr->set_line_width(2);

  // draw viewport corners (red)
  cr->set_source_rgb(0.8, 0, 0);
  cr->move_to(0,0);
  cr->line_to(this->Xvpmax,0);
  cr->line_to(this->Xvpmax,this->Yvpmax);
  cr->line_to(0,this->Yvpmax);
  cr->line_to(0,0);
  cr->stroke();


  // set color as black:
  cr->set_source_rgb(0, 0, 0);

  // draw displayfile objects
  std::list<DrawableObject*> objects = this->viewWindow->getDisplayFile()
                              ->getObjects();
  for (std::list<DrawableObject*>::iterator it_obj = objects.begin();
        it_obj != objects.end(); it_obj++)
  {
    list<Coordinate*> objectCoordinates = (*it_obj)->getCoordinates();
    Coordinate firstCordConverted = this->convertCoordinateFromWindow(
                                          **(objectCoordinates.begin()));
    cr->move_to(firstCordConverted.getx(),firstCordConverted.gety());

    if (objectCoordinates.size() == 1) {  // point case
      cr->line_to(firstCordConverted.getx()+1,firstCordConverted.gety()+1);
    }
    else
    {
      for (std::list<Coordinate*>::iterator it_cord = objectCoordinates.begin();
            it_cord != objectCoordinates.end(); it_cord++)
      {
        Coordinate cordConverted = this->convertCoordinateFromWindow(**it_cord);
        cr->line_to(cordConverted.getx(),cordConverted.gety());
      }
      cr->line_to(firstCordConverted.getx(),firstCordConverted.gety());
    }
  }
  cr->stroke();

  return true;
}

Coordinate Viewport::convertCoordinateFromWindow(Coordinate cord) {
  long int Xw = cord.getx();
  long int Xvp = (long int)(((double)(this->Xvpmax - this->Xvpmin) /
            (double)(this->viewWindow->getXwmax() - this->viewWindow->getXwmin()))
            * (double)(Xw - this->viewWindow->getXwmin()) + this->Xvpmin);

  long int Yw = cord.gety();
  long int Yvp = (this->Yvpmax - this->Yvpmin) -
            (long int)(((double)(this->Yvpmax - this->Yvpmin) /
            (double)(this->viewWindow->getYwmax() - this->viewWindow->getYwmin()))
            * (double)(Yw - this->viewWindow->getYwmin()) + this->Yvpmin);

  return Coordinate(Xvp, Yvp);
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
    int widthDiff = allocation.get_width() - (this->Xvpmax - this->Xvpmin);
    int heightDiff = allocation.get_height() - (this->Yvpmax - this->Yvpmin);

    if (this->Xvpmax != 0)
    {
      this->viewWindow->setXwmax(this->viewWindow->getXwmax() +
                                 (float)(this->viewWindow->getXwmax()
                                  - this->viewWindow->getXwmin())
                                 * (float)widthDiff
                                 / (float)(this->Xvpmax - this->Xvpmin));
    }
    else
    {
      this->viewWindow->setXwmax(widthDiff*2);
    }

    if (this->Yvpmax != 0)
    {
      this->viewWindow->setYwmin(this->viewWindow->getYwmin() -
                                 (float)(this->viewWindow->getYwmax()
                                  - this->viewWindow->getYwmin())
                                 * (float)heightDiff
                                 / (float)(this->Yvpmax - this->Yvpmin));
    }
    else
    {
      this->viewWindow->setYwmax(heightDiff*2);
    }
    this->Xvpmax += widthDiff;
    this->Yvpmax += heightDiff;

  }

}

Viewport::~Viewport()
{
}
