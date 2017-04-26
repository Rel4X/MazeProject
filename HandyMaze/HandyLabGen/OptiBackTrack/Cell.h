#ifndef		__CELL_H__
#define		__CELL_H__

#include	<iostream>
#include	<map>

#define		CL_TOP	0
#define		CL_BOT	1
#define		CL_EAS	2
#define		CL_WES	3
#define		CL_VIS	4

class		Cell
{
 private:
  static std::map<unsigned int, char>	p_mask;
  char		p_data;

 public:
  Cell();
  ~Cell();

 public:
  bool		GetVisited();
  bool		GetTop();
  bool		GetBottom();
  bool		GetEast();
  bool		GetWest();
  bool		GetDir(unsigned int dir);
  void		SetVisitedTrue();
  void		SetVisitedFalse();
  void		SetTopTrue();
  void		SetTopFalse();
  void		SetBottomTrue();
  void		SetBottomFalse();
  void		SetEastTrue();
  void		SetEastFalse();
  void		SetWestTrue();
  void		SetWestFalse();
  void		SetDirTrue(unsigned int d);
  void		SetDirFalse(unsigned int d);

 public:
  void		PrintConsole();
  
};

#endif		// __CELL_H__
