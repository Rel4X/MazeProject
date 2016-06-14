#pragma once

#include	"EasyBMP.h"
#include	"Labz.h"

class		LabDrawer
{
 public:
  LabDrawer();
  ~LabDrawer();

 public:
  static  bool		DrawToBMP(const Labz* l, const char* fname);
};
