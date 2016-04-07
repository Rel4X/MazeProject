HandyMaze
=========

HandyMaze is a maze generator with its solver and its drawer. It can generate huge mazes (more than 20k * 20k), BUT some software can not open bmps when the maze is bigger than 10k * 10k.

I have used the "EasyBMP" library by Paul Macklin for the drawing part.

Available on Windows and Linux.

Compile line for Linux:
g++ -o HandyMaze -I./EasyBMP/Includes/ EasyBMP/Srcs/EasyBMP.cpp *.cpp

Launching line :
./HandyMaze SIZE_OF_LAB [-ia]

-ia : Activate the AI solving of the maze plus the drawing of a picture of the maze with the ia's path
