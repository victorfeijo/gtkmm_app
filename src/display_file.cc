// #include "world.h"
//
// DisplayFile::DisplayFile()
// {
// }
//
// DisplayFile::~DisplayFile()
// {
// }
//
// void DisplayFile::addObject(DrawbleObject object)
// {
//   this->map[object.getName()] = object;
// }
//
// DrawbleObject DisplayFile::getObjectByName(string name)
// {
//   return this->map.find(name)->second;
// }
//
// void DisplayFile::removeObject(DrawbleObject object)
// {
//   this->removeObjectByName(object.getName());
// }
//
// void DisplayFile::removeObjectByName(string name)
// {
//   this->map.erase(name);
// }
//
// std::list<string> DisplayFile::getNamesList()
// {
//   std::list<string> list;
//   for(std::map<string, DrawbleObject>::iterator it = map.begin();
//       it != map.end(); it++)
//   {
//     list.push_back(it->first);
//   }
//   return list;
//
// }
