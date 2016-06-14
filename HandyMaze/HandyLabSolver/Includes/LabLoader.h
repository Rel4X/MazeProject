#pragma once

#include	<iostream>
#include	<sys/stat.h>
#include	<sys/types.h>
#include	<unistd.h>
#include	<fstream>
#include	<string>
#include	<string.h>

#include	"Labz.h"

class		LabLoader
{
 private:
  Labz		p_lab;
  bool		p_loaded;

 public:
  LabLoader();
  ~LabLoader();

 public:
  Labz*		GetLab() { return (&this->p_lab); }

 public:
  bool		LoadLab(const char* fname);
  char		Get(unsigned int x, unsigned int y);
  void		Set(unsigned int x, unsigned int y, char v);
  void		PrintConsole();

 private:
  bool		LoadContent(const char* fname);
};
