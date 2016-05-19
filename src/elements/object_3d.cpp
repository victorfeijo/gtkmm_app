#include "object_3d.hpp"

Object3D::Object3D(string name, list<Coordinate> coordinates)
    : DrawableObject(name, coordinates)
{
}

Object3D::~Object3D()
{
}

string Object3D::getTypeName()
{
  return "Object3D";
}

object_type Object3D::getType()
{
  return object_type::OBJECT3D;
}

void Object3D::resetWindowCoordinates()
{
  coordinatesWindow = coordinatesWorld;
}
