#include "GridDecoder.hpp"
#include "GridEncoder.hpp"


char fromVector(std::vector<bool> vec) {
	char retval = 0;
	for (size_t i = 0; i < vec.size(); i++)
	{
		if (vec[i] != 0)
			retval |= 1 << vec.size() - i - 1;
	}
	return retval;
}

GridDecoder::GridDecoder()
{
}


GridDecoder::~GridDecoder()
{
}

Grid GridDecoder::decode(const std::vector<bool> encodedGrid) const
{
	// Get the number of rows
	auto first = encodedGrid.begin();
	auto last = encodedGrid.begin() + sizeof(char)*8;
	std::vector<bool> newVec(first, last);
	int numberRows = fromVector(newVec);

	int numberColumns = ((encodedGrid.size() - sizeof(char)*8) / GridEncoder::NUMBER_BITS_PER_NODE) / numberRows;

	// Create a basic grid with good dimensions
	Grid decodedGrid(numberRows, numberColumns);

	// Modify each node accordingly to the encoded grid
	std::vector<Node>& nodes = decodedGrid.getNodes();
	for (size_t i = 0; i < nodes.size(); i++)
	{
		Node& node = nodes[i];

		// decode the content
		std::pair<bool, bool> content(encodedGrid[sizeof(char)*8 + i*6], encodedGrid[sizeof(char)*8 + i*6 + 1]);
		//std::cout << content.second << std::endl;
		if (content.first == 0)
		{
			if (content.second == 0)
				node.data = Node::Data::START;
			else
				node.data = Node::Data::EXIT;
		}
		else
		{
			if (content.second == 0)
				node.data = Node::Data::MUST_PASS;
			else
				node.data = Node::Data::NOTHING;
		}

		// decode the links with neighbours
		int ind = 8 + i * 6 + 2;
		node.setLinkedToUpNeighbor(encodedGrid[sizeof(char)*8 + i*6 + 2]);
		node.setLinkedToRightNeighbor(encodedGrid[sizeof(char)*8 + i*6 + 3]);
		node.setLinkedToDownNeighbor(encodedGrid[sizeof(char)*8 + i*6 + 4]);
		node.setLinkedToLeftNeighbor(encodedGrid[sizeof(char)*8 + i*6 + 5]);
	}
	return decodedGrid;
}


