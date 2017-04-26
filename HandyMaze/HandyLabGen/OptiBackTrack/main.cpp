#include	<iostream>
#include	<map>
#include	<stack>
#include	<fstream>
#include	"Grid1D.hpp"
#include	"Cell.h"
#include	"RandomMachine.h"
#include	"EasyBMP.h"

#include	<unistd.h>

struct		Direction
{
  int		x;
  int		y;
  int		dir;
  int		opp;

  Direction(int nx, int ny, int nd, int no)
  {
    x = nx;
    y = ny;
    dir = nd;
    opp = no;
  };

  ~Direction() { }
};

#define		CL_TOP	0
#define		CL_BOT	1
#define		CL_EAS	2
#define		CL_WES	3
#define		CL_VIS	4

Direction	Directions[4] = {
  Direction(0, -1, CL_TOP, CL_BOT),
  Direction(0, 1, CL_BOT, CL_TOP),
  Direction(1, 0, CL_EAS, CL_WES),
  Direction(-1, 0, CL_WES, CL_EAS)
};

typedef		std::pair<int, int>	Coords;

Direction*	DirAvailable[4] = {
  NULL, NULL, NULL, NULL
};

unsigned int		NDirAvailable = 0;

#define		GF_EMPTY	'*'
#define		GF_WALL		'X'

void			CheckOuts(Coords* c, Grid1D<Cell>* g)
{
  int			NX;
  int			NY;
  
  NDirAvailable = 0;
  for (unsigned int i = 0; i < 4; ++i)
    {
      NX = c->first + Directions[i].x;
      NY = c->second + Directions[i].y;
      if (NX >= 0 && NX < g->GetWidth()
	  && NY >= 0 && NY < g->GetHeight()
	  && g->GetElement(NX, NY)->GetVisited() == false)
	{
	  DirAvailable[NDirAvailable] = &Directions[i];
	  ++NDirAvailable;
	}
    }
}

void			ToFile(char** g, unsigned int w, unsigned int h)
{
  std::ofstream		o;

  o.open("OUTPUT.txt");
  for (unsigned int i = 0; i < h; ++i)
    {
      for (unsigned int j = 0; j < w; ++j)
	{
	  o << g[i][j];
	}
      if (i != h - 1)
	o << "\n";
    }
}

void			ToImage(char** g, unsigned int w, unsigned int h)
{
  BMP	Image;
  
  if (Image.SetSize(w, h) == false)
    { return ; }
  
  Image.SetBitDepth(1);
  
  for (int i = 0; i < w; ++i)
    {
      for (int j = 0; j < h; ++j)
	{
	  if (g[i][j] == 'X')
	    {
	      Image(i, j)->Red = 0;
	      Image(i, j)->Green = 0;
	      Image(i, j)->Blue = 0;
	    }
	  else
	    {
	      Image(i, j)->Red = 255;
	      Image(i, j)->Green = 255;
	      Image(i, j)->Blue = 255;
	    }
	  Image(i, j)->Alpha = 0;
	}
    }
  Image.WriteToFile("Limage.bmp");

}

void			Show(char** g, unsigned int w, unsigned int h)
{
  for (unsigned int i = 0; i < h; ++i)
    {
      for (unsigned int j = 0; j < w; ++j)
	{
	  std::cout << g[i][j];
	}
      if (i != h - 1)
	std::cout << std::endl;
    }
}

void			ShowLab(Grid1D<Cell>* g)
{
  char**		gout;
  unsigned int		x;
  unsigned int		y;

  try
    {
      gout = new char*[g->GetHeight() * 2 - 1];
      for (unsigned int i = 0; i < g->GetHeight() * 2 - 1; ++i)
	{
	  gout[i] = new char[g->GetWidth() * 2 - 1];
	}
    }
  catch (...)
    {
      std::cout << "LE SHOW" << std::endl;
    }
  y = 0;

  for (unsigned int i = 0; i < g->GetHeight(); ++i)
    {
      x = 0;
      for (unsigned int j = 0; j < g->GetWidth(); ++j)
	{
	  if (g->GetElement(j, i)->GetVisited() == true)
	    {
	      gout[y][x] = GF_EMPTY;
	    }
	  else
	    {
	      gout[y][x] = GF_WALL;
	    }
	  if (j + 1 < g->GetWidth())
	    {
	      if (g->GetElement(j, i)->GetEast() == true)
		{
		  gout[y][x + 1] = GF_EMPTY;
		}
	      else
		{
		  gout[y][x + 1] = GF_WALL;
		}
	    }
	  if (i + 1 < g->GetHeight())
	    {
	      if (g->GetElement(j, i)->GetBottom() == true)
		{
		  gout[y + 1][x] = GF_EMPTY;
		}
	      else
		{
		  gout[y + 1][x] = GF_WALL;
		}
	    }
	  if (i + 1 < g->GetHeight() && j + 1 < g->GetWidth())
	    {
	      gout[y + 1][x + 1] = GF_WALL;
	    }
	  x += 2;
	}
      y += 2;
    }
  Show(gout, x - 1, y - 1);
}

void			Generate(unsigned int w, unsigned int y)
{
  Grid1D<Cell>*		grid;
  Coords		cur;
  std::stack<Coords>	stck;
  bool			end;
  unsigned int		door;

  try
    {
      grid = new Grid1D<Cell>(w, y);
    }
  catch (...)
    {
      std::cout << "LA GRID" << std::endl;
      return ;
    }

  end = false;
  cur.first = 0;
  cur.second = 0;
  grid->GetElement(cur.first, cur.second)->SetVisitedTrue();
  while (!end)
    {
      CheckOuts(&cur, grid);
      if (NDirAvailable == 0)
	{
	  cur.first = stck.top().first;
	  cur.second = stck.top().second;
	  stck.pop();
	}
      else if (NDirAvailable == 1)
	{
	  grid->GetElement(cur.first, cur.second)->SetDirTrue(DirAvailable[0]->dir);
	  cur.first = cur.first + DirAvailable[0]->x;
	  cur.second = cur.second + DirAvailable[0]->y;
	  grid->GetElement(cur.first, cur.second)->SetDirTrue(DirAvailable[0]->opp);
	  grid->GetElement(cur.first, cur.second)->SetVisitedTrue();
	}
      else
	{ 
	  stck.emplace(cur);
	  door = RandomMachine::Randomize(0, NDirAvailable - 1);
	  
	  grid->GetElement(cur.first, cur.second)->SetDirTrue(DirAvailable[door]->dir);
	  cur.first = cur.first + DirAvailable[door]->x;
	  cur.second = cur.second + DirAvailable[door]->y;
	  grid->GetElement(cur.first, cur.second)->SetDirTrue(DirAvailable[door]->opp);
	  grid->GetElement(cur.first, cur.second)->SetVisitedTrue();
	}
      if (stck.size() == 0)
	end = true;
    }

  ShowLab(grid);
}

int		main(int ac, char** av)
{
  //std::cout << sizeof(long) << std::endl;
  Generate(50, 50);
  return (0);
}
