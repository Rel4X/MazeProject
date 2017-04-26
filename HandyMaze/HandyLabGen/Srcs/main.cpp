#include		<iostream>
#include		<sstream>
#include		<string>
#include		"HandyMaze.h"
#include		"LabzDrawer.h"
#include		"RxTime.h"

/*
  ajouter la possibilite de generer texte et bmp.
  ... heu ca y est je crois ... je dois verif que
  tout yes xD ..
 */

#define			OUTPUT_BOT	0
#define			OUTPUT_TXT	1
#define			OUTPUT_BMP	2

int			main(int ac, char** av)
{
  RxTime		timer;
  HandyMaze*		labz;
  Labz*			l;
  unsigned int		lsize;
  LabzDrawer		drawer;
  std::string		fnameT("");
  std::string		fnameB("");
  unsigned int		omod;

  omod = OUTPUT_TXT;
  lsize = 0;
  if (ac > 1)
    {
      lsize = atoi(av[1]);
      if (lsize >= MAZ_MAX)
	{
	  std::cout << "Merci de vous procurer la version payante." << std::endl;
	  return (1);
	}
    }
  else
    { 
      std::cout << "Usage ./LabyZ SIZE [[-txt | -bmp | -both] NAME]" << std::endl; 
      return (1);
    }

  fnameT = fnameT + "Labz_" + av[1] + ".txt";
  fnameB = fnameB + "Labz_" + av[1] + ".bmp";
  if (ac > 2)
    {
      if (strlen(av[2]) > 0 && strlen(av[2]) < 30)
	{
	  if (strncmp(av[2], "-txt", 4) == 0)
	    { omod = OUTPUT_TXT; }
	  else if (strncmp(av[2], "-bmp", 4) == 0)
	    { omod = OUTPUT_BMP; }
	  else if (strncmp(av[2], "-both", 5) == 0)
	    { omod = OUTPUT_BOT; }
	  else
	    {
	      fnameT = "";
	      fnameT = fnameT + av[2] + "_" + av[1] + ".txt";
	      fnameB = "";
	      fnameB = fnameB + av[2] + "_" + av[1] + ".bmp";
	    }
	}
      if (ac > 3)
	{
	  fnameT = "";
	  fnameT = fnameT + av[3] + "_" + av[1] + ".txt";
	  fnameB = "";
	  fnameB = fnameB + av[3] + "_" + av[1] + ".bmp";
	}
    }

  /*if (lsize % 2 == 0)
    {
      lsize = lsize / 2;
      //lsize += 1;
    }
  else
    {
      lsize = lsize / 2;
      //      lsize += 2;
      }*/

  lsize = lsize / 2;
  if (lsize < 2)
    { std::cout << "Taille trop petite." << std::endl; return (1); }
  // Allocation du Labyrinthe
  labz = new HandyMaze(lsize, lsize);

  // Generation du Labyrinthe
  timer.Start("Generation");
  if (labz->Generate() == false)
    { std::cout << "Generation failed" << std::endl; }
  std::cout << timer.GetEllapsedTime("Generation") << std::endl;

  // Recuperation du Labyrinthe formate
  l = labz->GetFormatedLab();
  if (l == 0)
    { std::cout << "Formating failed" << std::endl; }
  
  if (omod == OUTPUT_TXT)
    {
      if (drawer.DrawToTXT(l, (fnameT.c_str())) == false)
	{ std::cout << "Drawing failed" << std::endl; }
    }
  else if (omod == OUTPUT_BMP)
    {
      if (drawer.DrawToFile(l, (fnameB.c_str()), false) == false)
	{ std::cout << "Drawing failed" << std::endl; }
    }
  else if (omod == OUTPUT_BOT)
    {
      if (drawer.DrawToFile(l, (fnameB.c_str()), false) == false)
	{ std::cout << "Drawing failed" << std::endl; }
      if (drawer.DrawToTXT(l, (fnameT.c_str())) == false)
	{ std::cout << "Drawing failed" << std::endl; }
    }
  std::cout << "Fin" << std::endl;
  system("PAUSE");
  return (0);
}
