#include "display_file.h"

DisplayFile::DisplayFile()
{
}

DisplayFile::~DisplayFile()
{
}

void DisplayFile::addObject(DrawableObject* object)
{
  this->objects[object->getName()] = object;
}

DrawableObject* DisplayFile::getObjectByName(string name)
{
  return this->objects.find(name)->second;
}

void DisplayFile::removeObject(DrawableObject* object)
{
  this->removeObjectByName(object->getName());
}

void DisplayFile::removeObjectByName(string name)
{
  this->objects.erase(name);
}

std::list<string> DisplayFile::getNamesList()
{
  std::list<string> list;
  for(std::map<string, DrawableObject*>::iterator it = objects.begin();
      it != objects.end(); it++)
  {
    list.push_back(it->first);
  }
  return list;

}
