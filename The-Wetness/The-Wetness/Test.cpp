/// \file       Test.cpp
/// \date       04/10/2017
/// \package    Test
/// \author     Vincent STEHLY--CALISTO

#include "Test.hpp"

#include "PuzzleGenerator.hpp"
#include "GridDecoder.hpp"
#include "GridEncoder.hpp"
#include <vector>

using namespace std;

Test::Test() : grid(0, 0)
{
	speed = 30.0f;
	posX  = 1.0f;
	step = 0;
}

void display_vector(const vector<bool> &v)
{
	std::copy(v.begin(), v.end(),
		ostream_iterator<bool>(std::cout, " "));
}

/// \brief	None
void Test::TestGA(void)
{
	// PuzzleGenerator pg;
	// grid = pg.generateNextPuzzle();

	/*
	GridEncoder ge;
	GridDecoder gd;
	Grid g(2, 2);
	g.getNode(0, 0).setLinkedToDownNeighbor(false);
	g.getNode(0, 0).setLinkedToRightNeighbor(false);
	g.getNode(1, 1).data = Node::Data::MUST_PASS;
	std::cout << g << std::endl;
	display_vector(ge.encode(g));
	std::cout << gd.decode(ge.encode(g)) << std::endl;
	*/
}

/// \brief	None
void Test::Update(float dt, Window & w)
{
	posX += speed * dt;
	w.Draw((WCHAR)9608, 0x0E, (unsigned short)posX, 5);

	//for (size_t i = 0; i < grid.getWidth(); i++)
	//{
	//	for (size_t j = 0; j < grid.getHeight(); j++)
	//	{
	//		Node node = grid.getNode(i, j);
	//		w.Draw((WCHAR)node.data, 0x0E, i, j);
	//
	//		if (node.isLinkedToRightNeighbor() && node.rightNeighbor != nullptr && node.rightNeighbor->isLinkedToLeftNeighbor())
	//		{
	//			w.Draw((WCHAR)0x0030D, 0x0E, i, j);
	//			w.Draw((WCHAR)0x0030D, 0x0E, i, j);
	//		}
	//		else
	//		{
	//		//	""
	//		}
	//	}
	//	//output << std::endl;
	//	//for (size_t j = 0; j < grid.getHeight(); j++)
	//	//{
	//	//	Node node = grid.getNode(i, j);
	//	//	if (node.isLinkedToDownNeighbor() && node.downNeighbor != nullptr && node.downNeighbor->isLinkedToUpNeighbor())
	//	//		output << "|  ";
	//	//	else
	//	//		output << "   ";
	//	//}
	//	//output << std::endl;
	//}
}
