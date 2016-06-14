#include	<iostream>
#include	"LabLoader.h"
#include	"LabSolver.h"

int		main(int ac, char** av)
{
  LabLoader	ll;
  LabSolver	ls;
  bool		ret;

  if (ac < 2)
    { std::cout << "Missing Argument." << std::endl; return (0); }

  ll.LoadLab(av[1]);
  ret = ls.Solve(&ll);

  if (ret == false)
    { std::cout << "Can not solve maze." << std::endl; }

  return (0);
}
