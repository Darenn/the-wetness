#include "Engine.hpp"
#include "PuzzleGenerator.hpp"
#include "DifficultyAnalyzer.hpp"
#include "Test.hpp"
#include "SquareGrid.hpp"
#include "Pathfinding.hpp"
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

	/*GridEncoder ge;
	GridDecoder gd;
	Grid g(3, 3);
	g.setLinkWithNeighbor(Grid::Coordinates{ 0, 0 }, Grid::Direction::EAST, false);
	//g.setLinkWithNeighbor(Grid::Coordinates{ 1, 0 }, Grid::Direction::SOUTH, false);
	g.setData(Grid::Coordinates{ 1, 0 }, Grid::Data::MUST_PASS);
	std::cout << g << std::endl;
	std::cout << std::boolalpha << g.hasValidPath(Grid::Coordinates{ 0, 0 }, Grid::Coordinates{ 2, 2 }) << std::endl;
	*/
	/*// alias helpers
	using CoordinateType = char;
	using PriorityType = short;

	using TNode = AI::Node<CoordinateType, PriorityType>;
	using TSquareGrid = AI::SquareGrid <CoordinateType, PriorityType>;

	TSquareGrid squareGrid;

	squareGrid.Initialize(g.getWidth(), g.getHeight());

	// Fill the grid with links
	for (unsigned char x = 0; x < g.getWidth(); x++)
	{
		for (unsigned char y = 0; y < g.getHeight(); y++)
		{
			Grid::Coordinates coord{ x, y };
			unsigned char linkedToEast = g.isLinkedWithNeighbor(coord, Grid::Direction::EAST) ? TNode::EMask::EAST : 0;
			unsigned char linkedToWest = g.isLinkedWithNeighbor(coord, Grid::Direction::WEST) ? TNode::EMask::WEST : 0;
			unsigned char linkedToNorth = g.isLinkedWithNeighbor(coord, Grid::Direction::NORTH) ? TNode::EMask::NORTH : 0;
			unsigned char linkedToSouth = g.isLinkedWithNeighbor(coord, Grid::Direction::SOUTH) ? TNode::EMask::SOUTH : 0;
			squareGrid.SetNodeMask(x, y, linkedToEast | linkedToWest | linkedToSouth | linkedToNorth);
		}
	}
	std::vector<TNode> path;

	std::cout << std::boolalpha << AI::Pathfinding<TSquareGrid, CoordinateType, PriorityType>::GetPath(squareGrid, path,
		squareGrid.GetNode(1, 0),
		squareGrid.GetNode(1, 1)) << std::endl;
	int a = 2;*/
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

	/*DifficultyAnalyzer da("test.data");
	std::cout << std::endl << da.getTimeForScore(5) << std::endl;
	da.saveData();*/
    return 0;
}