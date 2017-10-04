#include "Node.hpp"


Node::Node()
{
}


Node::~Node()
{
}

void Node::setLinkedToUpNeighbor(bool isLinked)
{
	m_isLinkedToUpNeighbor = isLinked;
	if (upNeighbor != nullptr)
		upNeighbor->m_isLinkedToDownNeighbor = isLinked;
}

void Node::setLinkedToRightNeighbor(bool isLinked)
{
	m_isLinkedToRightNeighbor = isLinked;
	if (rightNeighbor != nullptr)
		rightNeighbor->m_isLinkedToLeftNeighbor = isLinked;
}

void Node::setLinkedToLeftNeighbor(bool isLinked)
{
	m_isLinkedToLeftNeighbor = isLinked;
	if (leftNeighbor != nullptr)
		leftNeighbor->m_isLinkedToRightNeighbor = isLinked;
}

void Node::setLinkedToDownNeighbor(bool isLinked)
{
	m_isLinkedToDownNeighbor = isLinked;
	if (downNeighbor != nullptr)
		downNeighbor->m_isLinkedToUpNeighbor = isLinked;
}

bool Node::isLinkedToUpNeighbor()
{
	return m_isLinkedToUpNeighbor;
}

bool Node::isLinkedToRightNeighbor()
{
	return m_isLinkedToRightNeighbor;
}

bool Node::isLinkedToLeftNeighbor()
{
	return m_isLinkedToLeftNeighbor;
}

bool Node::isLinkedToDownNeighbor()
{
	return m_isLinkedToDownNeighbor;
}

std::ostream & operator<<(std::ostream& output, const Node& node)
{
	output << static_cast<char>(node.data);
	return output;
}
