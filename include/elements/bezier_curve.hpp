#ifndef GTKMM_APP_BEZIER_CURVE
#define GTKMM_APP_BEZIER_CURVE

#define DELTA 0.008

#include <list>
#include "vector.hpp"
#include "matrix.hpp"

using namespace std;

class BezierCurve
{
public:
  BezierCurve(Vector vector1, Vector vector2);
  ~BezierCurve();
  Vector getVector1();
  Vector getVector2();
  list<Coordinate> blend();
private:
  Vector vector1, vector2;
};
#endif
