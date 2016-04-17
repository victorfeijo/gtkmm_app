#include "clipping_service.hpp"
#include "view_window.hpp"

ClippingService::ClippingService()
{
}

ClippingService::~ClippingService()
{
}

void ClippingService::clip(ViewWindow* window, DrawableObject *object)
{
  clipping_type type = window->getClippingType();
  std::list<Coordinate> coordinatesWindow = object->getCoordinatesWindow();
  int size = coordinatesWindow.size();

  switch (size) {
    case 1:  // point
      switch(type) {
        case POINT:
          clipPoint(window, object);
          break;
        default:
          goto USE_SAME_CORDINATES;
          break;
      }
      break;
    default:
      goto USE_SAME_CORDINATES;
      break;
  }
  return;
  USE_SAME_CORDINATES:
  object->setCoordinatesClipped(object->getCoordinatesWindow());
}

void ClippingService::clipPoint(ViewWindow* window, DrawableObject *object)
{
  std::list<Coordinate> windowCordList = object->getCoordinatesWindow();
  windowCordList.front();
  if (isCordOnWindow(windowCordList.front(), window))
  {
    object->setCoordinatesClipped(windowCordList);
  }
  else
  {
    object->setCoordinatesClipped(std::list<Coordinate>());
  }
}

bool ClippingService::isCordOnWindow(Coordinate cord, ViewWindow *window)
{
  int x = cord.getx();
  int y = cord.gety();
  if (window->getXwmin() <= x && x <= window->getXwmax() &&
      window->getYwmin() <= y && y <= window->getYwmax())
  {
    return true;
  }
  else
  {
    return false;
  }
}
