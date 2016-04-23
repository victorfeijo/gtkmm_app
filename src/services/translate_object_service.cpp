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
  for(Coordinate cord : cord_list)
  {
    Matrix<double> object_bitmap(1, 3);
    Matrix<double> translate_bitmap(1, 3);

    object_bitmap.set(0, 0, cord.getx());
    object_bitmap.set(0, 1, cord.gety());
    object_bitmap.set(0, 2, cord.getz());

    translate_bitmap.set(0, 0, dx);
    translate_bitmap.set(0, 1, dy);
    translate_bitmap.set(0, 2, dy);

    Matrix<double> new_bitmap = object_bitmap + translate_bitmap;

    Coordinate new_cord = Coordinate(new_bitmap.get(0, 0),
                            new_bitmap.get(0, 1), new_bitmap.get(0,2));
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
}
