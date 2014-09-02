#include		<iostream>
#include		"HandyMaze.h"
#include		"RxImage.h"
#include		"AStarLabzSolver.h"

#define			WIN_WIDTH	600
#define			WIN_HEIGHT	600
#define			WIN_NAME	"HandyMaze"

int				main()
{
  HandyMaze			labz(100, 100);
  AStarLabzSolver		solver;
  Labz*				l;
  RxImage			img;
  
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
  img.Create(l->w, l->h);
  std::cout << "Filling Image ..." << std::endl;
  std::cout << l->w << " " << l->h << std::endl;
  for (int i = 0; i < l->w; ++i)
    for (int j = 0; j < l->h; ++j)
      img.SetPixel(j, i, 255, 255, 255);
  for (uint64_t i = 0; i < l->h; ++i)
    for (uint64_t j = 0; j < l->w; ++j)
      {
	if (l->lab[j][i] == WALL)
	  img.SetPixel(j, i, 0, 0, 0);
      }
  std::cout << "Saving Image ..." << std::endl;
  img.SaveToJpeg("CLEAR.jpg");
  return (0);
}
