#include "curve_2d.hpp"

Curve2D::Curve2D(string name, std::list<Vector> vectors)
    : DrawableObject(name)
{
  if (vectors.size() < 2)
  {
    throw 40;
  }
  for (Vector vec : vectors)
  {
    this->coordinatesWorld.push_back(vec.getBegin());
    this->coordinatesWorld.push_back(vec.getEnd());
  }
}

Curve2D::~Curve2D()
{
}

string Curve2D::getTypeName()
{
  return "2D Curve";
}

object_type Curve2D::getType()
{
  return object_type::CURVE2D;
}

std::list<BezierCurve> Curve2D::getSubCurves()
{
  std::list<BezierCurve> subcurves;
  int k = 1;
  Coordinate last_cord(0,0);
  Vector last_vec(last_cord, last_cord);
  for (Coordinate cord : coordinatesWorld)
  {
    if (k % 2 != 0)
    {
      last_cord = cord;
    }
    else
    {
      Vector vec(last_cord, cord);
      if (k > 2)
      {
        subcurves.push_back(BezierCurve(last_vec, vec.getOpposite()));
      }
      last_vec = vec;
    }
    k++;
  }
  return subcurves;
}

void Curve2D::resetWindowCoordinates()
{
  coordinatesWindow.clear();
  for (BezierCurve curve : getSubCurves())
  {
    for (Coordinate cord : curve.blend())
    {
      coordinatesWindow.push_back(cord);
    }
  }
}
