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

  Matrix<double> p1 = vector1.getBegin().toMatrix();
  Matrix<double> p2 = vector1.getEnd().toMatrix();
  Matrix<double> p3 = vector2.getEnd().toMatrix();
  Matrix<double> p4 = vector2.getBegin().toMatrix();

  for(double t = 0; t <= 1; t += DELTA)
  {
    Matrix<double> p11 = p1 + ((p2 - p1) * t);
    Matrix<double> p21 = p2 + ((p3 - p2) * t);
    Matrix<double> p31 = p3 + ((p4 - p3) * t);

    Matrix<double> p22 = p11 + ((p21 - p11) * t);
    Matrix<double> p32 = p21 + ((p31 - p21) * t);

    Matrix<double> p33 = p22 + ((p32 - p22) * t);
    cord_list.push_back(Coordinate(p33));
  }
  return cord_list;
}
