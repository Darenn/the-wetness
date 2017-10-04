#pragma once

#include <iostream>

class Node
{
public:
	Node();
	~Node();

	enum Data {NOTHING = '#', START = 'S', EXIT = 'E', MUST_PASS = 'X'};
	Data data = NOTHING;

	void setLinkedToUpNeighbor(bool isLinked);
	void setLinkedToRightNeighbor(bool isLinked);
	void setLinkedToLeftNeighbor(bool isLinked);
	void setLinkedToDownNeighbor(bool isLinked);

	bool isLinkedToUpNeighbor();
	bool isLinkedToRightNeighbor();
	bool isLinkedToLeftNeighbor();
	bool isLinkedToDownNeighbor();

	friend std::ostream & operator<<(std::ostream& output, const Node& node);

	// They can be null
	Node* upNeighbor = nullptr;
	Node* rightNeighbor = nullptr;
	Node* downNeighbor = nullptr;
	Node* leftNeighbor = nullptr;

private:
	bool m_isLinkedToUpNeighbor = false;
	bool m_isLinkedToRightNeighbor = false;
	bool m_isLinkedToDownNeighbor = false;
	bool m_isLinkedToLeftNeighbor = false;
};

