#include "Cell.h"

Cell::Cell() :
  p_visited(false)
{
  this->p_door[CL_TOP] = false;
  this->p_door[CL_BOT] = false;
  this->p_door[CL_EAS] = false;
  this->p_door[CL_WES] = false;
}

Cell::~Cell()
{
}

bool		Cell::GetVisited() const
{
  return (this->p_visited);
}

bool		Cell::GetTop() const
{
  return (this->p_door[CL_TOP]);
}

bool		Cell::GetBottom() const
{
  return (this->p_door[CL_BOT]);
}

bool		Cell::GetEast() const
{
  return (this->p_door[CL_EAS]);
}

bool		Cell::GetWest() const
{
  return (this->p_door[CL_WES]);
}

bool		Cell::GetDir(unsigned int dir) const
{
  return (this->p_door[dir]);
}

void		Cell::SetVisited(bool v)
{
  this->p_visited = v;
}

void		Cell::SetTop(bool v)
{
  this->p_door[CL_TOP] = v;
}

void		Cell::SetBottom(bool v)
{
  this->p_door[CL_BOT] = v;
}

void		Cell::SetEast(bool v)
{
  this->p_door[CL_EAS] = v;
}

void		Cell::SetWest(bool v)
{
  this->p_door[CL_WES] = v;
}

void		Cell::SetDir(unsigned int dir, bool v)
{
  this->p_door[dir] = v;
}

void		Cell::PrintConsole() const
{
  std::cout << "vis: " << std::boolalpha;
  std::cout << this->GetVisited() << std::endl;
  std::cout << "top: " << std::boolalpha;
  std::cout << this->GetTop() << std::endl;
  std::cout << "bot: " << std::boolalpha;
  std::cout << this->GetBottom() << std::endl;
  std::cout << "eas: " << std::boolalpha;
  std::cout << this->GetEast() << std::endl;
  std::cout << "wes: " << std::boolalpha;
  std::cout << this->GetWest() << std::endl;
}
