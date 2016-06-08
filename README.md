HandyMaze
=========

HandyMaze is a maze generator with its solver and its drawer. It can generate huge mazes (more than 20k * 20k), BUT some software can not open bmps when the maze is bigger than 10k * 10k.

I have used the "EasyBMP" library by Paul Macklin for the drawing part.

Available on Windows and Linux.

Usage :
./HandyMaze SIZE_OF_LAB [[-txt | -bmp | -both] NAME_OF_LAB]

-txt asks for the output to be in ascii mod (default mod)
-bmp asks for the output to be a BMP file ... (For beautifull output <3)
-boths asks for both .txt and .bmp output.

If specified, the name of the output is NAME_OF_LAB_SIZE_OF_LAB.[txt | bmp]

If not, the name is Labz_SIZE_OF_LAB.[txt | bmp]
