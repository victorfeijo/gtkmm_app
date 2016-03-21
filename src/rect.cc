#include "rect.h"

Rect::Rect(string name, Coordenate* rect_cord1, Coordenate* rect_cord2)
: DrawableObject(name)
{
  coordenates.push_back(rect_cord1);
  coordenates.push_back(rect_cord2);
}

Rect::~Rect()
{
}

list<Coordenate*> Rect::getCoordenates()
{
  return coordenates;
}
