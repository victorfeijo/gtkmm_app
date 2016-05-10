#ifndef GTKMM_APP_ENUM_CLIPPING_TYPE
#define GTKMM_APP_ENUM_CLIPPING_TYPE

enum clipping_type
{
  NONE = 0,
  PC = 1,  // Point clipping
  CS = 2,  // Cohen-Sutherland
  LB = 3,  // Liang-Barsky
  SH = 4,  // Sutherland–Hodgman
  PC_CS = 5,
  PC_LB = 6,
  PC_CS_SH = 7,
  PC_LB_SH = 8,
  PC_SH = 9,
  CS_SH = 10,
  LB_SH = 11
};

#endif
