#include	"LabLoader.h"

LabLoader::LabLoader() :
  p_loaded(false)
{
  memset(&this->p_lab, 0, sizeof(this->p_lab));
}

LabLoader::~LabLoader()
{
}

bool		LabLoader::LoadLab(const char* fname)
{
  bool		ret;

  ret = this->LoadContent(fname);
  if (ret == false)
    { std::cout << "Cant Load File" << std::endl; return (false); }

  this->p_lab.xe = this->p_lab.w - 1;
  this->p_lab.ye = this->p_lab.h - 1;
  this->p_loaded = true;

  return (true);
}

char		LabLoader::Get(unsigned int x, unsigned int y)
{
  if (this->p_loaded == false)
    { return (-1); }

  if (x > (this->p_lab.w - 1) || y > (this->p_lab.h - 1))
    { return (-1); }

  return (this->p_lab.shebangs[(y * this->p_lab.h) + x]);
}

void		LabLoader::Set(unsigned int x, unsigned int y, char v)
{
  if (this->p_loaded == false)
    { return ; }

  if (x > (this->p_lab.w - 1) || y > (this->p_lab.h - 1))
    { return ; }

  this->p_lab.shebangs[(y * this->p_lab.h) + x] = v;
}

void		LabLoader::PrintConsole()
{
  for (unsigned int i = 0; i < this->p_lab.h; ++i)
    {
      for (unsigned int j = 0; j < this->p_lab.w; ++j)
	{
	  std::cout << this->Get(j, i);
	}
      std::cout << std::endl;
    }
}

bool		LabLoader::LoadContent(const char* fname)
{
  struct stat		st;
  off_t			size;
  std::ifstream*	file;
  std::string		line;
  char*			content;
  unsigned int		idx;
  bool			first_line;

  if (fname == NULL)
    { return (false); }

  if (stat(fname, &st) == -1)
    { return (false); }

  file = new std::ifstream(fname, std::ios::in);
  if (!file->is_open())
    { delete (file); return (false); }

  content = new char[st.st_size + 1]();
  memset(content, 0, st.st_size + 1);
  idx = 0;
  first_line = true;
  while (std::getline(*file, line))
    {
      if (first_line == true)
	{
	  this->p_lab.w = line.length();
	  first_line = false;
	}
      ++this->p_lab.h;
      if (line.length() != this->p_lab.w)
	{ delete (content); delete (file); return (false); }
      memcpy(content + idx, line.c_str(), line.length());
      idx = idx + line.length();
    }
  delete (file);
  file->close();

  this->p_lab.shebangs = content;
  return (true);
}
