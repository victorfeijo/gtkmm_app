#include "draw_viewport_service.hpp"
#include "viewport.hpp"

DrawViewportService::DrawViewportService()
{
}

DrawViewportService::~DrawViewportService()
{
}

void DrawViewportService::draw(const Cairo::RefPtr<Cairo::Context>& cr, Viewport* viewport)
{
  // resize viewwindow when viewport is resized
  updateViewportAllocation(viewport->get_allocation(), viewport);

  // paint white background
  cr->set_source_rgb(1, 1, 1);
  cr->paint();

  // draw viewport corners (red)
  cr->set_source_rgb(0.8, 0, 0);
  cr->move_to(0,0);
  cr->line_to(viewport->getXvpmax(),0);
  cr->line_to(viewport->getXvpmax(),viewport->getYvpmax());
  cr->line_to(0,viewport->getYvpmax());
  cr->line_to(0,0);
  cr->stroke();

  // set color as black:
  cr->set_source_rgb(0, 0, 0);

  // draw displayfile objects
  DisplayFile* displayFile = viewport->getViewWindow()->getDisplayFile();
  Coordinate windowCenter = viewport->getViewWindow()->getCenter();
  int windowAngle = viewport->getViewWindow()->getRotation();
  std::list<DrawableObject*> objects = displayFile->getObjects();
  for (std::list<DrawableObject*>::iterator it_obj = objects.begin();
        it_obj != objects.end(); ++it_obj)
  {
    (*it_obj)->copyFromWorldToWindow();
    rotate_service.rotate(*it_obj, windowCenter.getx(), windowCenter.gety(),
                          windowAngle, transform_type::ON_WINDOW);
    list<Coordinate> objectCoordinates = (*it_obj)->getCoordinatesWindow();
    Coordinate firstCordConverted = convertFromWindowToViewport(
                                      *(objectCoordinates.begin()), viewport);
    cr->move_to(firstCordConverted.getx(),firstCordConverted.gety());

    if (objectCoordinates.size() == 1)  // point case
    {
      cr->line_to(firstCordConverted.getx()+1,firstCordConverted.gety()+1);
    }
    else
    {
      for (std::list<Coordinate>::iterator it_cord = objectCoordinates.begin();
            it_cord != objectCoordinates.end(); ++it_cord)
      {
        Coordinate cordConverted = convertFromWindowToViewport(*it_cord,
                                                               viewport);
        cr->line_to(cordConverted.getx(),cordConverted.gety());
      }
      cr->line_to(firstCordConverted.getx(),firstCordConverted.gety());
    }
  }
  cr->stroke();
}

Coordinate DrawViewportService::convertFromWindowToViewport(Coordinate cord, Viewport* viewport)
{
  ViewWindow* viewWindow = viewport->getViewWindow();
  long int Xw = cord.getx();
  long int Xvp = (long int)(((double)(viewport->getXvpmax() - viewport->getXvpmin()) /
            (double)(viewWindow->getXwmax() - viewWindow->getXwmin()))
            * (double)(Xw - viewWindow->getXwmin()) + viewport->getXvpmin());

  long int Yw = cord.gety();
  long int Yvp = (viewport->getYvpmax() - viewport->getYvpmin()) -
            (long int)(((double)(viewport->getYvpmax() - viewport->getYvpmin()) /
            (double)(viewWindow->getYwmax() - viewWindow->getYwmin()))
            * (double)(Yw - viewWindow->getYwmin()) + viewport->getYvpmin());

  return Coordinate(Xvp, Yvp);
}

void DrawViewportService::updateViewportAllocation(Gtk::Allocation allocation, Viewport* viewport)
{

  if (viewport->getXvpmax() != allocation.get_width() ||
      viewport->getYvpmax() != allocation.get_height())
  {
    int widthDiff = allocation.get_width() - (viewport->getXvpmax() - viewport->getXvpmin());
    int heightDiff = allocation.get_height() - (viewport->getYvpmax() - viewport->getYvpmin());

    ViewWindow* viewWindow = viewport->getViewWindow();

    if (viewport->getXvpmax() != 0)
    {
      viewWindow->setXwmax(viewWindow->getXwmax() +
                           (float)(viewWindow->getXwmax()
                            - viewWindow->getXwmin())
                           * (float)widthDiff
                           / (float)(viewport->getXvpmax()
                            - viewport->getXvpmin()));
    }
    else
    {
      viewWindow->setXwmax(widthDiff*2);
    }

    if (viewport->getYvpmax() != 0)
    {
      viewWindow->setYwmin(viewWindow->getYwmin() -
                           (float)(viewWindow->getYwmax()
                            - viewWindow->getYwmin())
                           * (float)heightDiff
                           / (float)(viewport->getYvpmax()
                            - viewport->getYvpmin()));
    }
    else
    {
      viewWindow->setYwmax(heightDiff*2);
    }
    viewport->setXvpmax(viewport->getXvpmax() + widthDiff);
    viewport->setYvpmax(viewport->getYvpmax() + heightDiff);

  }

}
