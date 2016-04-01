#include "translate_object_service.hpp"

TranslateObjectService::TranslateObjectService()
{
}

TranslateObjectService::~TranslateObjectService()
{
}

void TranslateObjectService::translate(DrawableObject* object, int dx, int dy)
{
  std::list<Coordinate*> new_cord_list;
  std::list<Coordinate*> cord_list = object->getCoordinates();
  std::list<Coordinate*>::iterator it;
  for(it = cord_list.begin(); it!=cord_list.end(); ++it)
  {
    Matrix<int> object_bitmap(1, 2);
    Matrix<int> translate_bitmap(1, 2);

    object_bitmap.set(0, 0, (*it)->getx());
    object_bitmap.set(0, 1, (*it)->gety());

    translate_bitmap.set(0, 0, dx);
    translate_bitmap.set(0, 1, dy);

    Matrix<int> new_bitmap = object_bitmap + translate_bitmap;

    Coordinate* new_cord = new Coordinate(new_bitmap.get(0, 0), new_bitmap.get(0, 1));
    new_cord_list.push_front(new_cord);
  }
  object->setCoordinates(new_cord_list);
}
