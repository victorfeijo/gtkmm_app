#ifndef GTKMM_APP_B_SPLINE
#define GTKMM_APP_B_SPLINE

#include <list>
#include "matrix.hpp"
#include "coordinate.hpp"

using namespace std;

class BSpline
{
public:
  BSpline(std::list<Coordinate> coordinates);
  ~BSpline();

  list<Coordinate> blend();
  list<Coordinate> calcForwardDifferences(Matrix<double> cord_array);
  Matrix<double> getBase();
  
private:
  list<Coordinate> coordinates;
};
#endif
