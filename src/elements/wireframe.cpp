#include "wireframe.hpp"

WireFrame::WireFrame(string name, list<Coordinate> coordinates)
    : DrawableObject(name, coordinates)
{
}

WireFrame::~WireFrame()
{
}

string WireFrame::getTypeName()
{
  return "Polygon";
}

object_type WireFrame::getType()
{
  return object_type::WIREFRAME;
}

void WireFrame::resetWindowCoordinates()
{
  coordinatesWindow = coordinatesWorld;
}
