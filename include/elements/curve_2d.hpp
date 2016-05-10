#ifndef GTKMM_APP_CURVE_2D
#define GTKMM_APP_CURVE_2D

#include <list>
#include "vector.hpp"
#include "drawable_object.hpp"
#include "bezier_curve.hpp"
#include "b_spline.hpp"

using namespace std;

class Curve2D : public DrawableObject
{
public:
  Curve2D(string name, list<Vector> vectors);
  Curve2D(string name, list<Coordinate> coordinates, object_type type);
  ~Curve2D();
  virtual string getTypeName();
  virtual object_type getType();
  virtual void resetWindowCoordinates();
private:
  list<BezierCurve> getSubBezierCurves();
  object_type type;
};

#endif
