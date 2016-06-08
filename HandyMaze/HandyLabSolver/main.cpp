#include	<iostream>
#include	<fstream>
#include	<string>
#include	<string.h>

struct		Labz
{
  unsigned int	w;
  unsigned int	h;
  char*		shebangs;
};

int		main(int ac, char** av)
{
  std::ifstream*	file;
  std::string		line;
  Labz			lab;
  bool			first_line = true;

  if (ac < 2)
    { std::cout << "Missing Argument." << std::endl; return (0); }

  file = new std::ifstream(av[1], std::ios::in);
  if (!file->is_open())
    { std::cout << "Cant open file." << std::endl; return (0); }

  while (std::getline(*file, line))
    {
      if (first_line == true)
	{
	  if (!line.length() > 2)
	    { std::cout << "Weird file format." << std::endl; break ; }

	  lab.w = line.length();
	  lab.h = 0;
	  lab.shebangs = new char[line.length()]();

	  if (!lab.shebangs)
	    { std::cout << "Memory error." << std::endl; break ; }
	  
	  first_line = false;
	}
      
      std::cout << line << std::endl;
    }
  file->close();

  return (0);
}
