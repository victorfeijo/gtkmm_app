#include "display_file.hpp"
#include "curve_2d.hpp"

DisplayFile::DisplayFile()
{
  // add origin
  this->addObject(new Line(string("origin_x"), Coordinate(-10,0), Coordinate(10,0)));
  this->addObject(new Line(string("origin_y"), Coordinate(0,-10), Coordinate(0,10)));
  // this->addObject(new Line(string("origin_z"), Coordinate(0,0,-10), Coordinate(0,0,10)));

  //TEST 2D CURVE
  std::list<Vector> veclist;
  veclist.push_back(Vector(Coordinate(31,17), Coordinate(30,299)));
  veclist.push_back(Vector(Coordinate(401,296), Coordinate(398,403)));
  veclist.push_back(Vector(Coordinate(444,21), Coordinate(370,115)));
  this->addObject(new Curve2D("Curve", veclist));

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
  for(auto &key : objectsMap)
  {
    list.push_back(key.first);
  }
  return list;

}

std::list<DrawableObject*> DisplayFile::getObjects()
{
  std::list<DrawableObject*> list;
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
