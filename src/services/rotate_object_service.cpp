#include "rotate_object_service.hpp"

RotateObjectService::RotateObjectService()
{
}

RotateObjectService::~RotateObjectService()
{
}

void RotateObjectService::rotate(DrawableObject *object, int dx, int dy, int angleDegree)
{
  translate_service.translate(object, -dx, -dy);

  std::list<Coordinate*> new_cord_list;
  std::list<Coordinate*> cord_list = object->getCoordinates();
  std::list<Coordinate*>::iterator it;
  for(it = cord_list.begin(); it!=cord_list.end(); ++it)
  {

    Coordinate* cord = (*it);
    Matrix<double> point(1,3);
    point.set(0, 0, cord->getx());
    point.set(0, 1, cord->gety());
    point.set(0, 2, cord->getz());

    Matrix<double> offset1(3,3);
    offset1.set(0, 0, 1);
    offset1.set(1, 1, 1);
    offset1.set(2, 2, 1);
    offset1.set(2, 0, -1*dx);
    offset1.set(2, 1, -1*dy);

    double angleRad = angleDegree * pi / 180;

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

    Coordinate* new_cord = new Coordinate(pointRotated.get(0, 0),
                             pointRotated.get(0, 1),  pointRotated.get(0,2));

    new_cord_list.push_front(new_cord);
  }
  object->setCoordinates(new_cord_list);

  translate_service.translate(object, dx, dy);
}

void RotateObjectService::rotateCenterObject(DrawableObject *object, int angle)
{
  Coordinate *center = object->getCenter();
  rotate(object, center->getx(), center->gety(), angle);
}

void RotateObjectService::rotateCenterWorld(DrawableObject *object, int angle)
{
  rotate(object, 0, 0, angle);
}
