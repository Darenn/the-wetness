#include "TheWetness/GridEncoder.hpp"
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
	auto nodes = grid.getNodes();
	encodedGrid.reserve(sizeof(char) * 8 + nodes.size() * NUMBER_BITS_PER_NODE);

	// Encode the number of rows
	auto numberRows = fromChar(static_cast<char>(grid.height()));
	encodedGrid.insert(std::end(encodedGrid), std::begin(numberRows), std::end(numberRows));

	for (size_t i = 0; i < nodes.size(); i++)
	{
		// Encode a node
		auto node = nodes[i];

		// Encode the content
		std::pair<bool, bool> content{};
		switch (node.data)
		{
		case Node::Data::START:
			content.first = false;
			content.second = false;
			break;
		case Node::Data::EXIT:
			content.first = false;
			content.second = true;
			break;
		case Node::Data::MUST_PASS:
			content.first = true;
			content.second = false;
			break;
		case Node::Data::NOTHING:
			content.first = true;
			content.second = true;
			break;
		}
		encodedGrid.push_back(content.first);
		encodedGrid.push_back(content.second);

		// Encode the links with neighbours
		encodedGrid.push_back(node.isLinkedToUpNeighbor);
		encodedGrid.push_back(node.isLinkedToRightNeighbor);
		encodedGrid.push_back(node.isLinkedToDownNeighbor);
		encodedGrid.push_back(node.isLinkedToLeftNeighbor);
	}
	int a = sizeof(char) * 8 + nodes.size() * NUMBER_BITS_PER_NODE;
	assert(encodedGrid.size() == sizeof(char) * 8 + nodes.size() * NUMBER_BITS_PER_NODE);
	return encodedGrid;
}
