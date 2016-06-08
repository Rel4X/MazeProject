#pragma once

/*
  Purpose : LabzDrawer draws a formated Maze in .txt or .bmp
  Which is nice.
*/

#include	"EasyBMP.h"
#include	"Labz.h"

class		LabzDrawer
{
 public:
  LabzDrawer(void);
  ~LabzDrawer(void);
  
 public:
  bool	DrawToFile(const Labz*, const char*, bool);
  bool	DrawToTXT(const Labz*, const char*);
};
