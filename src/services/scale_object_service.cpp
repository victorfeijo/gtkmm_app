#include "scale_object_service.hpp"

ScaleObjectService::ScaleObjectService()
{
}

ScaleObjectService::~ScaleObjectService()
{
}

void ScaleObjectService::scale(DrawableObject* object, double sx, double sy, double sz)
{
  Coordinate center_cord = object->getCenterOnWorld();
  translate_service.translate(object, center_cord.getx() *- 1, center_cord.gety() *- 1);

  std::list<Coordinate> new_cord_list;
  std::list<Coordinate> cord_list = object->getCoordinatesWorld();

  Matrix<double> scale_bitmap(3, 3);
  scale_bitmap.set(0, 0, sx);
  scale_bitmap.set(1, 1, sy);
  scale_bitmap.set(2, 2, sz);

  for(Coordinate cord : cord_list)
  {
    Matrix<double> object_bitmap = cord.toMatrix();
    Matrix<double> new_bitmap = object_bitmap * scale_bitmap;
    new_cord_list.push_back(Coordinate(new_bitmap));
  }
  object->setCoordinatesWorld(new_cord_list);
  translate_service.translate(object, center_cord.getx(), center_cord.gety());
}
