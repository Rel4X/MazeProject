HandyMaze
=========

HandyMaze is a maze generator with its solver and its drawer. It can generate huge mazes (more than 20k * 20k).

I have used the "EasyBMP" library by Paul Macklin for the drawing part.

Only available on linux for now.

Compile line is :

g++ -o maze -I./EasyBMP *.cpp EasyBMP/EasyBMP.cpp

The size of the maze is to put in the main.cpp.




IMPORTANT NOTE : Output in image is broken atm. The algorithm work but cannot create images bigger thant 12k*12k due to BMP format problems.
