#include "display_file.hpp"

// Create the display file with a origin object
DisplayFile::DisplayFile()
{
  this->addObject(new Line(string("origin_x"), Coordinate(-10,0), Coordinate(10,0)));
  this->addObject(new Line(string("origin_y"), Coordinate(0,-10), Coordinate(0,10)));
  this->addObject(new Line(string("origin_z"), Coordinate(0,0,-10), Coordinate(0,0,10)));
}

DisplayFile::~DisplayFile()
{
  this->destroyMap();
}

void DisplayFile::addObject(DrawableObject* object)
{
  if (this->objectsMap.count(object->getName()))
  {
    // same object
    if (this->objectsMap.find(object->getName())->second == object) { return; }
    // delete older object with same
    removeObjectByName(object->getName());
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

list<string> DisplayFile::getNamesList()
{
  list<string> list;
  for(auto &key : objectsMap)
  {
    list.push_back(key.first);
  }
  return list;

}

list<DrawableObject*> DisplayFile::getObjects()
{
  list<DrawableObject*> list;
  for(auto &key : objectsMap){
    list.push_back(key.second);
  }
  return list;
}

void DisplayFile::destroyMap()
{
  for(auto &key : objectsMap)
  {
    delete key.second;
  }
}
