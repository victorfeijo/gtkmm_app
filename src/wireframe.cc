#include "wireframe.h"

WireFrame::WireFrame(string name, list<Coordenate*> coordenates)
: DrawableObject(name, coordenates)
{
  //nothing for while
}

WireFrame::~WireFrame()
{
}

list<Coordenate*> WireFrame::getCoordenates()
{
  return coordenates;
}
