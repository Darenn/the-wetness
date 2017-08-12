#include "GridEncoder.h"

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
	encodedGrid.reserve(nodes.size() * NUMBER_BITS_PER_NODE);

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
	return encodedGrid;
}
