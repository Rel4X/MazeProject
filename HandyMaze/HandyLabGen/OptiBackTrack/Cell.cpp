#include "Cell.h"

std::map<unsigned int, char> Cell::p_mask = {
  {CL_TOP, 1},
  {CL_BOT, 2},
  {CL_EAS, 4},
  {CL_WES, 8},
  {CL_VIS, 16}
};

Cell::Cell()
{
  this->p_data = 0;
}

Cell::~Cell()
{

}

bool		Cell::GetVisited()
{
  return (this->p_data & this->p_mask[CL_VIS]);
}

bool		Cell::GetTop()
{
  return (this->p_data & this->p_mask[CL_TOP]);
}

bool		Cell::GetBottom()
{
  return (this->p_data & this->p_mask[CL_BOT]);
}

bool		Cell::GetEast()
{
  return (this->p_data & this->p_mask[CL_EAS]);
}

bool		Cell::GetWest()
{
  return (this->p_data & this->p_mask[CL_WES]);
}

bool		Cell::GetDir(unsigned int dir)
{
  return (this->p_data & this->p_mask[dir]);
}

void		Cell::SetVisitedTrue()
{
  this->p_data |= this->p_mask[CL_VIS];
}

void		Cell::SetVisitedFalse()
{
  this->p_data ^= this->p_mask[CL_VIS];
}

void		Cell::SetTopTrue()
{
  this->p_data |= this->p_mask[CL_TOP];
}

void		Cell::SetTopFalse()
{
  this->p_data ^= this->p_mask[CL_TOP];
}

void		Cell::SetBottomTrue()
{
  this->p_data |= this->p_mask[CL_BOT];
}

void		Cell::SetBottomFalse()
{
  this->p_data ^= this->p_mask[CL_BOT];
}

void		Cell::SetEastTrue()
{
  this->p_data |= this->p_mask[CL_EAS];
}

void		Cell::SetEastFalse()
{
  this->p_data ^= this->p_mask[CL_EAS];
}

void		Cell::SetWestTrue()
{
  this->p_data |= this->p_mask[CL_WES];
}

void		Cell::SetWestFalse()
{
  this->p_data ^= this->p_mask[CL_WES];
}

void		Cell::SetDirTrue(unsigned int d)
{
  this->p_data |= this->p_mask[d];
}

void		Cell::SetDirFalse(unsigned int d)
{
  this->p_data ^= this->p_mask[d];
}

void		Cell::PrintConsole()
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
