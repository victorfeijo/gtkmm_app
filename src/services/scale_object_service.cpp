#include "scale_object_service.hpp"

ScaleObjectService::ScaleObjectService()
{
}

ScaleObjectService::~ScaleObjectService()
{
}

void ScaleObjectService::scale(DrawableObject* object, double sx, double sy)
{
  Coordinate center_cord = object->getCenterOnWorld();
  translate_service.translate(object, center_cord.getx() *- 1, center_cord.gety() *- 1);

  std::list<Coordinate> new_cord_list;
  std::list<Coordinate> cord_list = object->getCoordinatesWorld();
  std::list<Coordinate>::iterator it;
  for(it = cord_list.begin(); it!=cord_list.end(); ++it)
  {
    Matrix<double> object_bitmap(1, 3);
    Matrix<double> scale_bitmap(3, 3);

    object_bitmap.set(0, 0, (it)->getx());
    object_bitmap.set(0, 1, (it)->gety());
    object_bitmap.set(0, 2, (it)->getz());

    scale_bitmap.set(0, 0, sx);
    scale_bitmap.set(1, 1, sy);
    scale_bitmap.set(2, 2, 1);

    Matrix<double> new_bitmap = object_bitmap * scale_bitmap;
    Coordinate new_cord = Coordinate(new_bitmap.get(0, 0), new_bitmap.get(0, 1), new_bitmap.get(0, 2));
    new_cord_list.push_front(new_cord);
  }
  object->setCoordinatesWorld(new_cord_list);
  translate_service.translate(object, center_cord.getx(), center_cord.gety());
}
