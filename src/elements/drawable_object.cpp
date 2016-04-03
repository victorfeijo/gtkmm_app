#include "drawable_object.hpp"

DrawableObject::DrawableObject(string name)
    : name(name)
{
}

DrawableObject::DrawableObject(string name, list<Coordinate*> coordinates)
    : name(name), coordinates(coordinates)
{
}

DrawableObject::~DrawableObject()
{
  this->destroyList();
}

void DrawableObject::destroyList()
{
  while(!coordinates.empty())
  {
    delete coordinates.front();
    coordinates.pop_front();
  }
}

std::string DrawableObject::getName()
{
  return name;
}

void DrawableObject::setCoordinates(list<Coordinate*> coordinates)
{
  this->destroyList();
  this->coordinates = coordinates;
}

Coordinate DrawableObject::getCenter()
{
  long int xSum, ySum, zSum, xAvg, yAvg, zAvg;
  int count = 0;
  xSum = 0;
  ySum = 0;
  zSum = 0;
  for (std::list<Coordinate*>::iterator it = coordinates.begin();
        it != coordinates.end(); ++it)
  {
    xSum += (*it)->getx();
    ySum += (*it)->gety();
    zSum += (*it)->getz();
    count++;
  }
  xAvg = xSum / count;
  yAvg = ySum / count;
  zAvg = zSum / count;

  return Coordinate(xAvg, yAvg, zAvg);
}
