#ifndef GTKMM_APP_COORDINATE
#define GTKMM_APP_COORDINATE

#include "matrix.hpp"

class Coordinate
{
public:
  Coordinate(double x, double y);
  Coordinate(double x, double y, double z);
  Coordinate(Matrix<double> matrix);
  ~Coordinate();
  double getx();
  double gety();
  double getz();
  Matrix<double> toMatrix();
protected:
  double cord_x, cord_y, cord_z;
};
#endif // GTKMM_APP_Coordinate
