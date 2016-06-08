#pragma once

#define		OPEN	1
#define		CLOSED	2	
#define		WALL	3

struct			Labz
{
	char**		lab;
	int			w;
	int			h;

public:
	Labz() : lab(0) { }
};