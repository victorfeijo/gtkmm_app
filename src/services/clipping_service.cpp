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
    {
      switch(type)
      {
        case PC:
        case PC_CS:
        case PC_LB:
        case PC_CS_SH:
        case PC_LB_SH:
        case PC_SH:
        {
          clipPoint(window, object);
          break;
        }
        default:
        {
          goto DO_NOT_CLIP;
        }
      }
      break;
    }
    case 2:  // line
    {
      switch (type)
      {
        case CS:
        case PC_CS:
        case PC_CS_SH:
        case CS_SH:
        {
          clipCohenSutherland(window, object);
          break;
        }
        case LB:
        case PC_LB:
        case PC_LB_SH:
        case LB_SH:
        {
          clipLiangBarsky(window, object);
          break;
        }
        default:
        {
          goto DO_NOT_CLIP;
        }
      }
      break;
    }
    default:  // wireframe / curve2d
    {
      switch (type)
      {
        case SH:
        case PC_CS_SH:
        case PC_LB_SH:
        case PC_SH:
        case CS_SH:
        case LB_SH:
        {
          clipSutherlandHodgman(window, object);
          break;
        }
        default:
        {
          goto DO_NOT_CLIP;
        }
      }
    }
  }
  return;
  DO_NOT_CLIP:
  object->setCoordinatesClipped(object->getCoordinatesWindow());
}

void ClippingService::clipPoint(ViewWindow* window, DrawableObject *object)
{
  if (object->getCoordinatesWindow().size() != 1)
  {
    throw 30;
  }
  std::list<Coordinate> windowCordList;
  if (calcRegionCode(window, object->getCoordinatesWindow().front()) == INSIDE)
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
  Coordinate p2 = object->getCoordinatesWindow().back();
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

      Coordinate intersection = calcIntersection(p1, p2, window, regionCodeOutside);

      if (regionCodeOutside == regionCode1) {
        p1 = intersection;
        regionCode1 = calcRegionCode(window, p1);
      } else {
        p2 = intersection;
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
  Coordinate p2 = object->getCoordinatesWindow().back();
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
      {
        p = -1 * xDelta;
        q = -1 * (window->getXwmin() - p1.getx());
        break;
      }
      case 1:
      {
        p = xDelta;
        q = (window->getXwmax() - p1.getx());
        break;
      }
      case 2:
      {
        p = -1 * yDelta;
        q = -1 * (window->getYwmin() - p1.gety());
        break;
      }
      case 3:
      {
        p = yDelta;
        q = (window->getYwmax() - p1.gety());
        break;
      }
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

void ClippingService::clipSutherlandHodgman(ViewWindow *window, DrawableObject *object)
{
  if (object->getCoordinatesWindow().size() < 3)
  {
    throw 33;
  }

  std::list<Coordinate> output = object->getCoordinatesWindow();

  for (int i = 0; i < 4; i++)  // for each edge in window
  {
    int edge_code = pow(2, i);  // LEFT // RIGHT // BOTTOM // TOP //
    std::list<Coordinate> input = output;
    output.clear();
    Coordinate last = input.back();
    if (object->getType() == BEZIER2D || object->getType() == BSPLINE2D)
    {
      last = input.front();
    }

    for (Coordinate cord : input)
    {
      int last_code = calcRegionCode(window, last);
      int cord_code = calcRegionCode(window, cord);
      if (!(cord_code & edge_code))  // if cord.isInside(edge)
      {
        if (last_code & edge_code)  // if not last.isInside(edge)
        {
          output.push_back(calcIntersection(last, cord, window, edge_code));
        }
        output.push_back(cord);
      }
      else if (!(last_code & edge_code)) // else if last.isInside(edge)
      {
        output.push_back(calcIntersection(last, cord, window, edge_code));
      }
      last = cord;
    }
  }
  object->setCoordinatesClipped(output);
}

Coordinate ClippingService::calcIntersection(Coordinate cord1, Coordinate cord2, ViewWindow *window, int regionCode)
{
  double x, y;
  if (regionCode & TOP)
  {
    x = cord1.getx() + (cord2.getx() - cord1.getx()) * (window->getYwmax() -
        cord1.gety()) / (cord2.gety() - cord1.gety());
    y = window->getYwmax();
  }
  else if (regionCode & BOTTOM)
  {
    x = cord1.getx() + (cord2.getx() - cord1.getx()) * (window->getYwmin() -
        cord1.gety()) / (cord2.gety() - cord1.gety());
    y = window->getYwmin();
  }
  else if (regionCode & RIGHT)
  {
    y = cord1.gety() + (cord2.gety() - cord1.gety()) * (window->getXwmax() -
        cord1.getx()) / (cord2.getx() - cord1.getx());
    x = window->getXwmax();
  }
  else if (regionCode & LEFT)
  {
    y = cord1.gety() + (cord2.gety() - cord1.gety()) * (window->getXwmin() -
        cord1.getx()) / (cord2.getx() - cord1.getx());
    x = window->getXwmin();
  }
  return Coordinate(x, y);
}

Coordinate ClippingService::alignToEdge(Coordinate cord, ViewWindow *window, int regionCode)
{
  double x = cord.getx();
  double y = cord.gety();
  if (regionCode & TOP)
  {
    y = window->getYwmax();
  }
  if (regionCode & BOTTOM)
  {
    y = window->getYwmin();
  }
  if (regionCode & RIGHT)
  {
    x = window->getXwmax();
  }
  if (regionCode & LEFT)
  {
    x = window->getXwmin();
  }
  return Coordinate(x, y);
}
