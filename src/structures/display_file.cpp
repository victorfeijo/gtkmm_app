#include "display_file.hpp"

DisplayFile::DisplayFile()
{
  // add origin
  this->addObject(new Line(string("origin_x"), Coordinate(-10,0), Coordinate(10,0)));
  this->addObject(new Line(string("origin_y"), Coordinate(0,-10), Coordinate(0,10)));
  // this->addObject(new Line(string("origin_z"), Coordinate(0,0,-10), Coordinate(0,0,10)));
}

DisplayFile::~DisplayFile()
{
  this->destroyMap();
}

void DisplayFile::addObject(DrawableObject* object)
{
  if (this->objectsMap.count(object->getName()))
  {
    if (this->objectsMap.find(object->getName())->second == object)
    {  // same object
      return;
    }
    else
    {  // delete older object with same
      removeObjectByName(object->getName());
    }
  }
  this->objectsMap[object->getName()] = object;
}

DrawableObject* DisplayFile::getObjectByName(string name)
{
  return this->objectsMap.find(name)->second;
}

void DisplayFile::removeObjectByName(string name)
{
  DrawableObject* object = this->getObjectByName(name);
  this->objectsMap.erase(name);
  delete object;
}

std::list<string> DisplayFile::getNamesList()
{
  std::list<string> list;
  for(std::map<string, DrawableObject*>::iterator it = objectsMap.begin();
      it != objectsMap.end(); it++)
  {
    list.push_back(it->first);
  }
  return list;

}

std::list<DrawableObject*> DisplayFile::getObjects()
{
  std::list<DrawableObject*> list;
  for(std::map<string, DrawableObject*>::iterator it = objectsMap.begin();
      it != objectsMap.end(); it++)
  {
    list.push_back(it->second);
  }
  return list;

}

void DisplayFile::destroyMap()
{
  for (std::map<string, DrawableObject*>::iterator it=objectsMap.begin();
        it!=objectsMap.end(); ++it)
  {
    delete it->second;
  }
}
