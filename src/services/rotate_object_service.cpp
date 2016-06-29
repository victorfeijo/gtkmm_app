#include "rotate_object_service.hpp"

RotateObjectService::RotateObjectService()
{
}

RotateObjectService::~RotateObjectService()
{
}

void RotateObjectService::rotateAxis(DrawableObject *object, Vector vec, int angle)
{
  // convert from deg to rad
  double angleRad = angle * M_PI / 180;

  double bx = vec.getBegin().getx();
  double by = vec.getBegin().gety();
  double bz = vec.getBegin().getz();
  double ex = vec.getEnd().getx()-bx;
  double ey = vec.getEnd().gety()-by;
  double ez = vec.getEnd().getz()-bz;
  double eModule = sqrt(ex*ex + ey*ey + ez*ez);

  double ax = ex/eModule;
  double ay = ey/eModule;
  double az = ez/eModule;

  Matrix<double> rotationMatrix(3,3);
  rotationMatrix.set(0, 0,      cos(angleRad)      + ax*ax*(1-cos(angleRad)));
  rotationMatrix.set(0, 1, ax*ay*(1-cos(angleRad)) -    az*sin(angleRad));
  rotationMatrix.set(0, 2, ax*az*(1-cos(angleRad)) +    ay*sin(angleRad));
  rotationMatrix.set(1, 0, ay*ax*(1-cos(angleRad)) +    az*sin(angleRad));
  rotationMatrix.set(1, 1,      cos(angleRad)      + ay*ay*(1-cos(angleRad)));
  rotationMatrix.set(1, 2, ay*az*(1-cos(angleRad)) -    ax*sin(angleRad));
  rotationMatrix.set(2, 0, az*ax*(1-cos(angleRad)) -    ay*sin(angleRad));
  rotationMatrix.set(2, 1, ay*az*(1-cos(angleRad)) +    ax*sin(angleRad));
  rotationMatrix.set(2, 2,      cos(angleRad)      + az*az*(1-cos(angleRad)));

  rotate(object, bx, by, bz, rotationMatrix);
}

void RotateObjectService::rotateX(DrawableObject *object, int dx, int dy, int dz,
                                  int angle, transform_type type)
{
  // convert from deg to rad
  double angleRad = angle * M_PI / 180;

  Matrix<double> rotateX(3,3);
  rotateX.set(0, 0, 1);
  rotateX.set(1, 1, cos(angleRad));
  rotateX.set(1, 2, -sin(angleRad));
  rotateX.set(2, 1, sin(angleRad));
  rotateX.set(2, 2, cos(angleRad));

  rotate(object, dx, dy, dz, rotateX, type);
}
void RotateObjectService::rotateY(DrawableObject *object, int dx, int dy, int dz,
                                  int angle, transform_type type)
{
  // convert from deg to rad
  double angleRad = angle * M_PI / 180;

  Matrix<double> rotateY(3,3);
  rotateY.set(0, 0, cos(angleRad));
  rotateY.set(0, 2, sin(angleRad));
  rotateY.set(1, 1, 1);
  rotateY.set(2, 0, -sin(angleRad));
  rotateY.set(2, 2, cos(angleRad));

  rotate(object, dx, dy, dz, rotateY, type);
}
void RotateObjectService::rotateZ(DrawableObject *object, int dx, int dy, int dz,
                                  int angle, transform_type type)
{
  // convert from deg to rad
  double angleRad = angle * M_PI / 180;

  Matrix<double> rotateZ(3,3);
  rotateZ.set(0, 0, cos(angleRad));
  rotateZ.set(0, 1, -sin(angleRad));
  rotateZ.set(1, 0, sin(angleRad));
  rotateZ.set(1, 1, cos(angleRad));
  rotateZ.set(2, 2, 1);

  rotate(object, dx, dy, dz, rotateZ, type);
}


void RotateObjectService::rotate(DrawableObject *object, int dx, int dy, int dz,
                          Matrix<double> transform_matrix, transform_type type)
{
  translate_service.translate(object, -dx, -dy, -dz, type);
  list<Coordinate> new_cord_list;
  list<Coordinate> cord_list;
  switch (type) {
    case transform_type::ON_WORLD:
      cord_list = object->getCoordinatesWorld();
    break;
    case transform_type::ON_WINDOW:
      cord_list = object->getCoordinatesWindow();
    break;
  }

  for(Coordinate cord : cord_list)
  {
    Matrix<double> point = cord.toMatrix();
    Matrix<double> pointRotated = point * transform_matrix;
    new_cord_list.push_back(pointRotated);
  }
  switch (type) {
    case transform_type::ON_WORLD:
      object->setCoordinatesWorld(new_cord_list);
    break;
    case transform_type::ON_WINDOW:
      object->setCoordinatesWindow(new_cord_list);
    break;
  }
  translate_service.translate(object, dx, dy, dz, type);
}
