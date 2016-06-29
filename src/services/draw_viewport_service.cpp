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
  cr->set_source_rgb(RED);
  cr->move_to(viewport->getXvpmin(),viewport->getYvpmin());
  cr->line_to(viewport->getXvpmax(),viewport->getYvpmin());
  cr->line_to(viewport->getXvpmax(),viewport->getYvpmax());
  cr->line_to(viewport->getXvpmin(),viewport->getYvpmax());
  cr->close_path();
  cr->stroke_preserve();
  cr->fill();

  // set color as black:
  cr->set_source_rgb(BLACK);

  // draw displayfile objects
  DisplayFile* displayFile = viewport->getViewWindow()->getDisplayFile();
  Coordinate windowCenter = viewport->getViewWindow()->getCenter();
  int windowAngleX = viewport->getViewWindow()->getRotationX();
  int windowAngleY = viewport->getViewWindow()->getRotationY();
  int windowAngleZ = viewport->getViewWindow()->getRotationZ();
  list<DrawableObject*> objectsList = displayFile->getObjects();

  for (DrawableObject* object : objectsList)
  {
    object->resetWindowCoordinates();
    rotate_service.rotateX(object, windowCenter.getx(), windowCenter.gety(),
    windowCenter.getz(), windowAngleX, transform_type::ON_WINDOW);
    rotate_service.rotateY(object, windowCenter.getx(), windowCenter.gety(),
    windowCenter.getz(), windowAngleY, transform_type::ON_WINDOW);
    rotate_service.rotateZ(object, windowCenter.getx(), windowCenter.gety(),
    windowCenter.getz(), windowAngleZ, transform_type::ON_WINDOW);
    if (object->isInFrontOfWindow(windowCenter.getz()))
    {
      if (viewport->getProjection())
      {
        applyPerspective(object, windowCenter);
      }
      clipping_service.clip(viewport->getViewWindow(), object);
      list<Coordinate> objectCoordinates = object->getCoordinatesClipped();
      Coordinate firstCordConverted = convertFromWindowToViewport(
                                        *(objectCoordinates.begin()), viewport);

      cr->move_to(firstCordConverted.getx(),firstCordConverted.gety());
      if (objectCoordinates.size() == 1)  // point case
      {
        cr->line_to(firstCordConverted.getx()+1,firstCordConverted.gety()+1);
        cr->stroke();
      }
      else
      {
        if (object->getType() == object_type::OBJECT3D)
        {
          int k = 0;
          for (Coordinate coordinate : objectCoordinates)
          {
            Coordinate cordConverted = convertFromWindowToViewport(coordinate, viewport);
            if (k%2 == 0)
            {
              cr->move_to(cordConverted.getx(),cordConverted.gety());
            }
            else
            {
              cr->line_to(cordConverted.getx(),cordConverted.gety());
            }
            k++;
          }
        }
        else
        {
          for (Coordinate coordinate : objectCoordinates)
          {
            Coordinate cordConverted = convertFromWindowToViewport(coordinate, viewport);
            cr->line_to(cordConverted.getx(),cordConverted.gety());
          }
        }
        if (object->getType() == object_type::WIREFRAME) // wireframe case
        {
          cr->close_path();
          if(viewport->getFill())
          {
            cr->stroke_preserve();
            cr->fill();
          }
          else
          {
            cr->stroke();
          }
        }
        else
        {
          cr->stroke();
        }
      }
    }
  }

  // draw viewport corners
  cr->set_line_width(2);
  cr->set_source_rgb(RED);
  cr->move_to(viewport->getXvpmin(),viewport->getYvpmin());
  cr->line_to(viewport->getXvpmax(),viewport->getYvpmin());
  cr->line_to(viewport->getXvpmax(),viewport->getYvpmax());
  cr->line_to(viewport->getXvpmin(),viewport->getYvpmax());
  cr->close_path();
  cr->stroke();
}

Coordinate DrawViewportService::convertFromWindowToViewport(Coordinate cord, Viewport* viewport)
{
  ViewWindow* viewWindow = viewport->getViewWindow();
  double Xw = cord.getx();
  double Xvp = (((viewport->getXvpmax() - viewport->getXvpmin()) /
            (viewWindow->getXwmax() - viewWindow->getXwmin()))
            * (Xw - viewWindow->getXwmin()) + viewport->getXvpmin());

  double Yw = cord.gety();
  double Yvp = (viewport->getYvpmax() + viewport->getYvpmin()) -
                (((viewport->getYvpmax() - viewport->getYvpmin()) /
                (viewWindow->getYwmax() - viewWindow->getYwmin()))
                * (Yw - viewWindow->getYwmin()) + viewport->getYvpmin());

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
                           (viewWindow->getXwmax()
                            - viewWindow->getXwmin())
                           * widthDiff
                           / (viewport->getXvpmax()
                            - viewport->getXvpmin()));
    }
    else
    {
      viewWindow->setXwmax(widthDiff*DEFAULT_ZOOM);
    }

    if (viewport->getYvpmax() != 0)
    {
      viewWindow->setYwmin(viewWindow->getYwmin() -
                           (viewWindow->getYwmax()
                            - viewWindow->getYwmin())
                           * heightDiff
                           / (viewport->getYvpmax()
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

/*
 * COP = CENTER OBSERVER POINT
 */
 void DrawViewportService::applyPerspective(DrawableObject* object, Coordinate windowCenter)
{
  Coordinate cop(
    windowCenter.getx(),
    windowCenter.gety(),
    windowCenter.getz() + COP_Z
  );
  list<Coordinate> cord_list;
  for (Coordinate cord : object->getCoordinatesWindow())
  {
    Coordinate translated_cord = cord.toMatrix() + (cop.toMatrix()*-1);
    Coordinate projection_cord(
      translated_cord.getx()/(translated_cord.getz()/abs(COP_Z)),
      translated_cord.gety()/(translated_cord.getz()/abs(COP_Z)),
      abs(COP_Z)
    );
    cord_list.push_back(projection_cord.toMatrix() + cop.toMatrix());
  }
  object->setCoordinatesWindow(cord_list);
}
