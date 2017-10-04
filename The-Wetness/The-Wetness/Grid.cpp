#include "Grid.hpp"

Grid::Grid(int width, int height)
{
	_width = width;
	_height = height;
	// Create the nodes
	size_t nNodes = width * height;
	_nodes = std::vector<Node>();
	_nodes.reserve(nNodes);
	for (size_t i = 0; i < nNodes; i++)
	{
		_nodes.push_back(Node());
	}

	// Assign neighbors
	for (size_t i = 0; i < nNodes; i++)
	{
		// First column
		if (i % width == 0) {
			_nodes[i].rightNeighbor = &_nodes[i + 1];
			if (i > 0)
				_nodes[i].upNeighbor = &_nodes[i - width];
			if (i < nNodes - width)
				_nodes[i].downNeighbor = &_nodes[i + width];
		}
		// Last column
		else if (i % width == width - 1) {
			_nodes[i].leftNeighbor = &_nodes[i - 1];
			if (i > width - 1)
				_nodes[i].upNeighbor = &_nodes[i - width];
			if (i < nNodes - 1)
				_nodes[i].downNeighbor = &_nodes[i + width];
		}
		// First row
		else if (i / width == 0) {
			_nodes[i].downNeighbor = &_nodes[i + width];
			if (i > 0)
				_nodes[i].leftNeighbor = &_nodes[i - 1];
			if (i < width - 1)
				_nodes[i].rightNeighbor = &_nodes[i + 1];
		}
		// Last row
		else if (i / width == height - 1) {
			_nodes[i].upNeighbor = &_nodes[i - width];
			if (i > nNodes - width)
				_nodes[i].leftNeighbor = &_nodes[i - 1];
			if (i < nNodes - 1)
				_nodes[i].rightNeighbor = &_nodes[i + 1];
		}
		// Al other nodes
		else {			
			_nodes[i].leftNeighbor = &_nodes[i - 1];
			_nodes[i].rightNeighbor = &_nodes[i + 1];
			_nodes[i].upNeighbor = &_nodes[i - width];
			_nodes[i].downNeighbor = &_nodes[i + width];
		}
	}

	// Link them
	for (size_t i = 0; i < nNodes; i++)
	{
		if (_nodes.at(i).downNeighbor != nullptr)
			_nodes.at(i).setLinkedToDownNeighbor(true);
		if (_nodes.at(i).upNeighbor != nullptr)
			_nodes.at(i).setLinkedToUpNeighbor(true);
		if (_nodes.at(i).leftNeighbor != nullptr)
			_nodes.at(i).setLinkedToLeftNeighbor(true);
		if (_nodes.at(i).rightNeighbor != nullptr)
			_nodes.at(i).setLinkedToRightNeighbor(true);
	}
}

Grid::~Grid()
{
}

const Node & Grid::getNode(const size_t i, const size_t j) const
{
	return _nodes.at(i * _width + j);
}

Node & Grid::getNode(const size_t i, const size_t j)
{
	return _nodes.at(i * _width + j);
}

const std::vector<Node>& Grid::getNodes() const
{
	return _nodes;
}

std::vector<Node>& Grid::getNodes()
{
	return _nodes;
}

size_t Grid::getWidth() const
{
	return _width;
}

size_t Grid::getHeight() const
{
	return _height;
}

int Grid::getNumData(Node::Data data) const
{
	int numMustPass = 0;
	for (const Node& node : _nodes)
		if (node.data == data)
			numMustPass++;
	return numMustPass;
}

const Node & Grid::getExit() const
{
	for (auto& node : _nodes)
		if (node.data == Node::Data::EXIT)
			return node;
}

const Node & Grid::getStart() const
{
	for (auto node : _nodes)
		if (node.data == Node::Data::START)
			return node;
}

std::ostream & operator<<(std::ostream& output, const Grid& grid)
{
	for (size_t i = 0; i < grid._width; i++)
	{
		for (size_t j = 0; j < grid._height; j++)
		{
			Node node = grid.getNode(i, j);
			output << node;
			if (node.isLinkedToRightNeighbor() && node.rightNeighbor != nullptr && node.rightNeighbor->isLinkedToLeftNeighbor())
				output << "==";
			else
				output << "  ";
		}
		output << std::endl;
		for (size_t j = 0; j < grid._height; j++)
		{
			Node node = grid.getNode(i, j);
			if (node.isLinkedToDownNeighbor() && node.downNeighbor != nullptr && node.downNeighbor->isLinkedToUpNeighbor())
				output << "|  ";
			else
				output << "   ";
		}
		output << std::endl;
	}
	return output;
}
