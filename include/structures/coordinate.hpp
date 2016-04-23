#ifndef GTKMM_APP_COORDINATE
#define GTKMM_APP_COORDINATE

#include "matrix.hpp"

class Coordinate
{
public:
  Coordinate(double x, double y)
      : cord_x(x), cord_y(y), cord_z(1) {}
  Coordinate(double x, double y, double z)
      : cord_x(x), cord_y(y), cord_z(z) {}
  Coordinate(Matrix<double> matrix)
      : cord_x(matrix.get(0,0)),
        cord_y(matrix.get(0,1)),
        cord_z(matrix.get(0,2)) {}
  ~Coordinate() {}
  double getx()
  {
    return cord_x;
  }
  double gety()
  {
    return cord_y;
  }
  double getz()
  {
    return cord_z;
  }
  Matrix<double> toMatrix()
  {
    Matrix<double> mat(1,3);
    mat.set(0, 0, cord_x);
    mat.set(0, 1, cord_y);
    mat.set(0, 2, cord_z);
    return mat;
  }
protected:
  double cord_x, cord_y, cord_z;
};
#endif // GTKMM_APP_Coordinate
