#include "point.hpp"

Point::Point(string name, Coordinate* point_cord)
    : DrawableObject(name)
{
  coordinates.push_back(point_cord);
}

Point::~Point()
{
}

list<Coordinate*> Point::getCoordinates()
{
  return coordinates;
}

string Point::getType()
{
  return "Point";
}
