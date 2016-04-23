#include "rotate_object_service.hpp"

RotateObjectService::RotateObjectService()
{
}

RotateObjectService::~RotateObjectService()
{
}

void RotateObjectService::rotate(DrawableObject *object, int dx, int dy, int angleDegree, transform_type type)
{
  object->resetWindowCoordinates();
  translate_service.translate(object, -dx, -dy, 0, type);
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
    Matrix<double> point(1,3);
    point.set(0, 0, cord.getx());
    point.set(0, 1, cord.gety());
    point.set(0, 2, cord.getz());

    Matrix<double> offset1(3,3);
    offset1.set(0, 0, 1);
    offset1.set(1, 1, 1);
    offset1.set(2, 2, 1);
    offset1.set(2, 0, -1*dx);
    offset1.set(2, 1, -1*dy);

    double angleRad = angleDegree * M_PI / 180;

    Matrix<double> angle(3,3);
    angle.set(0, 0, cos(angleRad));
    angle.set(0, 1, -sin(angleRad));
    angle.set(1, 0, sin(angleRad));
    angle.set(1, 1, cos(angleRad));
    angle.set(2, 2, 1);

    Matrix<double> offset2(3,3);
    offset2.set(0, 0, 1);
    offset2.set(1, 1, 1);
    offset2.set(2, 2, 1);
    offset2.set(2, 0, dx);
    offset2.set(2, 1, dy);

    Matrix<double> pointRotated = point * angle;

    Coordinate new_cord = Coordinate(pointRotated.get(0, 0),
                             pointRotated.get(0, 1),  pointRotated.get(0,2));

    new_cord_list.push_back(new_cord);
  }
  switch (type) {
    case transform_type::ON_WORLD:
      object->setCoordinatesWorld(new_cord_list);
    break;
    case transform_type::ON_WINDOW:
      object->setCoordinatesWindow(new_cord_list);
    break;
  }
  translate_service.translate(object, dx, dy, 0, type);
}

void RotateObjectService::rotateCenterObject(DrawableObject *object, int angle)
{
  Coordinate center = object->getCenterOnWorld();
  rotate(object, center.getx(), center.gety(), angle);
}

void RotateObjectService::rotateCenterWorld(DrawableObject *object, int angle)
{
  rotate(object, 0, 0, angle);
}
