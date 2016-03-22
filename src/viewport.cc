#include "viewport.h"

Viewport::Viewport()
    : viewWindow(new ViewWindow (0, 0, 0, 0)),
      Xvpmin(0),
      Yvpmin(0),
      Xvpmax(0),
      Yvpmax(0)
{
  // NOTE TESTS USING DISPLAY_FILE AND OBJECTS
  viewWindow->getDisplayFile()->addObject(new Point("ponto1", new Coordinate(20,30)));
  viewWindow->getDisplayFile()->addObject(new Rect("reta1", new Coordinate(432,58), new Coordinate(89,355)));
  list<Coordinate*> coordinates;
  coordinates.push_back(new Coordinate(100,100));
  coordinates.push_back(new Coordinate(200,100));
  coordinates.push_back(new Coordinate(200,200));
  coordinates.push_back(new Coordinate(300,300));
  viewWindow->getDisplayFile()->addObject(new WireFrame("wire1", coordinates));
  // NOTE END TESTS
}

bool Viewport::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{

  // this->viewWindow->move_up(2);
  this->updateAllocation(this->get_allocation());

  cr->set_line_width(2);


  // paint white background
  cr->set_source_rgb(1, 1, 1);
  cr->paint();

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
    }
  }
  cr->stroke();

  return true;
}

Coordinate Viewport::convertCoordinateFromWindow(Coordinate cord) {
  int Xw = cord.getx();
  int Xvp = ((this->Xvpmax - this->Xvpmin) /
             (this->viewWindow->getXwmax() - this->viewWindow->getXwmin()))
            * (Xw - this->viewWindow->getXwmin()) + this->Xvpmin;

  int Yw = cord.gety();
  int Yvp = (this->Yvpmax - this->Yvpmin) -
            (((this->Yvpmax - this->Yvpmin) /
              (this->viewWindow->getYwmax() - this->viewWindow->getYwmin()))
             * (Yw - this->viewWindow->getYwmin()) + this->Yvpmin);


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

  }

}

Viewport::~Viewport()
{
}
