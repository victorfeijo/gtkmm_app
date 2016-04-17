#include "rw_object_service.hpp"

RwObjectService::RwObjectService()
{
}

RwObjectService::~RwObjectService()
{
}

list<DrawableObject*> RwObjectService::read(string file_path)
{
  list<DrawableObject*> objects_list;
  string line;
  ifstream myfile(file_path);
  list<Coordinate> cord_list;
  string name;
  if(myfile.is_open())
  {
    while(getline(myfile, line))
    {
      if (line.front() == 'o')
      {
        name = line.substr(2, line.length());
      }
      if (line.front() == 'v')
      {
        vector<string> sep = split(line, ' ');
        Coordinate* cord;
        if (sep.size() > 3)
        {
          cord = new Coordinate(atof(sep[1].c_str()), atof(sep[2].c_str()), atof(sep[3].c_str()));
        }
        else
        {
          cord = new Coordinate(atof(sep[1].c_str()), atof(sep[2].c_str()));
        }
        cord_list.push_back(*cord);
      }
      if (line.front() == 'f')
      {
        DrawableObject *object;
        if (cord_list.size() == 1)
        {
          object = new Point(name, cord_list.front());
        }
        else if (cord_list.size() == 2)
        {
          Coordinate cord_x = cord_list.front();
          Coordinate cord_y = cord_list.back();
          object = new Line(name, cord_x, cord_y);
        }
        else
        {
          object = new WireFrame(name, cord_list);
        }
        objects_list.push_back(object);
        cord_list = * new list<Coordinate>;
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
  myfile << "# Starting the file objects\n\n";
  for (DrawableObject* obj : objects_list)
  {
    myfile << "o " + obj->getName() + "\n\n";
    list<Coordinate> objectCoordinates = obj->getCoordinatesWorld();
    for (Coordinate cord : objectCoordinates)
    {
      string line_cord = "v " + to_string(cord.getx()) + " " + to_string(cord.gety())
      + " " + to_string(cord.getz()) + "\n";
      myfile << line_cord;
    }
    myfile << "\nf ";
    for (unsigned int i = 1; i < objectCoordinates.size()+1; i++)
    {
      myfile << to_string(i) + " ";
    }
    myfile << "\n\n";
  }
  myfile.close();
}

vector<string> RwObjectService::split(string str, char delimiter)
{
  vector<string> internal;
  stringstream ss(str); // Turn the string into a stream.
  string tok;

  while(getline(ss, tok, delimiter)) {
    internal.push_back(tok);
  }

  return internal;
}
