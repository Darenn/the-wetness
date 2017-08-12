#include "Node.h"


Node::Node()
{
}


Node::~Node()
{
}

std::ostream & operator<<(std::ostream& output, const Node& node)
{
	output << static_cast<char>(node.data);
	return output;
}
