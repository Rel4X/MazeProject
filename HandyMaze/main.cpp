#include		<iostream>
#include		<stdint.h>
#include		<inttypes.h>
#include		"HandyMaze.h"
#include		"AStarLabzSolver.h"
#include		"EasyBMP.h"

#define			WIN_WIDTH	600
#define			WIN_HEIGHT	600
#define			WIN_NAME	"HandyMaze"

int				main()
{
  HandyMaze			labz(1000, 1000);
  AStarLabzSolver		solver;
  Labz*				l;
  BMP				img;
  
  if (labz.Generate() == false)
    {
      std::cout << "Derp" << std::endl;
      return (1);
    }
  l = labz.GetFormatedLab();
  if (l == 0)
    {
      std::cout << "Dorp" << std::endl;
      return (1);
    }
  std::cout << "Generated" << std::endl;
  std::cout << "Allocating Image ..." << std::endl;
  if (img.SetBitDepth(1) == false)
    std::cout << "Failed to change Depth" << std::endl;
  img.SetSize(l->w, l->h);
  std::cout << "Filling Image ..." << std::endl;
  std::cout << l->w << " " << l->h << std::endl;
  for (int i = 0; i < l->w; ++i)
    for (int j = 0; j < l->h; ++j)
      {
	img(j, i)->Red = 255;
	img(j, i)->Green = 255;
	img(j, i)->Blue = 255;
	img(j, i)->Alpha = 0;
      }
  for (uint64_t i = 0; i < l->h; ++i)
    for (uint64_t j = 0; j < l->w; ++j)
      {
	if (l->lab[j][i] == WALL)
	  {
	    img(j, i)->Red = 0;
	    img(j, i)->Green = 0;
	    img(j, i)->Blue = 0;
	    img(j, i)->Alpha = 0;
	  }
      }
  std::cout << "Saving Image ..." << std::endl;
  img.WriteToFile("LabyZ.bmp");
  return (0);
}
