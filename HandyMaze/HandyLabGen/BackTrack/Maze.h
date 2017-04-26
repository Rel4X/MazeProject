#ifndef		__MAZE_H__
#define		__MAZE_H__

#include	<iostream>
#include	"Cell.h"

class		Maze
{
 private:
  unsigned int	p_w;
  unsigned int	p_h;
  unsigned int	p_s;
  
 private:
  Maze() { }
  
 public:
  Maze(unsigned int w, unsigned int h);
  Maze(const Maze& m);
  ~Maze();

 public:
  unsigned int	GetWidth() const	{ return (this->p_w); }
  unsigned int	GetHeight() const	{ return (this->p_h); }
  unsigned int	GetSize() const		{ return (this->p_s); }

 public:
  bool		Init(unsigned int w, unsigned int l);
  
};

#endif		// __MAZE_H__
