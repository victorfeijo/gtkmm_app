#include "point.h"

Point::Point(string name, Coordinate* point_cord)
: DrawableObject(name)
{
  Coordinates.push_back(point_cord);
}

Point::~Point()
{
}

list<Coordinate*> Point::getCoordinates()
{
  return Coordinates;
}
