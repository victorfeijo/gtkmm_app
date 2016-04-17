#ifndef GTKMM_APP_ENUM_CLIPPING_TYPE
#define GTKMM_APP_ENUM_CLIPPING_TYPE

enum clipping_type {
  NONE = 0,
  POINT = 1,
  CS = 2,  // Cohen-Sutherland
  LB = 3,  // Liang-Barsky
  POINT_CS = 4,
  POINT_LB = 5
};

#endif
