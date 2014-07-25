#include		<iostream>
#include		<SFML/Window.hpp>
#include		<SFML/Graphics.hpp>
#include		<SFML/System.hpp>
#include		"HandyMaze.h"
#include		"AStarLabzSolver.h"

#define			WIN_WIDTH	600
#define			WIN_HEIGHT	600
#define			WIN_NAME	"HandyMaze"

int				main()
{
	//sf::RenderWindow	win(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT, 32), WIN_NAME);
	sf::Sprite			sprite;
	sf::Image			image;
	sf::Image			imgStart;
	sf::Image			imgEnd;
	sf::Image			imgOpenL;
	sf::Image			imgCloseL;
	sf::Image			imgPath;
	sf::Image			final;
	HandyMaze			labz(15000, 15000);
	AStarLabzSolver		solver;
	int					imgW;
	int					imgH;
	Labz*				l;


	if (labz.Generate() == false)
	{
		std::cout << "Derp" << std::endl;
		return (1);
	}
	l = labz.GetFormatedLab();
	if (l == 0)
	{
		std::cout << "Dorp" << std::endl;
		return (1);
	}
	std::cout << "Generated" << std::endl;
	//solver.Solve(l);
	imgW = 1;//WIN_WIDTH / l->w;
	imgH = 1;//WIN_HEIGHT / l->h;
	image.create(imgW, imgH);
	imgStart.create(imgW, imgH);
	imgEnd.create(imgW, imgH);
	imgOpenL.create(imgW, imgH);
	imgCloseL.create(imgW, imgH);
	imgPath.create(imgW, imgH);
	for (int i = 0; i < imgH; ++i)
		for (int j = 0; j < imgW; ++j)
		{
			image.setPixel(j, i, sf::Color::Black);
			imgStart.setPixel(j, i, sf::Color::Green);
			imgEnd.setPixel(j, i, sf::Color::Red);
			imgOpenL.setPixel(j, i, sf::Color::Yellow);
			imgCloseL.setPixel(j, i, sf::Color::Blue);
			imgPath.setPixel(j, i, sf::Color::Magenta);
		}
	std::cout << "Allocating Image ..." << std::endl;
	final.create(l->w, l->h);
	std::cout << "Filling Image ..." << std::endl;
	for (int i = 0; i < l->w; ++i)
		for (int j = 0; j < l->h; ++j)
			final.setPixel(j, i, sf::Color::White);
	for (int i = 0; i < l->h; ++i)
		for (int j = 0; j < l->w; ++j)
		{
			if (l->lab[j][i] == WALL)
				final.copy(image, j * imgW, i * imgW);
			else if (l->lab[j][i] == STARTING_BLOC)
				final.copy(imgStart, j * imgW, i * imgW);
			else if (l->lab[j][i] == ARRIVAL)
				final.copy(imgEnd, j * imgW, i * imgW);
		}
	std::cout << "Saving Image ..." << std::endl;
	final.saveToFile("CLEAR.jpg");
	/*for (int i = 0; i < l->h; ++i)
		for (int j = 0; j < l->w; ++j)
		{
			if (l->lab[j][i] == WALL)
				final.copy(image, j * imgW, i * imgW);
			else if (l->lab[j][i] == STARTING_BLOC)
				final.copy(imgStart, j * imgW, i * imgW);
			else if (l->lab[j][i] == ARRIVAL)
				final.copy(imgEnd, j * imgW, i * imgW);
			else if (l->lab[j][i] == IN_OPEN)
				final.copy(imgOpenL, j * imgW, i * imgW);
			else if (l->lab[j][i] == IN_CLOSED)
				final.copy(imgCloseL, j * imgW, i * imgW);
			else if (l->lab[j][i] == IN_PATH)
				final.copy(imgPath, j * imgW, i * imgW);

		}
	final.saveToFile("DONE.jpg");*/
	system("PAUSE");
	return (0);
}
