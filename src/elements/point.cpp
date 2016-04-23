#include "point.hpp"

Point::Point(string name, Coordinate point_cord)
    : DrawableObject(name)
{
  coordinatesWorld.push_back(point_cord);
}

Point::~Point()
{
}

string Point::getTypeName()
{
  return "Point";
}

object_type Point::getType()
{
  return object_type::POINT;
}

void Point::resetWindowCoordinates()
{
  coordinatesWindow = coordinatesWorld;
}
