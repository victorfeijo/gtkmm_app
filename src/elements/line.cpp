#include "line.hpp"

Line::Line(string name, Coordinate line_cord1, Coordinate line_cord2)
  : DrawableObject(name)
{
  coordinatesWorld.push_back(line_cord1);
  coordinatesWorld.push_back(line_cord2);
}

Line::~Line()
{
}

string Line::getTypeName()
{
  return "Line";
}

object_type Line::getType()
{
  return object_type::LINE;
}

void Line::resetWindowCoordinates()
{
  coordinatesWindow = coordinatesWorld;
}
