#include "Generation/Grid/GridEncoder.hpp"
#include <cassert>

std::vector<bool> fromChar(char value)
{
	int nBits = sizeof(char) * 8;
	std::vector<bool> charToBools(nBits);
	for (size_t i = 0; i < nBits; i++)
	{
		char mask = 1 << i;
		char masked_value = value & mask;
		charToBools.at(nBits - 1 - i) = masked_value;
	}
	return charToBools;
}

GridEncoder::GridEncoder()
{
}


GridEncoder::~GridEncoder()
{
}

std::vector<bool> GridEncoder::encode(const Grid & grid) const
{
	std::vector<bool> encodedGrid{};

	encodedGrid.reserve(sizeof(char) * 8 + grid.getNodeCount() * NUMBER_BITS_PER_NODE);

	// Encode the number of rows
	auto numberRows = fromChar(static_cast<char>(grid.getHeight()));
	encodedGrid.insert(std::end(encodedGrid), std::begin(numberRows), std::end(numberRows));

	for (size_t i = 0; i < grid.getNodeCount(); i++)
	{
		// Encode a node

		// Encode the content
		std::pair<bool, bool> content{};
		switch (grid.getData(i))
		{
		case Grid::Data::START:
			content.first = false;
			content.second = false;
			break;
		case Grid::Data::EXIT:
			content.first = false;
			content.second = true;
			break;
		case Grid::Data::MUST_PASS:
			content.first = true;
			content.second = false;
			break;
		case Grid::Data::NOTHING:
			content.first = true;
			content.second = true;
			break;
		}
		encodedGrid.push_back(content.first);
		encodedGrid.push_back(content.second);

		// Encode the links with neighbours
		encodedGrid.push_back(grid.isLinkedWithNeighbor(i, Grid::Direction::NORTH));
		encodedGrid.push_back(grid.isLinkedWithNeighbor(i, Grid::Direction::EAST));
		encodedGrid.push_back(grid.isLinkedWithNeighbor(i, Grid::Direction::SOUTH));
		encodedGrid.push_back(grid.isLinkedWithNeighbor(i, Grid::Direction::WEST));
	}
	assert(encodedGrid.size() == sizeof(char) * 8 + grid.getNodeCount() * NUMBER_BITS_PER_NODE);
	return encodedGrid;
}
