#include "TheWetness/Grid.hpp"

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
			_nodes[i]._rightNeighbor = &_nodes[i + 1];
			if (i > 0)
				_nodes[i]._upNeighbor = &_nodes[i - width];
			if (i < nNodes - width)
				_nodes[i]._downNeighbor = &_nodes[i + width];
		}
		// Last column
		else if (i % width == width - 1) {
			_nodes[i]._leftNeighbor = &_nodes[i - 1];
			if (i > width - 1)
				_nodes[i]._upNeighbor = &_nodes[i - width];
			if (i < nNodes - 1)
				_nodes[i]._downNeighbor = &_nodes[i + width];
		}
		// First row
		else if (i / width == 0) {
			_nodes[i]._downNeighbor = &_nodes[i + width];
			if (i > 0)
				_nodes[i]._leftNeighbor = &_nodes[i - 1];
			if (i < width - 1)
				_nodes[i]._rightNeighbor = &_nodes[i + 1];
		}
		// Last row
		else if (i / width == height - 1) {
			_nodes[i]._upNeighbor = &_nodes[i - width];
			if (i > nNodes - width)
				_nodes[i]._leftNeighbor = &_nodes[i - 1];
			if (i < nNodes - 1)
				_nodes[i]._rightNeighbor = &_nodes[i + 1];
		}
		// Al other nodes
		else {			
			_nodes[i]._leftNeighbor = &_nodes[i - 1];
			_nodes[i]._rightNeighbor = &_nodes[i + 1];
			_nodes[i]._upNeighbor = &_nodes[i - width];
			_nodes[i]._downNeighbor = &_nodes[i + width];
		}
	}

	// Link them
	for (size_t i = 0; i < nNodes; i++)
	{
		if (_nodes.at(i)._downNeighbor != nullptr)
			_nodes.at(i).isLinkedToDownNeighbor = true;
		if (_nodes.at(i)._upNeighbor != nullptr)
			_nodes.at(i).isLinkedToUpNeighbor = true;
		if (_nodes.at(i)._leftNeighbor != nullptr)
			_nodes.at(i).isLinkedToLeftNeighbor = true;
		if (_nodes.at(i)._rightNeighbor != nullptr)
			_nodes.at(i).isLinkedToRightNeighbor = true;
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

size_t Grid::width() const
{
	return _width;
}

size_t Grid::height() const
{
	return _height;
}

std::ostream & operator<<(std::ostream& output, const Grid& grid)
{
	for (size_t i = 0; i < grid._width; i++)
	{
		for (size_t j = 0; j < grid._height; j++)
		{
			Node node = grid.getNode(i, j);
			output << node;
			if (node.isLinkedToRightNeighbor)
				output << "==";
			else
				output << "  ";
		}
		output << std::endl;
		for (size_t j = 0; j < grid._height; j++)
		{
			Node node = grid.getNode(i, j);
			if (node.isLinkedToDownNeighbor)
				output << "|  ";
			else
				output << "   ";
		}
		output << std::endl;
	}
	return output;
}
