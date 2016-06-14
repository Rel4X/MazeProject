#!/bin/bash

g++ -o SolverZ -I../HandyLabGen/EasyBMP/Includes/ -I./Includes/ ../HandyLabGen/EasyBMP/Srcs/EasyBMP.cpp Srcs/*.cpp -O3
