#include "AStarLabzSolver.h"

AStarLabzSolver::AStarLabzSolver(void)
{
}

AStarLabzSolver::~AStarLabzSolver(void)
{
}

void			AStarLabzSolver::Clean()
{
	this->openList_.clear();
	this->closedList_.clear();
}

void			AStarLabzSolver::Solve(Labz* l)
{
	std::map<int, std::pair<int, int>*>::iterator	is;
	std::map<int, std::pair<int, int>*>::iterator	ie;
	std::map<int, std::pair<int, int>*>::iterator	ib;

	this->x_cur = 1;
	this->y_cur = 1;
	this->x_end = l->w - 2;
	this->y_end = l->h - 2;
	l->lab[1][1] = STARTING_BLOC;
	l->lab[this->x_end][this->y_end] = ARRIVAL;
	this->closedList_[this->GetId(l->w, 1, 1)] = new std::pair<int, int>(0, this->GetManathanToEnd(1, 1));
	while (this->x_cur != this->x_end || this->y_cur != this->y_end)
	{
		this->OpenTrial(l, this->x_cur + 1, this->y_cur, this->GetId(l->w, this->x_cur, this->y_cur));	
		this->OpenTrial(l, this->x_cur - 1, this->y_cur, this->GetId(l->w, this->x_cur, this->y_cur));	
		this->OpenTrial(l, this->x_cur, this->y_cur + 1, this->GetId(l->w, this->x_cur, this->y_cur));	
		this->OpenTrial(l, this->x_cur, this->y_cur - 1, this->GetId(l->w, this->x_cur, this->y_cur));
		ib = this->openList_.begin();
		is = this->openList_.begin();
		ie = this->openList_.end();
		for (; is != ie; ++is)
			if (is->second->second < ib->second->second)
				ib = is;
		this->closedList_[ib->first] = new std::pair<int, int>(ib->second->first, ib->second->second);
		this->x_cur = ib->first % l->w;
		this->y_cur = ib->first / l->w;
		this->openList_.erase(ib);
		l->lab[this->x_cur][this->y_cur] = IN_CLOSED;
	}
	this->RecoverPath(l);
}

int				AStarLabzSolver::GetId(int m, int x, int y)
{
	return (y * m + x);
}

int				AStarLabzSolver::GetManathanToEnd(int x, int y)
{
	return ((this->x_end - x) + (this->y_end - y));
}

void			AStarLabzSolver::OpenTrial(Labz* l, int x, int y, int p)
{
	std::map<int, std::pair<int, int>*>::iterator	oit;
	int			cost;

	oit = this->closedList_.find(this->GetId(l->w, x, y));
	if ((l->lab[x][y] == OPEN || l->lab[x][y] == ARRIVAL)
		&& oit == this->closedList_.end())
	{
		cost = this->GetManathanToEnd(x, y);
		oit = this->openList_.find(this->GetId(l->w, x, y));
		if (oit != this->openList_.end())
		{
			if (oit->second->second > cost)
			{
				oit->second->second = cost;
				oit->second->first = this->GetId(l->w, x, y);
			}
		}
		else
		{
			this->openList_[this->GetId(l->w, x, y)] = new std::pair<int, int>(p, cost);
			if (l->lab[x][y] != ARRIVAL)
				l->lab[x][y] = IN_OPEN;
		}
	}
}

void			AStarLabzSolver::RecoverPath(Labz* l)
{
	std::map<int, std::pair<int, int>*>::iterator	it;

	it = this->closedList_.find(this->GetId(l->h, this->x_cur, this->y_cur));
	if (it == this->closedList_.end())
		return ;
	while (it->second->first != 0)
	{
		it = this->closedList_.find(it->second->first);
		if (it == this->closedList_.end())
			return ;
		l->lab[it->first % l->w][it->first / l->w] = IN_PATH;
	}
}