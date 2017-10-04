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
	std::vector<Node>& getNodes();

	size_t getWidth() const;
	size_t getHeight() const;

	int getNumData(Node::Data data) const;
	const Node& getExit() const;
	const Node& getStart() const;

	friend std::ostream &operator<<(std::ostream &output, const Grid &D);

private:
	std::vector<Node> _nodes;
	size_t _width;
	size_t _height;
};


