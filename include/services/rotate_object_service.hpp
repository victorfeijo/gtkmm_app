#ifndef GTKMM_APP_ROTATE_OBJECT_SERVICE
#define GTKMM_APP_ROTATE_OBJECT_SERVICE

#include <math.h>
#include "drawable_object.hpp"
#include "coordinate.hpp"
#include "matrix.hpp"
#include "vector.hpp"
#include "translate_object_service.hpp"
#include "transform_type.hpp"

using namespace std;

class RotateObjectService
{
public:
  RotateObjectService();
  ~RotateObjectService();
  void rotateX(DrawableObject *object, int dx, int dy, int dz,
               int angle, transform_type type = ON_WORLD);
  void rotateY(DrawableObject *object, int dx, int dy, int dz,
               int angle, transform_type type = ON_WORLD);
  void rotateZ(DrawableObject *object, int dx, int dy, int dz,
               int angle, transform_type type = ON_WORLD);
  void rotateAxis(DrawableObject *object, Vector vec, int angle);

protected:
  TranslateObjectService translate_service;
  void rotate(DrawableObject *object, int dx, int dy, int dz,
              Matrix<double> transform_matrix, transform_type type = ON_WORLD);

};

#endif
