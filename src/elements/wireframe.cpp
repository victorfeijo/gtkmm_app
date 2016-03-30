#include "wireframe.hpp"

WireFrame::WireFrame(string name, list<Coordinate*> Coordinates)
    : DrawableObject(name, Coordinates)
{
  //nothing for while
}

WireFrame::~WireFrame()
{
}

list<Coordinate*> WireFrame::getCoordinates()
{
  return Coordinates;
}

string WireFrame::getType()
{
  return "Polygon";
}
