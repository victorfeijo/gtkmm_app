#include "point.h"

Point::Point(string name, Coordenate* point_cord)
: DrawableObject(name)
{
  Coordenate *point_trick = new Coordenate(point_cord->getx(), point_cord->gety());
  coordenates.push_back(point_cord);
  coordenates.push_back(point_trick);
}

Point::~Point()
{
}

list<Coordenate*> Point::getCoordenates()
{
  return coordenates;
}
