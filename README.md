# Game-of-life
Simulation of the popular game "Conway's Game of Life " in C

This implementation already comes with 8 initial board configurations that the user can start the game with.

There are two ways to run the program. One can specify on the command line the initial configuration 
(enter a number between 1-8) and the number of generations to simulate. The program will print the board after specified number
of generations. For example, the following command prints the board configuration after 50 generations, starting 
from initial configuration 8. $ ./game-of-life 8 50

The other way to run the program is to only specify the board configuration $ ./game-of-life 8 
The program will print the initial board and then ask how many generations you wish to simulate, then you can sit
back and enjoy the movie :)
