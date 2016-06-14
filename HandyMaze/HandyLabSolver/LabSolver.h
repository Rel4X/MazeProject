#pragma once

#include	"LabLoader.h"

class		LabSolver
{
 private:
  LabLoader*	p_labl;
  Labz*		p_lab;

 public:
  LabSolver();
  ~LabSolver();

 public:
  bool		Solve(LabLoader* lab);

 private:
  bool		Track(unsigned int px, unsigned int py);
};
