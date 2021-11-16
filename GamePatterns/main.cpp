#include <vector>
#include <iostream>

#include "Vec2.h"
#include "Maze.h"


int main() {

	MazeGeneration* randomMaze = new MazeGeneration();
	randomMaze->ExploreNode(Vec2<int>(0, 0)); //use recursive backtracker to generate maze
	Maze maze(randomMaze); //convert the generate maze into blockwise
	maze.printMaze();

	std::cin.get();
	return 0;
}