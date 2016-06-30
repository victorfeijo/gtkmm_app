#include "curve_2d.hpp"

Curve2D::Curve2D(string name, list<Vector> vectors)
    : DrawableObject(name)
{
  this->type = object_type::BEZIER2D;
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

Curve2D::Curve2D(string name, list<Coordinate> coordinates, object_type type)
    : DrawableObject(name, coordinates), type(type)
{
  if (coordinates.size() < 4 || (type != BEZIER2D && type != BSPLINE2D))
  {
    throw 41;
  }
}

Curve2D::~Curve2D()
{
}

string Curve2D::getTypeName()
{
  if (type == object_type::BEZIER2D) { return "2D Bezier Curve"; }

  return "2D B-Spline";
}

object_type Curve2D::getType()
{
  return type;
}

list<BezierCurve> Curve2D::getSubBezierCurves()
{
  list<BezierCurve> subcurves;
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
  if (type == object_type::BEZIER2D)
  {
    for (BezierCurve curve : getSubBezierCurves())
    {
      for (Coordinate cord : curve.blend())
      {
        coordinatesWindow.push_back(cord);
      }
    }
  }
  else
  {
    BSpline spline(this->coordinatesWorld);
    for (Coordinate cord : spline.blend())
    {
      coordinatesWindow.push_back(cord);
    }
  }
}
