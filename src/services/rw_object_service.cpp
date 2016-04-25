#include "rw_object_service.hpp"

RwObjectService::RwObjectService()
{
  setlocale(LC_NUMERIC, "en_US.UTF-8");
}

RwObjectService::~RwObjectService()
{
}

list<DrawableObject*> RwObjectService::read(string file_path)
{
  list<Coordinate> cord_list;
  list<DrawableObject*> objects_list;
  string line;
  ifstream myfile(file_path);
  string groupname = "#";
  int groupfaces = 0;
  if(myfile.is_open())
  {
    while(getline(myfile, line))
    {
      char* content = const_cast<char*>(line.c_str());
      char* tag = strtok(content, " \t\r");
      if (tag == NULL)  // empty line
      {
        continue;
      }
      else if (strcmp(tag, "v") == 0)
      {
        double x, y, z;
        istringstream(strtok(NULL, " \t\r")) >> x;
        istringstream(strtok(NULL, " \t\r")) >> y;
        istringstream(strtok(NULL, " \t\r")) >> z;
        cord_list.push_back(Coordinate(x, y, z));
      }
      else if (strcmp(tag, "g") == 0)
      {
        groupfaces = 0;
        int pos = line.find(tag);
        groupname = line.substr(pos+2, line.length());
      }
      else if (strcmp(tag, "f") == 0 || strcmp(tag, "curv2") == 0)
      {
        string facename = groupname;
        if (groupfaces != 0)
        {
          facename += "#" + to_string(groupfaces);
        }
        groupfaces++;
        list<Coordinate> current_cord_list;
        for (char *cord_index = strtok(NULL, " \t\r"); cord_index != NULL;
            cord_index = strtok(NULL, " \t\r"))
        {
          list<Coordinate>::iterator it = cord_list.begin();
          advance(it, atoi(cord_index)-1);
          current_cord_list.push_back(*it);
        }
        DrawableObject *object;
        if (current_cord_list.size() == 1)
        {
          object = new Point(facename, current_cord_list.front());
        }
        else if (cord_list.size() == 2)
        {
          Coordinate cord_x = current_cord_list.front();
          Coordinate cord_y = current_cord_list.back();
          object = new Line(facename, cord_x, cord_y);
        }
        else
        {
          if (strcmp(tag, "curv2") == 0)
          {
            object = new Curve2D(facename, current_cord_list);
          }
          else
          {
            object = new WireFrame(facename, current_cord_list);
          }
        }
        objects_list.push_back(object);
      }
    }
    myfile.close();
  }
  return objects_list;
}

void RwObjectService::write(list<DrawableObject*> objects_list, string file_path)
{
  ofstream myfile;
  myfile.open(file_path);
  myfile << "# List of vertices\n";
  for (DrawableObject* obj : objects_list)
  {
    for (Coordinate cord : obj->getCoordinatesWorld())
    {
      myfile << "v " << std::fixed << cord.getx() << " " << cord.gety() << " "
          << cord.getz() << "\n";
    }
  }
  myfile << "\n# List of objects\n";
  int current_vertice = 1;
  for (DrawableObject* obj : objects_list)
  {
    myfile << "g " + obj->getName() + "\n";
    if (obj->getType() == CURVE2D)
    {
      myfile << "curv2";
    }
    else
    {
      myfile << "f";
    }
    for (Coordinate cord : obj->getCoordinatesWorld())
    {
      myfile << " " + to_string(current_vertice++);
    }
    myfile << "\n";
  }
  myfile.close();
}
