#include "Engine.hpp"
#include "PuzzleGenerator.hpp"

/// \brief Entry point
int main(int argc, char ** argv)
{
	/*Engine gameEngine;
	gameEngine.Start();*/
	//PuzzleGenerator pg;
	//pg.generateNextPuzzle();
	Grid g = Grid(6, 6);
	std::cout << g << std::endl;
	auto paths = g.getPaths(Grid::Coordinates{ 0, 0 }, Grid::Coordinates{ 5, 5 });
	/*for (std::vector<Grid::Coordinates> p : paths) {
		std::cout << "[ ";
		for (auto node : p) {
			std::cout << "{" << (int)node.x << ", " << (int)node.y << "}";
		}
		std::cout << "]" << std::endl;
	}*/
	std::cout << paths.size() << std::endl;
    return 0;
}