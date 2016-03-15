#pragma once

/*
	Purpose : LabzDrawer draws a formated Maze.
*/

#include	"EasyBMP.h"
#include	"Labz.h"

class		LabzDrawer
{
public:
	LabzDrawer(void);
	~LabzDrawer(void);

public:
	bool	DrawToFile(const Labz*, const char*, bool);
};

