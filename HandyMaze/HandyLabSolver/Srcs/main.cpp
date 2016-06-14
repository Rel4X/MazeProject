#include	<iostream>
#include	"LabLoader.h"
#include	"LabSolver.h"
#include	"LabDrawer.h"

int		main(int ac, char** av)
{
  LabLoader	ll;
  LabSolver	ls;
  bool		ret;
  char*		fname;

  if (ac < 3)
    { std::cout << "Missing Argument." << std::endl; return (0); }

  fname = av[2];

  ll.LoadLab(av[1]);
  ret = ls.Solve(&ll);

  LabDrawer::DrawToBMP(ll.GetLab(), av[2]);

  if (ret == false)
    { std::cout << "Can not solve maze." << std::endl; }

  return (0);
}
