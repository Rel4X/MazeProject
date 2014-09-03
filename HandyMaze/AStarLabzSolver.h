#pragma once

#include		<map>
#include		<utility>
#include		"HandyMaze.h"

#define			STARTING_BLOC	10
#define			ARRIVAL			20
#define			IN_OPEN			30
#define			IN_CLOSED		40
#define			IN_PATH			50

class			AStarLabzSolver
{
private:
	std::map<int, std::pair<int, int>*>	openList_;
	std::map<int, std::pair<int, int>*>	closedList_;
	unsigned int	x_cur;
	unsigned int	y_cur;
	unsigned int	x_end;
	unsigned int	y_end;

public:
	AStarLabzSolver(void);
	~AStarLabzSolver(void);

public:
	void		Solve(Labz*);

private:
	void		Clean();
	int			GetId(int, int, int);
	int			GetManathanToEnd(int, int);
	void		OpenTrial(Labz*, int, int, int);
	void		RecoverPath(Labz*);

};

