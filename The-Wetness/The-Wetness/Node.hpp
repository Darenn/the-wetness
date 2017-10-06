#pragma once

#include <iostream>
#include <vector>

class Node
{
public:
	Node();
	~Node();



	std::vector<Node*> getLinkedNeighbors();

	friend std::ostream & operator<<(std::ostream& output, const Node& node);

	bool isLinkedToUpNeighbor = false;
	bool isLinkedToRightNeighbor = false;
	bool isLinkedToDownNeighbor = false;
	bool isLinkedToLeftNeighbor = false;
};

