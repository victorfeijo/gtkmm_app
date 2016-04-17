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
  cr->set_source_rgb(WHITE);
  cr->move_to(viewport->getXvpmin(),viewport->getYvpmin());
  cr->line_to(viewport->getXvpmax(),viewport->getYvpmin());
  cr->line_to(viewport->getXvpmax(),viewport->getYvpmax());
  cr->line_to(viewport->getXvpmin(),viewport->getYvpmax());
  cr->close_path();
  cr->fill_preserve();

  // draw viewport corners
  cr->set_line_width(2);
  cr->set_source_rgb(RED);
  cr->move_to(viewport->getXvpmin(),viewport->getYvpmin());
  cr->line_to(viewport->getXvpmax(),viewport->getYvpmin());
  cr->line_to(viewport->getXvpmax(),viewport->getYvpmax());
  cr->line_to(viewport->getXvpmin(),viewport->getYvpmax());
  cr->close_path();
  cr->stroke();

  // set color as black:
  cr->set_source_rgb(BLACK);

  // draw displayfile objects
  DisplayFile* displayFile = viewport->getViewWindow()->getDisplayFile();
  Coordinate windowCenter = viewport->getViewWindow()->getCenter();
  int windowAngle = viewport->getViewWindow()->getRotation();
  std::list<DrawableObject*> objectsList = displayFile->getObjects();

  for (DrawableObject* object : objectsList)
  {
    cr->begin_new_sub_path();
    rotate_service.rotate(object, windowCenter.getx(), windowCenter.gety(),
                          windowAngle, transform_type::ON_WINDOW);
    clipping_service.clip(viewport->getViewWindow(), object);
    list<Coordinate> objectCoordinates = object->getCoordinatesClipped();
    Coordinate firstCordConverted = convertFromWindowToViewport(
                                      *(objectCoordinates.begin()), viewport);

    cr->move_to(firstCordConverted.getx(),firstCordConverted.gety());
    if (objectCoordinates.size() == 1)  // point case
    {
      cr->line_to(firstCordConverted.getx()+1,firstCordConverted.gety()+1);
    }
    else
    {
      for (Coordinate coordinate : objectCoordinates)
      {
        Coordinate cordConverted = convertFromWindowToViewport(coordinate, viewport);
        cr->line_to(cordConverted.getx(),cordConverted.gety());
      }
      if (objectCoordinates.size() > 2) // wireframe case
      {
        cr->close_path();
        // fill polygon
        cr->fill_preserve();
        cr->restore();
        cr->stroke_preserve();
        cr->clip();
      }
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
  long int Yvp = (viewport->getYvpmax() + viewport->getYvpmin()) -
            (long int)(((double)(viewport->getYvpmax() - viewport->getYvpmin()) /
            (double)(viewWindow->getYwmax() - viewWindow->getYwmin()))
            * (double)(Yw - viewWindow->getYwmin()) + viewport->getYvpmin());

  return Coordinate(Xvp, Yvp);
}

void DrawViewportService::updateViewportAllocation(Gtk::Allocation allocation, Viewport* viewport)
{
  viewport->setXvpmin(BORDER);
  viewport->setYvpmin(BORDER);

  if (viewport->getXvpmax() != allocation.get_width() ||
      viewport->getYvpmax() != allocation.get_height())
  {
    int widthDiff = allocation.get_width()-2*BORDER - (viewport->getXvpmax() - viewport->getXvpmin());
    int heightDiff = allocation.get_height()-2*BORDER - (viewport->getYvpmax() - viewport->getYvpmin());

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
      viewWindow->setXwmax(widthDiff*DEFAULT_ZOOM);
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
      viewWindow->setYwmax(heightDiff*DEFAULT_ZOOM);
    }
    viewport->setXvpmax(viewport->getXvpmax() + widthDiff);
    viewport->setYvpmax(viewport->getYvpmax() + heightDiff);

  }

  viewport->set_allocation(allocation);

}
