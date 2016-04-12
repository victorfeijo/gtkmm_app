#include "point.hpp"

Point::Point(string name, Coordinate point_cord)
    : DrawableObject(name)
{
  coordinatesWorld.push_back(point_cord);
  this->copyFromWorldToWindow();
}

Point::~Point()
{
}

string Point::getType()
{
  return "Point";
}
