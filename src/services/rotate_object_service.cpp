#include "rotate_object_service.hpp"

RotateObjectService::RotateObjectService()
{
}

RotateObjectService::~RotateObjectService()
{
}

void RotateObjectService::rotateX(DrawableObject *object, int dx, int dy, int dz,
                                  int angle, transform_type type)
{
  // convert from deg to rad
  double angleRad = angle * M_PI / 180;

  Matrix<double> rotateX(4,4);
  rotateX.set(0, 0, 1);
  rotateX.set(1, 1, cos(angleRad));
  rotateX.set(1, 2, sin(angleRad));
  rotateX.set(2, 1, sin(angleRad));
  rotateX.set(2, 2, cos(angleRad));
  rotateX.set(3, 3, 1);

  rotate(object, dx, dy, dz, rotateX, type);
  // Matrix<double> rotateX(3,3);
  // rotateZ.set(0, 0, cos(angleRad));
  // rotateZ.set(0, 1, -sin(angleRad));
  // rotateZ.set(1, 0, sin(angleRad));
  // rotateZ.set(1, 1, cos(angleRad));
  // rotateZ.set(2, 2, 1);

}
void RotateObjectService::rotateY(DrawableObject *object, int dx, int dy, int dz,
                                  int angle, transform_type type)
{
  // convert from deg to rad
  double angleRad = angle * M_PI / 180;

  Matrix<double> rotateY(4,4);
  rotateY.set(0, 0, cos(angleRad));
  rotateY.set(0, 2, sin(angleRad));
  rotateY.set(1, 1, 1);
  rotateY.set(2, 0, sin(angleRad));
  rotateY.set(2, 2, cos(angleRad));
  rotateY.set(3, 3, 1);

  rotate(object, dx, dy, dz, rotateY, type);
}
void RotateObjectService::rotateZ(DrawableObject *object, int dx, int dy, int dz,
                                  int angle, transform_type type)
{
  // convert from deg to rad
  double angleRad = angle * M_PI / 180;

  Matrix<double> rotateZ(3,3);
  rotateZ.set(0, 0, cos(angleRad));
  rotateZ.set(0, 1, sin(angleRad));
  rotateZ.set(1, 0, sin(angleRad));
  rotateZ.set(1, 1, cos(angleRad));
  rotateZ.set(2, 2, 1);
  rotateZ.set(3, 3, 1);

  rotate(object, dx, dy, dz, rotateZ, type);
}


void RotateObjectService::rotate(DrawableObject *object, int dx, int dy, int dz,
                          Matrix<double> transform_matrix, transform_type type)
{
  object->resetWindowCoordinates();
  translate_service.translate(object, -dx, -dy, -dz, type);
  std::list<Coordinate> new_cord_list;
  std::list<Coordinate> cord_list;
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
    Matrix<double> point(4,4);
    point.set(0, 0, cord.getx());
    point.set(0, 1, cord.gety());
    point.set(0, 2, cord.getz());
    point.set(0, 3, 1);

    Matrix<double> pointRotated = point * transform_matrix;
    Coordinate cordRotated(
        pointRotated.get(0,0),
        pointRotated.get(0,1),
        pointRotated.get(0,2)
    );
    new_cord_list.push_back(cordRotated);
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

void RotateObjectService::rotateCenterObjectX(DrawableObject *object, int angle)
{
  Coordinate center = object->getCenterOnWorld();
  rotateX(object, center.getx(), center.gety(), center.getz(), angle);
}

void RotateObjectService::rotateCenterObjectY(DrawableObject *object, int angle)
{
  Coordinate center = object->getCenterOnWorld();
  rotateY(object, center.getx(), center.gety(), center.getz(), angle);
}

void RotateObjectService::rotateCenterObjectZ(DrawableObject *object, int angle)
{
  Coordinate center = object->getCenterOnWorld();
  rotateZ(object, center.getx(), center.gety(), center.getz(), angle);
}

void RotateObjectService::rotateCenterWorldX(DrawableObject *object, int angle)
{
  rotateX(object, 0, 0, 0, angle);
}

void RotateObjectService::rotateCenterWorldY(DrawableObject *object, int angle)
{
  rotateY(object, 0, 0, 0, angle);
}

void RotateObjectService::rotateCenterWorldZ(DrawableObject *object, int angle)
{
  rotateZ(object, 0, 0, 0, angle);
}
