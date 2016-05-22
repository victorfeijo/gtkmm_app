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
  list<Coordinate> group_cord_list;
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
        if (!group_cord_list.empty())
        {
          objects_list.push_back(addGroup(group_cord_list, groupname));
        }
        group_cord_list.clear();
        int pos = line.find(tag);
        groupname = line.substr(pos+2, line.length());
      }
      else if ( strcmp(tag, "f") == 0 ||
                strcmp(tag, "curv2bz") == 0 ||
                strcmp(tag, "curv2sp") == 0 )
      {
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
          object = new Point(groupname, current_cord_list.front());
        }
        else if (current_cord_list.size() == 2)
        {
          Coordinate cord_x = current_cord_list.front();
          Coordinate cord_y = current_cord_list.back();
          group_cord_list.push_back(cord_x);
          group_cord_list.push_back(cord_y);
          object = NULL;
        }
        else
        {
          if (strcmp(tag, "curv2bz") == 0)
          {
            object = new Curve2D(groupname, current_cord_list, BEZIER2D);
          }
          else if (strcmp(tag, "curv2sp") == 0)
          {
            object = new Curve2D(groupname, current_cord_list, BSPLINE2D);
          }
          else
          {
            object = new WireFrame(groupname, current_cord_list);
          }
        }
        if (object != NULL)
        {
          objects_list.push_back(object);
        }
      }
    }
    if (!group_cord_list.empty())
    {
      objects_list.push_back(addGroup(group_cord_list, groupname));
    }
    myfile.close();
  }
  return objects_list;
}

DrawableObject* RwObjectService::addGroup(list<Coordinate> cord_list, string name)
{
  DrawableObject* object;
  if (cord_list.size() == 2)
  {
    Coordinate cord_x = cord_list.front();
    Coordinate cord_y = cord_list.back();
    object = new Line(name, cord_x, cord_y);
  }
  else
  {
    object = new Object3D(name, cord_list);
  }
  return object;
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
    if (obj->getType() == BEZIER2D)
    {
      myfile << "curv2bz";
    }
    else if (obj->getType() == BSPLINE2D)
    {
      myfile << "curv2sp";
    }
    else
    {
      myfile << "f";
    }
    int k = 0;
    for (Coordinate cord : obj->getCoordinatesWorld())
    {
      myfile << " " + to_string(current_vertice++);
      if (k % 2 == 1)
      {
      myfile << "\nf";
      }
      k++;
    }
    myfile << "\n";
  }
  myfile.close();
}
