#include "wireframe.hpp"

WireFrame::WireFrame(string name, list<Coordinate> coordinates)
    : DrawableObject(name, coordinates)
{
}

WireFrame::~WireFrame()
{
}

string WireFrame::getType()
{
  return "Polygon";
}
