#ifndef GTKMM_APP_VECTOR
#define GTKMM_APP_VECTOR

#include "coordinate.hpp"

class Vector
{

public:

  Vector(Coordinate begin, int x, int y, int z = 1);
  Vector(Coordinate begin, Coordinate end);
  ~Vector();
  Coordinate getBegin();
  Coordinate getEnd();
  Vector getOpposite();

protected:
  Coordinate begin;
  int x, y, z;

};

#endif
