#ifndef GTKMM_APP_ENUM_CLIPPING_TYPE
#define GTKMM_APP_ENUM_CLIPPING_TYPE

enum clipping_type {
  NONE = 0,
  POINT = 1,
  CS = 2,  // Cohen-Sutherland
  LB = 3,  // Liang-Barsky
  SH = 4,  // Sutherland–Hodgman
  POINT_CS = 5,
  POINT_LB = 6,
  POINT_CS_SH = 7,
  POINT_LB_SH = 8,
  POINT_SH = 9,
  CS_SH = 10,
  LB_SH = 11
};

#endif
