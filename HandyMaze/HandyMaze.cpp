#include "Labyrinthuz.h"

std::string		HandyMaze::p_error = "";

HandyMaze::HandyMaze(unsigned int w, unsigned int h)
	: p_width(w), p_height(h), p_maxshebs(w * h), p_map(0), p_groups(0), p_pool(0),
	p_pool_idx(0)
{
}

HandyMaze::~HandyMaze(void)
{
}

bool			HandyMaze::Generate()
{
	if (this->Initialize() == true)
	{
		unsigned int		maxcombmax;			// Maximum openable walls.
		unsigned int		maxcomb;			// Maximum openable walls, moving value.

		maxcombmax = this->p_maxshebs - 1;		// This what the algorithm says :x
		maxcomb = maxcombmax;
		this->p_pool_idx = this->p_maxshebs;	// At first the index is up to the end.

		std::cout << "Starting allocations..." << std::endl;
		this->p_pool = new (std::nothrow)std::vector<Index>(this->p_pool_idx);				// Allocation of the value pool.
		if (!this->p_pool) { HandyMaze::p_error = "Memory failed while allocating pool."; return (false); }
		this->p_groups = new std::vector<std::list<int>>(this->p_pool_idx);					// ALlocation of the id path lists.
		if (!this->p_map) { HandyMaze::p_error = "Memory failed while allocating groups."; return (false); }
		for (int i = 0; i < this->p_pool_idx; ++i)
		{
			(*this->p_pool)[i].value = i;				// Filling the values.
			(*this->p_groups)[i].push_back(i);			// At the begining, each square is alone in its path.
		}

		std::cout << "Starting generation..." << std::endl;
		--this->p_pool_idx;								// We decrease this->p_pool_idx because max index is this->p_pool_idx - 1;

		/* Beginning of the algorithm. */
		int					rand_sheb;
		int					rand_wall;

		while (maxcomb > 0)												// While we have not opened maxcomb walls.
		{
			rand_sheb = RandomMachine::Randomize(0, this->p_pool_idx);	// Seek a value for a Shebang to open.
			rand_wall = RandomMachine::Randomize(0, 1);					// Seek a wall to open.
			if (rand_wall == 0)
				rand_wall = -1;
			if (this->TryToOpen((*this->p_pool)[rand_sheb].value, rand_wall) == true)		// Tries to open first wall.
			{
				--maxcomb;
				--(*this->p_pool)[rand_sheb].ttl;
			}
			else
			{
				rand_wall = -rand_wall;
				if (this->TryToOpen((*this->p_pool)[rand_sheb].value, rand_wall) == true)	// If failed, try the other wall.
				{
					--maxcomb;
					--(*this->p_pool)[rand_sheb].ttl;
				}
			}

			if (this->p_map[((*this->p_pool)[rand_sheb]).value].id == this->p_map[((*this->p_pool)[rand_sheb]).value + 1].id
				&& ((*this->p_pool)[rand_sheb]).value > this->p_width
				&& this->p_map[((*this->p_pool)[rand_sheb]).value].id == this->p_map[((*this->p_pool)[rand_sheb]).value - this->p_width].id)
			{
				(*this->p_pool)[rand_sheb].value = (*this->p_pool)[this->p_pool_idx].value;	// If a square is can not be picked anymore because
				(*this->p_pool)[rand_sheb].ttl = (*this->p_pool)[this->p_pool_idx].ttl;		// north and east in the same group we replace its
				--this->p_pool_idx;															// index by another in the pool.
			}
			else if ((*this->p_pool)[rand_sheb].ttl == 0)
			{
				(*this->p_pool)[rand_sheb].value = (*this->p_pool)[this->p_pool_idx].value;	// If a value has been used twice
				(*this->p_pool)[rand_sheb].ttl = (*this->p_pool)[this->p_pool_idx].ttl;		// we remove it from the pool value.
				--this->p_pool_idx;															//
			}
		}
		return (true);
	}
	return (false);
}

bool			HandyMaze::Initialize()
{
	this->p_map = new (std::nothrow)Shebang[this->GetMaxShebs()]();
	if (!this->p_map)
	{
		HandyMaze::p_error = "Memory failed while initializing.";
		return (false);
	}
	for (int i = 0; i < this->p_maxshebs; ++i)
	{
		this->p_map[i].id = i;
		this->p_map[i].north = CLOSED;
		this->p_map[i].east = CLOSED;
		if (i < this->p_width)
			this->p_map[i].north = WALL;
		if (((i + 1) % this->p_width) == 0)
			this->p_map[i].east = WALL;
	}
	return (true);
}

bool			HandyMaze::TryToOpen(int sheb, int wall)
{
	if (wall == 1)
	{
		if (this->p_map[sheb].east == CLOSED && (this->p_map[sheb].id != this->p_map[sheb + 1].id))
		{
			this->p_map[sheb].east = OPEN;
			this->PathFuuuuuuusion(this->p_map[sheb].id, this->p_map[sheb + 1].id);
			return (true);
		}
		return (false);
	}
	if (this->p_map[sheb].north == CLOSED && (this->p_map[sheb].id != this->p_map[sheb - this->p_width].id))
	{
		this->p_map[sheb].north = OPEN;
		this->PathFuuuuuuusion(this->p_map[sheb].id, this->p_map[sheb - this->p_width].id);
		return (true);
	}
	return (false);
}

