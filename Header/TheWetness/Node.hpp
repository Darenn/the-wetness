#pragma once

#include <iostream>

class Node
{
public:
	friend class Grid;
	Node();
	~Node();

	bool isLinkedToUpNeighbor = false;
	bool isLinkedToRightNeighbor = false;
	bool isLinkedToDownNeighbor = false;
	bool isLinkedToLeftNeighbor = false;

	enum Data {NOTHING = '#', START = 'S', EXIT = 'E', MUST_PASS = 'X'};
	Data data = NOTHING;

	friend std::ostream & operator<<(std::ostream& output, const Node& node);

private:

	// They can be null
	Node* _upNeighbor = nullptr;
	Node* _rightNeighbor = nullptr;
	Node* _downNeighbor = nullptr;
	Node* _leftNeighbor = nullptr;
};

