#include "wireframe.hpp"

WireFrame::WireFrame(string name, list<Coordinate*> coordinates)
    : DrawableObject(name, coordinates)
{
}

WireFrame::~WireFrame()
{
}

list<Coordinate*> WireFrame::getCoordinates()
{
  return coordinates;
}

string WireFrame::getType()
{
  return "Polygon";
}
