#include "b_spline.hpp"

BSpline::BSpline(std::list<Coordinate> coordinates)
    : coordinates(coordinates)
{
}

BSpline::~BSpline()
{
}

std::list<Coordinate> BSpline::blend()
{
  std::list<Coordinate> cord_list;

  for(unsigned int i = 0; i < coordinates.size()-3; i++)
  {
    Matrix<double> current_curve(4,3);

    std::list<Coordinate>::iterator it_cord = coordinates.begin();
    advance(it_cord, i);
    for (unsigned int j = 0; j < 4; j++)
    {
      current_curve.set(j, 0, it_cord->getx());
      current_curve.set(j, 1, it_cord->gety());
      current_curve.set(j, 2, it_cord->getz());
      it_cord++;
    }

    list<Coordinate> aux = calcForwardDifferences(current_curve);

    for (Coordinate cord : aux)
    {
      cord_list.push_back(cord);
    }
  }

  return cord_list;
}

Matrix<double> BSpline::getBase()
{
  Matrix<double> base(4,4);

  base.set(0, 0, -1.0/6.0);
  base.set(0, 1,  3.0/6.0);
  base.set(0, 2, -3.0/6.0);
  base.set(0, 3,  1.0/6.0);

  base.set(1, 0,  3.0/6.0);
  base.set(1, 1, -6.0/6.0);
  base.set(1, 2,  3.0/6.0);
  base.set(1, 3,  0.0/6.0);

  base.set(2, 0, -3.0/6.0);
  base.set(2, 1,  0.0/6.0);
  base.set(2, 2,  3.0/6.0);
  base.set(2, 3,  0.0/6.0);

  base.set(3, 0,  1.0/6.0);
  base.set(3, 1,  4.0/6.0);
  base.set(3, 2,  1.0/6.0);
  base.set(3, 3,  0.0/6.0);

  return base;
}

list<Coordinate> BSpline::calcForwardDifferences(Matrix<double> cord_array)
{
  list<Coordinate> cord_list;
  Matrix<double> base = getBase();
  Matrix<double> mult = base * cord_array;

  Matrix<double> a = mult.getRow(0);
  Matrix<double> b = mult.getRow(1);
  Matrix<double> c = mult.getRow(2);
  Matrix<double> d = mult.getRow(3);

  Matrix<double> f0 = d;
  Matrix<double> f1 = a*0.001 + b*0.01 + c*0.1;
  Matrix<double> f2 = a*6*0.001 + b*2*0.01;
  Matrix<double> f3 = a*6*0.001;

  for(int i = 0; i <= 10; i++){
    cord_list.push_back(Coordinate(f0));
    f0 = f0 + f1;
    f1 = f1 + f2;
    f2 = f2 + f3;
  }

  return cord_list;
}
