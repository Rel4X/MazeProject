#ifndef		__CELL_H__
#define		__CELL_H__

#include	<iostream>

#define		CL_TOP	0
#define		CL_BOT	1
#define		CL_EAS	2
#define		CL_WES	3

class		Cell
{
 private:
  bool		p_visited;
  bool		p_door[4];

 public:
  Cell();
  ~Cell();

 public:
  bool		GetVisited() const;
  bool		GetTop() const;
  bool		GetBottom() const;
  bool		GetEast() const;
  bool		GetWest() const;
  bool		GetDir(unsigned int dir) const;
  void		SetVisited(bool v);
  void		SetTop(bool v);
  void		SetBottom(bool v);
  void		SetEast(bool v);
  void		SetWest(bool v);
  void		SetDir(unsigned int dir, bool v);

 public:
  void		PrintConsole() const;
  
};

#endif		// __CELL_H__
