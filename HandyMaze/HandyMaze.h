#pragma once

/*
	Purpose : HandyMaze is a class who generates mazes using a "Random Path Fusion" algorithm.
*/

#include	<iostream>
#include	<fstream>
#include	<string.h>
#include	<vector>
#include	<list>
#include	"RandomMachine.h"

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

class				HandyMaze
{
private:
	static std::string		p_error;

private:
	struct			Index				//
	{									// The Index struct is used to build a pool
		int			value;				// of values. Each value can be picked twice
		char		ttl;				// then will be pushed at the back of the pool.
										// All this is an optimization whose the goal
	public:								// is to avoid to loose time when seeking random
		Index() : value(0), ttl(2) { }	// values which have not been picked twice already.
	};									// I Know, I am great.

public:
	struct			Shebang		//
	{							// Shebang struct represents a square in the maze.
		char		north;		// Each square has two unique walls, north en east.
		char		east;		// Each wall can be either opened or closed.
		int			id;			// Each square also has a unique id, at least before the
	};							// path fusion.

private:
	unsigned int					p_width;		// The width of the maze.
	unsigned int					p_height;		// The height of the maze.
	unsigned int					p_maxshebs;		// The maximum squares in the maze.
	Shebang*						p_map;			// Shebang map. One shebang for each square.
	
	std::vector<Index>*				p_pool;			// Will contain values for random picking.
	unsigned int					p_pool_idx;		// Index in pool where is the last usable value.

	std::vector<std::list<int>>*	p_groups;		// Vectors of differents group of id. On id per path at the begining.
	std::list<int>::iterator		gis;			// Its iterators.
	std::list<int>::iterator		gie;			//

	char**							p_formated_lab;	// Formated lab using #define values up there.

private:
	HandyMaze(void);

public:
	HandyMaze(unsigned int, unsigned int);
	~HandyMaze(void);

public:
	const int			GetWidth() const		{ return (this->p_width); }
	const int			GetHeight() const		{ return (this->p_height); }
	const int			GetMaxShebs() const		{ return (this->p_maxshebs); }
	const Shebang*		GetLabz() const			{ return (this->p_map); }
	Labz*				GetFormatedLab()	{ return (this->FormatLab()); }

public:
	bool				Generate();
	void				DrawAscii();
	void				DrawFile();

private:
	bool				Initialize();
	bool				TryToOpen(int, int);
	void				PathFuuuuuuusion(int, int);
	Labz*				FormatLab();
};
