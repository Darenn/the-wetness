#include "PuzzleGenerator.hpp"
#include "GridDecoder.hpp"
#include "GridEncoder.hpp"
#include <vector>
#include "Engine.hpp"

using namespace std;

void display_vector(const vector<bool> &v)
{
	std::copy(v.begin(), v.end(),
		ostream_iterator<bool>(std::cout, " "));
}

int& getInt() {
	return *(int*)nullptr;
}

#include <typeinfo>

/// \brief Entry point
int main(int argc, char ** argv)
{
	///////

	Engine gameEngine;
	//gameEngine.Start();
	
	/////
	PuzzleGenerator pg;

	pg.generateNextPuzzle();

	/*GridEncoder ge;
	GridDecoder gd;
	Grid g(2, 2);
	//g.setLinkWithNeighbor(Grid::Coordinates{ 0, 0 }, Grid::Direction::SOUTH, true);
	g.setLinkWithNeighbor(Grid::Coordinates{ 0, 1 }, Grid::Direction::EAST, true);
	//g.setLinkWithNeighbor(Grid::Coordinates{ 1, 1 }, Grid::Direction::NORTH, true);
	std::cout << g.isLinkedWithNeighbor(Grid::Coordinates{ 1, 0 }, Grid::Direction::EAST) << std::endl;
	std::cout << g << std::endl;*/
	//display_vector(ge.encode(g));
	//std::cout << gd.decode(ge.encode(g)) << std::endl;
    return 0;
}