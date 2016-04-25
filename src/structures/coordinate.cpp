#include "coordinate.hpp"

Coordinate::Coordinate(double x, double y)
    : cord_x(x), cord_y(y), cord_z(1)
{
}

Coordinate::Coordinate(double x, double y, double z)
    : cord_x(x), cord_y(y), cord_z(z)
{
}

Coordinate::Coordinate(Matrix<double> matrix)
    : cord_x(matrix.get(0,0)),
      cord_y(matrix.get(0,1)),
      cord_z(matrix.get(0,2))
{
}

Coordinate::~Coordinate()
{
}

double Coordinate::getx()
{
  return cord_x;
}

double Coordinate::gety()
{
  return Coordinate::cord_y;
}

double Coordinate::getz()
{
  return cord_z;
}

Matrix<double> Coordinate::toMatrix()
{
  Matrix<double> mat(1,3);
  mat.set(0, 0, cord_x);
  mat.set(0, 1, cord_y);
  mat.set(0, 2, cord_z);
  return mat;
}
