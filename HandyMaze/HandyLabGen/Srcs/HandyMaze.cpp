#include "HandyMaze.h"

std::string	HandyMaze::p_error = "";

HandyMaze::HandyMaze(unsigned int w, unsigned int h)
	: p_width(w), p_height(h), p_maxshebs(w * h), p_map(0), p_groups(0), p_pool(0),
	p_pool_idx(0)
{
  if (w >= MAZ_MAX || h >= MAZ_MAX)
    exit (0);
}

HandyMaze::~HandyMaze(void)
{
}

bool		HandyMaze::Generate()
{ 
  if (this->Initialize() == true)
    {
      unsigned int		maxcombmax;	// Maximum openable walls.
      unsigned int		maxcomb;	// Maximum openable walls, moving value.
      
      maxcombmax = this->p_maxshebs - 1;	// This what the algorithm says :x
      maxcomb = maxcombmax;
      this->p_pool_idx = this->p_maxshebs;	// At first the index is up to the end.
      
      this->p_pool = new (std::nothrow)std::vector<Index>(this->p_pool_idx);
      if (!this->p_pool) { HandyMaze::p_error = "Memory failed while allocating pool."; return (false); }
      this->p_groups = new (std::nothrow)GNode[this->p_maxshebs]();
      if (!this->p_groups) { HandyMaze::p_error = "Memory failed while allocating groups."; return (false); }
      for (int i = 0; i < this->p_pool_idx; ++i)
	{
	  (*this->p_pool)[i].value = i;
	  this->p_groups[i].value = i;
	  this->p_groups[i].tail = &(this->p_groups[i]);
	  this->p_groups[i].next = 0;
	  this->p_groups[i].size = 1;
	}
      --this->p_pool_idx;
      
      /* Beginning of the algorithm. */
      int					rand_sheb;
      int					rand_wall;
      
      while (maxcomb > 0)										       
	{
	  rand_sheb = RandomMachine::Randomize(0, this->p_pool_idx);
	  rand_wall = RandomMachine::Randomize(0, 1);
	  if (rand_wall == 0)
	    rand_wall = -1;
	  if (this->TryToOpen((*this->p_pool)[rand_sheb].value, rand_wall) == true)
	    {
	      --maxcomb;
	      --(*this->p_pool)[rand_sheb].ttl;
	    }
	  else
	    {
	      rand_wall = -rand_wall;
	      if (this->TryToOpen((*this->p_pool)[rand_sheb].value, rand_wall) == true)
		{
		  --maxcomb;
		  --(*this->p_pool)[rand_sheb].ttl;
		}
	    }
	  
	  if (this->p_map[((*this->p_pool)[rand_sheb]).value].id == this->p_map[((*this->p_pool)[rand_sheb]).value + 1].id
	      && ((*this->p_pool)[rand_sheb]).value > this->p_width
	      && this->p_map[((*this->p_pool)[rand_sheb]).value].id == this->p_map[((*this->p_pool)[rand_sheb]).value - this->p_width].id)
	    {
	      (*this->p_pool)[rand_sheb].value = (*this->p_pool)[this->p_pool_idx].value;
	      (*this->p_pool)[rand_sheb].ttl = (*this->p_pool)[this->p_pool_idx].ttl;
	      --this->p_pool_idx;
	    }
	  else if ((*this->p_pool)[rand_sheb].ttl == 0)
	    {
	      (*this->p_pool)[rand_sheb].value = (*this->p_pool)[this->p_pool_idx].value;
	      (*this->p_pool)[rand_sheb].ttl = (*this->p_pool)[this->p_pool_idx].ttl;
	      --this->p_pool_idx;
	    }
	}
      delete (this->p_pool);
      delete (this->p_groups);
      return (true);
    }
  return (false);
}

bool		HandyMaze::Initialize()
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

bool	HandyMaze::TryToOpen(int sheb, int wall)
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

void		HandyMaze::PathFuuuuuuusion(int oidx, int nidx)
{
  GNode*	tmp;
  
  if (this->p_groups[oidx].size > this->p_groups[nidx].size)
    {
      this->p_groups[oidx].size += this->p_groups[nidx].size;
      tmp = &(this->p_groups[nidx]);
      while (tmp != 0)
	{
	  this->p_map[tmp->value].id = oidx;
	  tmp = tmp->next;
	}
      this->p_groups[oidx].tail->next = &(this->p_groups[nidx]);
      this->p_groups[oidx].tail = this->p_groups[nidx].tail;
    }
  else
    {
      this->p_groups[nidx].size += this->p_groups[oidx].size;
      tmp = &(this->p_groups[oidx]);
      while (tmp != 0)
	{
	  this->p_map[tmp->value].id = nidx;
	  tmp = tmp->next;
	}
      this->p_groups[nidx].tail->next = &(this->p_groups[oidx]);
      this->p_groups[nidx].tail = this->p_groups[oidx].tail;
    }
}

Labz*		HandyMaze::FormatLab()
{
  Labz*		l;
  int		shebX;
  int		shebY;
  
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
