#ifndef GTKMM_APP_COORDENATE
#define GTKMM_APP_COORDENATE

class Coordenate
{
public:
  Coordenate(int x, int y)
  : cord_x(x), cord_y(y)
  {}
  ~Coordenate() {}
  int getx()
  {
    return cord_x;
  }
  int gety()
  {
    return cord_y;
  }
protected:
  int cord_x;
  int cord_y;
};
#endif // GTKMM_APP_COORDENATE
