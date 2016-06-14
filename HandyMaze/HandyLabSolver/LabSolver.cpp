#include	"LabSolver.h"

LabSolver::LabSolver() :
  p_labl(0x0), p_lab(0x0)
{
}

LabSolver::~LabSolver()
{
}

bool		LabSolver::Solve(LabLoader* labl)
{
  bool		ret;

  this->p_labl = labl;
  this->p_lab = labl->GetLab();

  if (this->p_labl->Get(0, 0) != WAY)
    { return (false); }
  ret = this->Track(0, 0);
  this->p_labl->Set(0, 0, PATH);

  if (ret == false)
    { return (false); }

  // Pour virer les visites ... mais ca peut etre cool de les garder.
  for (int i = 0; i < this->p_lab->h; ++i)
    {
      for (int j = 0; j < this->p_lab->w; ++j)
	{
	  if (this->p_labl->Get(j, i) == VISIT)
	    this->p_labl->Set(j, i, WAY);
	}
    }

  this->p_labl->PrintConsole();
  return (true);
}

bool		LabSolver::Track(unsigned int px, unsigned int py)
{
  bool		ret;

  if (!this->p_labl || !this->p_lab)
    { return (false); }

  if (px == this->p_lab->xe && py == this->p_lab->ye)
    { return (true); }

  this->p_labl->Set(px, py, VISIT);

  if (this->p_labl->Get(px + 1, py) == WAY)
    {
      ret = this->Track(px + 1, py);
      if (ret == true) { this->p_labl->Set(px + 1, py, PATH); return (true); }
    }
  if (this->p_labl->Get(px, py + 1) == WAY)
    {
      ret = this->Track(px, py + 1);
      if (ret == true) { this->p_labl->Set(px, py + 1, PATH); return (true); }
    }
  if (this->p_labl->Get(px - 1, py) == WAY)
    {
      ret = this->Track(px - 1, py);
      if (ret == true) { this->p_labl->Set(px - 1, py, PATH); return (true); }
    }
  if (this->p_labl->Get(px, py - 1) == WAY)
    {
      ret = this->Track(px, py - 1);
      if (ret == true) { this->p_labl->Set(px, py - 1, PATH); return (true); }
    }

  return (false);
}
