#include "clipping_service.hpp"
#include "view_window.hpp"

ClippingService::ClippingService()
{
}

ClippingService::~ClippingService()
{
}

void ClippingService::clip(ViewWindow* window, DrawableObject *object)
{
  clipping_type type = window->getClippingType();
  std::list<Coordinate> coordinatesWindow = object->getCoordinatesWindow();
  int size = coordinatesWindow.size();

  switch (size) {
    case 1:  // point
      switch(type) {
        case POINT:
        case POINT_CS:
          clipPoint(window, object);
          break;
        default:
          goto USE_SAME_COORDINATES;
          break;
      }
      break;
    case 2:  // line
      switch (type) {
        case CS:
        case POINT_CS:
          clipCohenSutherland(window, object);
          break;
        default:
          goto USE_SAME_COORDINATES;
          break;
      }
      break;
    default:  // wireframe
      goto USE_SAME_COORDINATES;
      break;
  }
  return;
  USE_SAME_COORDINATES:
  object->setCoordinatesClipped(object->getCoordinatesWindow());
}

void ClippingService::clipPoint(ViewWindow* window, DrawableObject *object)
{
  std::list<Coordinate> windowCordList = object->getCoordinatesWindow();
  windowCordList.front();
  if (isCordOnWindow(windowCordList.front(), window))
  {
    object->setCoordinatesClipped(windowCordList);
  }
  else
  {
    object->setCoordinatesClipped(std::list<Coordinate>());
  }
}

void ClippingService::clipCohenSutherland(ViewWindow* window, DrawableObject *object)
{
  Coordinate p1 = object->getCoordinatesWindow().front();
  Coordinate p2 = *(--object->getCoordinatesWindow().end());
  int regionCode1 = calcRegionCode(window, p1);
  int regionCode2 = calcRegionCode(window, p2);
  bool draw;

  while (true)
  {
    if (!regionCode1 && !regionCode2)  // both points are inside the window
    {
      draw = true;
      break;
    }
    else if (regionCode1 && regionCode2)  // both points are outside the window
    {
      draw = false;
      break;
    }
    else {
      int regionCodeOutside;
      if (regionCode1)
      {
        regionCodeOutside = regionCode1;
      }
      else
      {
        regionCodeOutside = regionCode2;
      }

      double x, y;
      if (regionCodeOutside & TOP)
      {
        x = p1.getx() + (p2.getx() - p1.getx()) * (window->getYwmax() -
            p1.gety()) / (p2.gety() - p1.gety());
        y = window->getYwmax();
      }
      else if (regionCodeOutside & BOTTOM)
      {
        x = p1.getx() + (p2.getx() - p1.getx()) * (window->getYwmin() -
            p1.gety()) / (p2.gety() - p1.gety());
        y = window->getYwmin();
      }
      else if (regionCodeOutside & RIGHT)
      {
        y = p1.gety() + (p2.gety() - p1.gety()) * (window->getXwmax() - p1.getx()) / (p2.getx() - p1.getx());
        x = window->getXwmax();
      }
      else if (regionCodeOutside & LEFT)
      {
        y = p1.gety() + (p2.gety() - p1.gety()) * (window->getXwmin() - p1.getx()) / (p2.getx() - p1.getx());
        x = window->getXwmin();
      }

      if (regionCodeOutside == regionCode1) {
        p1 = Coordinate(x, y);
        regionCode1 = calcRegionCode(window, p1);
      } else {
        p2 = Coordinate(x, y);
        regionCode2 = calcRegionCode(window, p2);
      }
    }
  }

  std::list<Coordinate> clippedCoordinates;
  if (draw)
  {
    clippedCoordinates.push_back(p1);
    clippedCoordinates.push_back(p2);
  }
  object->setCoordinatesClipped(clippedCoordinates);

}

int ClippingService::calcRegionCode(ViewWindow* window, Coordinate cord)
{
  int code = INSIDE;
  code = INSIDE;

  if (cord.getx() < window->getXwmin())
    code |= LEFT;
  else if (cord.getx() > window->getXwmax())
    code |= RIGHT;
  if (cord.gety() < window->getYwmin())
    code |= BOTTOM;
  else if (cord.gety() > window->getYwmax())
    code |= TOP;

  return code;
}

bool ClippingService::isCordOnWindow(Coordinate cord, ViewWindow *window)
{
  int x = cord.getx();
  int y = cord.gety();
  if (window->getXwmin() <= x && x <= window->getXwmax() &&
      window->getYwmin() <= y && y <= window->getYwmax())
  {
    return true;
  }
  else
  {
    return false;
  }
}
