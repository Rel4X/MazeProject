#pragma once

#define		WALL	'X'
#define		WAY	'*'
#define		PATH	'o'
#define		VISIT	'8'

struct	Labz
{
  unsigned int	w;
  unsigned int	h;
  unsigned int	xe;
  unsigned int	ye;
  char*		shebangs;
};
