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
  std::list<Coordinate>::iterator it;
  for(it = cord_list.begin(); it!=cord_list.end(); ++it)
  {
    Matrix<int> object_bitmap(1, 3);
    Matrix<int> translate_bitmap(1, 3);

    object_bitmap.set(0, 0, (it)->getx());
    object_bitmap.set(0, 1, (it)->gety());
    object_bitmap.set(0, 2, (it)->getz());

    translate_bitmap.set(0, 0, dx);
    translate_bitmap.set(0, 1, dy);
    translate_bitmap.set(0, 2, dy);

    Matrix<int> new_bitmap = object_bitmap + translate_bitmap;

    Coordinate new_cord = Coordinate(new_bitmap.get(0, 0),
                            new_bitmap.get(0, 1), new_bitmap.get(0,2));
    new_cord_list.push_front(new_cord);
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
