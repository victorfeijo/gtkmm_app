#include "point.h"

Point::Point(list<Coordenate> view_cords, string name)
: DrawableObject(name, view_cords)
{
  Coordenate point_trick(view_cords.front().getx(), view_cords.front().gety());
  DrawableObject::coordenates.push_back(point_trick);
}

Point::~Point()
{
}

list<Coordenate> Point::getCoordenates()
{
  return coordenates;
}
