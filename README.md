HandyMaze
=========

HandyMaze is a maze generator with its solver and its drawer. It can generate huge mazes (more than 20k * 20k).

I have used the "EasyBMP" library by Paul Macklin for the drawing part.

Only available on linux for now.

Compile line is :

g++ -o maze -I./EasyBMP *.cpp EasyBMP.cpp

The size of the maze is to put in the main.cpp.
