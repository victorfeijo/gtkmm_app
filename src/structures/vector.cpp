#include "vector.hpp"

Vector::Vector(Coordinate begin, int x, int y, int z)
    : begin(begin), x(x), y(y), z(z)
{
}

Vector::Vector(Coordinate begin, Coordinate end)
    : begin(begin)
{
  x = end.getx() - begin.getx();
  y = end.gety() - begin.gety();
  z = end.getz() - begin.getz();
}

Vector::~Vector()
{
}

Coordinate Vector::getBegin()
{
  return this->begin;
}

Coordinate Vector::getEnd()
{
  return Coordinate(begin.getx()+x, begin.gety()+y, begin.getz()+z);
}

Vector Vector::getOpposite()
{
  return Vector(begin, -x, -y, -z);
}
