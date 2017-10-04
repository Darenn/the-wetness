#include "PuzzleGenerator.hpp"
#include "GridDecoder.hpp"
#include "GridEncoder.hpp"
#include <vector>
#include "ASCIITest.hpp"
#include "Engine.hpp"

using namespace std;

void display_vector(const vector<bool> &v)
{
	std::copy(v.begin(), v.end(),
		ostream_iterator<bool>(std::cout, " "));
}

/// \brief Entry point
int main(int argc, char ** argv)
{
	///////

	Engine gameEngine;
	gameEngine.Start();
	
	/////
	PuzzleGenerator pg;
	pg.generateNextPuzzle();

	/*GridEncoder ge;
	GridDecoder gd;
	Grid g(2, 2);
	g.getNode(0, 0).setLinkedToDownNeighbor(false);
	g.getNode(0, 0).setLinkedToRightNeighbor(false);
	g.getNode(1, 1).data = Node::Data::MUST_PASS;
	std::cout << g << std::endl;
	display_vector(ge.encode(g));
	std::cout << gd.decode(ge.encode(g)) << std::endl;*/
    return 0;
}