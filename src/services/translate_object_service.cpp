#include "translate_object_service.hpp"

TranslateObjectService::TranslateObjectService()
{
}

TranslateObjectService::~TranslateObjectService()
{
}

void TranslateObjectService::translate(DrawableObject* object, int dx, int dy, int dz, transform_type type)
{
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
  Matrix<double> translate_bitmap = Coordinate(dx, dy, dz).toMatrix();
  for(Coordinate cord : cord_list)
  {
    Matrix<double> object_bitmap = cord.toMatrix();
    Matrix<double> new_bitmap = object_bitmap + translate_bitmap;
    new_cord_list.push_back(Coordinate(new_bitmap));
  }
  switch (type) {
    case transform_type::ON_WORLD:
      object->setCoordinatesWorld(new_cord_list);
    break;
    case transform_type::ON_WINDOW:
      object->setCoordinatesWindow(new_cord_list);
    break;
  }
}
