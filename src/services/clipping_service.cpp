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
        case POINT_LB:
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
        case LB:
        case POINT_LB:
          clipLiangBarsky(window, object);
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
  if (object->getCoordinatesWindow().size() != 1)
  {
    throw 30;
  }
  std::list<Coordinate> windowCordList;
  if (calcRegionCode(window, windowCordList.front()) == INSIDE)
  {
    windowCordList = object->getCoordinatesWindow();
  }
  object->setCoordinatesClipped(windowCordList);
}

void ClippingService::clipCohenSutherland(ViewWindow* window, DrawableObject *object)
{
  if (object->getCoordinatesWindow().size() != 2)
  {
    throw 31;
  }
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
    else if (regionCode1 & regionCode2)  // line does not pass through the window
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

void ClippingService::clipLiangBarsky(ViewWindow* window, DrawableObject *object)
{
  if (object->getCoordinatesWindow().size() != 2)
  {
    throw 32;
  }
  Coordinate p1 = object->getCoordinatesWindow().front();
  Coordinate p2 = *(--object->getCoordinatesWindow().end());
  double u1 = 0.0;
  double u2 = 1.0;
  double xDelta = p2.getx() - p1.getx();
  double yDelta = p2.gety() - p1.gety();
  double p, q, r;
  bool draw = true;

  for (int i = 0; i < 4; i++)
  {
    switch (i)
    {
      case 0:
        p = -1 * xDelta;
        q = -1 * (window->getXwmin() - p1.getx());
        break;
      case 1:
        p = xDelta;
        q = (window->getXwmax() - p1.getx());
        break;
      case 2:
        p = -1 * yDelta;
        q = -1 * (window->getYwmin() - p1.gety());
        break;
      case 3:
        p = yDelta;
        q = (window->getYwmax() - p1.gety());
        break;
    }

    r = q / p;

    if ((p == 0 && q < 0) || (p < 0 && r > u2) || (p > 0 && r < u1))
    {
      draw = false;
      break;
    }
    if (p < 0 && r > u1)
    {
      u1 = r;
    }
    if (p > 0 && r < u2)
    {
      u2 = r;
    }
  }

  std::list<Coordinate> clippedCoordinates;
  if (draw)
  {
    double x1 = p1.getx() + u1*xDelta;
    double y1 = p1.gety() + u1*yDelta;
    double x2 = p1.getx() + u2*xDelta;
    double y2 = p1.gety() + u2*yDelta;
    clippedCoordinates.push_back(Coordinate(x1, y1));
    clippedCoordinates.push_back(Coordinate(x2, y2));
  }
  object->setCoordinatesClipped(clippedCoordinates);

}
