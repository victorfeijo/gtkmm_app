#include "rect.hpp"

Rect::Rect(string name, Coordinate* rect_cord1, Coordinate* rect_cord2)
: DrawableObject(name)
{
  Coordinates.push_back(rect_cord1);
  Coordinates.push_back(rect_cord2);
}

Rect::~Rect()
{
}

list<Coordinate*> Rect::getCoordinates()
{
  return Coordinates;
}