void			HandyMaze::PathFuuuuuuusion(int oidx, int nidx)
{
	if ((*this->p_groups)[oidx].size() > (*this->p_groups)[nidx].size())
	{
		this->gis = (*this->p_groups)[nidx].begin();
		this->gie = (*this->p_groups)[nidx].end();
		for (; this->gis != this->gie; ++(this->gis))
			this->p_map[(*this->gis)].id = oidx;
		(*this->p_groups)[oidx].splice((*this->p_groups)[oidx].begin(), (*this->p_groups)[nidx]);
	}
	else
	{
		this->gis = (*this->p_groups)[oidx].begin();
		this->gie = (*this->p_groups)[oidx].end();
		for (; this->gis != this->gie; ++(this->gis))
			this->p_map[(*this->gis)].id = nidx;
		(*this->p_groups)[nidx].splice((*this->p_groups)[nidx].begin(), (*this->p_groups)[oidx]);
	}
}

Labz*			HandyMaze::FormatLab()
{
	Labz*		l;
	int			shebX;
	int			shebY;
	
	l = new Labz();
	l->h = this->GetHeight() * 2 + 1;
	l->w = this->GetWidth() * 2 + 1;
	l->lab = new char*[l->w]();
	for (int i = 0; i < l->w; ++i)
	{
		l->lab[i] = new char[l->h]();
		memset(l->lab[i], OPEN, l->w - 1);
	}
	for (int i = 0; i < l->h; ++i)
	{
		for (int j = 0; j < l->w; ++j)
		{
			if (j == 0)					// Bord Gauche
				l->lab[0][i] = WALL;
			if (i == 0 || i % 2 == 0)	// Detecte un ligne TOP
			{
				if (j % 2 == 0)			// Pose les intersections
					l->lab[j][i] = WALL;
				else if (i + 1 == l->w)	// WALL DU BAS
					l->lab[j][i] = WALL;
				else
				{
					shebX = j / 2;
					shebY = (i + 1) / 2;
					if (this->p_map[shebY * this->GetWidth() + shebX].north != OPEN)
						l->lab[j][i] = WALL;
				}
			}
			else
			{
				if (j % 2 == 0)
				{
					shebX = (j - 1) / 2;
					shebY = i / 2;
					if (this->p_map[shebY * this->GetWidth() + shebX].east != OPEN)
						l->lab[j][i] = WALL;
				}
			}
		}
	}
	return (l);
}

void			HandyMaze::DrawAscii()
{
	if (this->p_map == 0)
		return ;
	for (int i = 0; i < this->p_height; ++i)
	{
		for (int j = 0; j < this->p_width; ++j)
		{
			if (j == 0)
				std::cout << "2";
			if (this->p_map[i * this->p_width + j].north == WALL)
				std::cout << "22";
			else if (this->p_map[i * this->p_width + j].north == CLOSED)
			{
				if (this->p_map[i * this->p_width + j].east == WALL)
					std::cout << "12";
				else
					std::cout << "11";
			}
			else
				std::cout << " 1";
		}
		std::cout << std::endl;
		for (int j = 0; j < this->p_width; ++j)
		{
			if (j == 0)
				std::cout << "2";
			if (this->p_map[i * this->p_width + j].east == WALL)
				std::cout << " 2";
			else if (this->p_map[i * this->p_width + j].east == CLOSED)
				std::cout << " 1";
			else
				std::cout << "  ";
		}
		std::cout << std::endl;
	}
	std::cout << "2";
	for (int i = 0; i < this->p_width; ++i)
		std::cout << "22";
	std::cout << std::endl;
}

void			HandyMaze::DrawFile()
{
	std::ofstream	output;

	output.open("Labz.txt");
	if (this->p_map == 0)
		return ;
	for (int i = 0; i < this->p_height; ++i)
	{
		for (int j = 0; j < this->p_width; ++j)
		{
			if (j == 0)
				output << "@";
			if (this->p_map[i * this->p_width + j].north == WALL)
				output << "@@";
			else if (this->p_map[i * this->p_width + j].north == CLOSED)
			{
				if (this->p_map[i * this->p_width + j].east == WALL)
					output << "@@";
				else
					output << "@@";
			}
			else
			{
				if (this->p_map[i * this->p_width + j].east == WALL)
					output << " @";
				else
					output << " @";
			}
		}
		output << "\r\n";
		for (int j = 0; j < this->p_width; ++j)
		{
			if (j == 0 && i == 0)
				output << " ";
			else if (j == 0)
				output << "@";
			if (this->p_map[i * this->p_width + j].east == WALL)
				output << " @";
			else if (this->p_map[i * this->p_width + j].east == CLOSED)
				output << " @";
			else
				output << "  ";
		}
		output << "\r\n";
	}
	output << "@";
	for (int i = 0; i < this->p_width; ++i)
		output << "@@";
	output << "\r\n";
	output.close();
}
