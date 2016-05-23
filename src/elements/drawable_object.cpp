#include "drawable_object.hpp"

DrawableObject::DrawableObject(string name)
    : name(name)
{
}

DrawableObject::DrawableObject(string name, list<Coordinate> coordinates)
    : name(name), coordinatesWorld(coordinates)
{
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
    coordinates.pop_front();
  }
}

string DrawableObject::getName()
{
  return name;
}

list<Coordinate> DrawableObject::getCoordinatesWorld()
{
  return this->coordinatesWorld;
}

list<Coordinate> DrawableObject::getCoordinatesClipped()
{
  return this->coordinatesClipped;
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

void DrawableObject::setCoordinatesClipped(list<Coordinate> coordinates)
{
  this->destroyList(coordinatesClipped);
  this->coordinatesClipped = coordinates;
}

Coordinate DrawableObject::getCenterOnWorld()
{
  double xSum, ySum, zSum, xAvg, yAvg, zAvg;
  int count = 0;
  xSum = 0;
  ySum = 0;
  zSum = 0;
  for (Coordinate cord : coordinatesWorld)
  {
    xSum += cord.getx();
    ySum += cord.gety();
    zSum += cord.getz();
    count++;
  }
  xAvg = xSum / count;
  yAvg = ySum / count;
  zAvg = zSum / count;

  return Coordinate(xAvg, yAvg, zAvg);
}

bool DrawableObject::isInFrontOfWindow(double viewportZ)
{
  double zSum = 0;
  int count = 0;
  for (Coordinate cord : coordinatesWindow)
  {
    zSum += cord.getz();
    count++;
  }
  double zAvg = zSum / count;
  return zAvg >= viewportZ;
}
