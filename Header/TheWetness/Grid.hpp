#pragma once

#include <vector>
#include <iostream>
#include "Node.hpp"

class Grid
{
public:
	Grid(int width, int height);
	~Grid();

	const Node& getNode(const size_t i, const size_t j) const;
	Node& getNode(const size_t i, const size_t j);
	const std::vector<Node>& getNodes() const;

	size_t width() const;
	size_t height() const;

	friend std::ostream &operator<<(std::ostream &output, const Grid &D);

private:
	std::vector<Node> _nodes;
	size_t _width;
	size_t _height;
};


