#include "Engine.hpp"
#include "PuzzleGenerator.hpp"
#include <ctime>

void display_vector2(const std::vector<bool> &v)
{
	std::copy(v.begin(), v.end(),
	          std::ostream_iterator<bool>(std::cout, " "));
}

/// \brief Entry point
int main(int argc, char ** argv)
{
	/*Engine gameEngine;
	gameEngine.Start();*/
	PuzzleGenerator pg;
	pg.generateNextPuzzle();
	/*Grid g = Grid(2, 2);
	srand(std::time(nullptr));
	g.setData(Grid::Coordinates{ 1, 1 }, Grid::Data::MUST_PASS);
	g.setLinkWithNeighbor(Grid::Coordinates{ 0, 0 }, Grid::Direction::EAST, false);
	std::cout << g << std::endl;
	GA_Algorithms ga_algo;
	GridEncoder ge;
	GridDecoder gd;
	std::vector<bool> test = { 0,0,0,0, 0,0,1,0,  1,1, 0,0,1,0,  1,1, 0,0,1,1,  1,1, 1,1,0,0, 1,0, 1,0,0,1 };
	auto gEncoded = ge.encode(g);
	assert(gEncoded == test);

	std::cout << gd.decode(gEncoded) << std::endl;
	assert(ge.encode(gd.decode(gEncoded)) == test);
	ga_algo.mutate(gEncoded);
	std::cout << gd.decode(gEncoded) << std::endl;
	auto a = 2;*/
    return 0;
}