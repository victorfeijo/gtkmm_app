#include "bezier_curve.hpp"

BezierCurve::BezierCurve(Vector vector1, Vector vector2)
    : vector1(vector1),
      vector2(vector2)
{
}

BezierCurve::~BezierCurve()
{
}

Vector BezierCurve::getVector1()
{
  return vector1;
}

Vector BezierCurve::getVector2()
{
  return vector2;
}

std::list<Coordinate> BezierCurve::blend()
{
  std::list<Coordinate> cord_list;

  Matrix<double> p1(1,3);
  p1.set(0, 0, vector1.getBegin().getx());
  p1.set(0, 1, vector1.getBegin().gety());
  p1.set(0, 2, vector1.getBegin().getz());

  Matrix<double> p2(1,3);
  p2.set(0, 0, vector1.getEnd().getx());
  p2.set(0, 1, vector1.getEnd().gety());
  p2.set(0, 2, vector1.getEnd().getz());

  Matrix<double> p3(1,3);
  p3.set(0, 0, vector2.getEnd().getx());
  p3.set(0, 1, vector2.getEnd().gety());
  p3.set(0, 2, vector2.getEnd().getz());

  Matrix<double> p4(1,3);
  p4.set(0, 0, vector2.getBegin().getx());
  p4.set(0, 1, vector2.getBegin().gety());
  p4.set(0, 2, vector2.getBegin().getz());

  for(double t = 0; t <= 1; t += DELTA)
  {
    Matrix<double> p11 = p1 + ((p2 - p1) * t);
    Matrix<double> p21 = p2 + ((p3 - p2) * t);
    Matrix<double> p31 = p3 + ((p4 - p3) * t);

    Matrix<double> p22 = p11 + ((p21 - p11) * t);
    Matrix<double> p32 = p21 + ((p31 - p21) * t);

    Matrix<double> p33 = p22 + ((p32 - p22) * t);
    Coordinate cord(p33.get(0,0), p33.get(0,1), p33.get(0,2));
    cord_list.push_back(cord);
  }
  return cord_list;
}
