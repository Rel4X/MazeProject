#include		<iostream>
#include		<sstream>
#include		<string>
#include		"HandyMaze.h"
#include		"AStarLabzSolver.h"
#include		"LabzDrawer.h"

int				main(int ac, char** av)
{
	unsigned int		lsize;
	HandyMaze*			labz;
	LabzDrawer			drawer;
	AStarLabzSolver*	solver;
	Labz*				l;
	std::string			fname("");

	lsize = 0;

	// Check des arguments
	if (ac == 2 || ac == 3)
	{ lsize = atoi(av[1]); }
	else
	{ std::cout << "Missing argument" << std::endl; }

	lsize = lsize / 2;

	if (lsize >= 2)
	{
		// Allocation du Labyrinthe
		labz = new HandyMaze(lsize, lsize);

		// Generation du Labyrinthe
		if (labz->Generate() == false)
		{ std::cout << "Generation failed" << std::endl; }

		// Recuperation du Labyrinthe formate
		l = labz->GetFormatedLab();
		if (l == 0)
		{ std::cout << "Formating failed" << std::endl; }

		// Dessin du Labyrinthe en BMP
		//fname = fname + "Labz_" + av[1];
		//if (drawer.DrawToFile(l, (new std::string(fname + ".bmp"))->c_str(), false) == false)
		//{ std::cout << "Drawing failed" << std::endl; }

		// Dessin du Labyrinthe en TXT
		fname = fname + "Labz_" + av[1];
		if (drawer.DrawToTXT(l, (new std::string(fname + ".txt"))->c_str()) == false)
		{ std::cout << "Drawing failed" << std::endl; }

		if (ac == 3 && strncmp(av[2], "-ia", 3) == 0)
		{
			solver = new AStarLabzSolver();
			solver->Solve(l);
			fname = "";
			fname = fname + "Labz_" + av[1] + "_AI.bmp";
			if (drawer.DrawToFile(l, fname.c_str(), true) == false)
			{ std::cout << "Drawing failed (AI)" << std::endl; }
		}
	}

	system("PAUSE");
	return (0);
}
