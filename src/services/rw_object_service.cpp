#include "rw_object_service.hpp"

RwObjectService::RwObjectService()
{
}

RwObjectService::~RwObjectService()
{
}

list<DrawableObject*> RwObjectService::read(string file_path)
{

}

void RwObjectService::write(list<DrawableObject*> objects_list, string file_path)
{
  ofstream myfile;
  myfile.open(file_path);
  myfile << "# Starting the file objects\n\n";
  for (list<DrawableObject*>::iterator it_obj = objects_list.begin();
        it_obj != objects_list.end(); ++it_obj)
  {
    myfile << "o " + (*it_obj)->getName() + "\n\n";
    list<Coordinate*> objectCoordinates = (*it_obj)->getCoordinates();
    for (std::list<Coordinate*>::iterator it_cord = objectCoordinates.begin();
          it_cord != objectCoordinates.end(); ++it_cord)
    {
      string line_cord = "v " + to_string((*it_cord)->getx()) + " " + to_string((*it_cord)->gety())
      + " " + to_string((*it_cord)->getz()) + "\n";
      myfile << line_cord;
    }
    myfile << "\nf ";
    for (int i = 1; i < objectCoordinates.size()+1; i++)
    {
      myfile << to_string(i) + " ";
    }
    myfile << "\n\n";
  }
  myfile.close();
}
