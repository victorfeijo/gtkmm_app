#include "scale_object_service.hpp"

ScaleObjectService::ScaleObjectService()
{
}

ScaleObjectService::~ScaleObjectService()
{
}

void ScaleObjectService::scale(DrawableObject* object, int sx, int sy)
{
  std::list<Coordinate*> new_cord_list;
  std::list<Coordinate*> cord_list = object->getCoordinates();
  std::list<Coordinate*>::iterator it;
  for(it = cord_list.begin(); it!=cord_list.end(); ++it)
  {
    Matrix<int> object_bitmap(1, 2);
    Matrix<int> scale_bitmap(2, 2);

    object_bitmap.set(0, 0, (*it)->getx());
    object_bitmap.set(0, 1, (*it)->gety());

    scale_bitmap.set(0, 0, sx);
    scale_bitmap.set(0, 1, 0);
    scale_bitmap.set(1, 0, 0);
    scale_bitmap.set(1, 1, sy);

    Matrix<int> new_bitmap = object_bitmap * scale_bitmap;
    Coordinate* new_cord = new Coordinate(new_bitmap.get(0, 0), new_bitmap.get(0, 1));
    new_cord_list.push_front(new_cord);
  }
  object->setCoordinates(new_cord_list);
}
