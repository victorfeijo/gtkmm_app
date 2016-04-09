#include "drawable_object.hpp"

DrawableObject::DrawableObject(string name)
    : name(name)
{
}

DrawableObject::DrawableObject(string name, list<Coordinate> coordinates)
    : name(name), coordinatesWorld(coordinates)
{
  this->copyFromWorldToWindow();
}

DrawableObject::~DrawableObject()
{
  this->destroyList(coordinatesWorld);
  this->destroyList(coordinatesWindow);
}

void DrawableObject::destroyList(list<Coordinate> coordinates)
{
  while(!coordinates.empty())
  {
    // delete coordinates.front();
    coordinates.pop_front();
  }
}

std::string DrawableObject::getName()
{
  return name;
}

list<Coordinate> DrawableObject::getCoordinatesWorld()
{
  return this->coordinatesWorld;
}

list<Coordinate> DrawableObject::getCoordinatesWindow()
{
  return this->coordinatesWindow;
}

void DrawableObject::setCoordinatesWorld(list<Coordinate> coordinates)
{
  this->destroyList(coordinatesWorld);
  this->coordinatesWorld = coordinates;
}

void DrawableObject::setCoordinatesWindow(list<Coordinate> coordinates)
{
  this->destroyList(coordinatesWindow);
  this->coordinatesWindow = coordinates;
}

Coordinate DrawableObject::getCenterOnWorld()
{
  long int xSum, ySum, zSum, xAvg, yAvg, zAvg;
  int count = 0;
  xSum = 0;
  ySum = 0;
  zSum = 0;
  for (std::list<Coordinate>::iterator it = coordinatesWorld.begin();
        it != coordinatesWorld.end(); ++it)
  {
    xSum += (*it).getx();
    ySum += (*it).gety();
    zSum += (*it).getz();
    count++;
  }
  xAvg = xSum / count;
  yAvg = ySum / count;
  zAvg = zSum / count;

  return Coordinate(xAvg, yAvg, zAvg);
}

void DrawableObject::copyFromWorldToWindow()
{
  coordinatesWindow = coordinatesWorld;
}
