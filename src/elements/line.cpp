#include "line.hpp"

Line::Line(string name, Coordinate line_cord1, Coordinate line_cord2)
  : DrawableObject(name)
{
  coordinatesWorld.push_back(line_cord1);
  coordinatesWorld.push_back(line_cord2);
  this->copyFromWorldToWindow();
}

Line::~Line()
{
}

string Line::getType()
{
  return "Line";
}
