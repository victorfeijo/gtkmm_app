#ifndef GTKMM_APP_ENUM_CLIPPING_TYPE
#define GTKMM_APP_ENUM_CLIPPING_TYPE

enum clipping_type {
  NONE = 0,
  POINT = 1,
  CS = 2,  // Cohen-Sutherland
  POINT_CS = 3
};

#endif
