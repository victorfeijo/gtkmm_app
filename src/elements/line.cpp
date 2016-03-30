#include "line.hpp"

Line::Line(string name, Coordinate* line_cord1, Coordinate* line_cord2)
: DrawableObject(name)
{
  Coordinates.push_back(line_cord1);
  Coordinates.push_back(line_cord2);
}

Line::~Line()
{
}

list<Coordinate*> Line::getCoordinates()
{
  return Coordinates;
}

string Line::getType()
{
  return "Line";
}
