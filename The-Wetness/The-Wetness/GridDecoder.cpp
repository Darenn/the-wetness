#include "GridDecoder.hpp"
#include "GridEncoder.hpp"
#include <cassert>


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
	assert(newVec.size() == 8);
	int numberRows = fromVector(newVec);

	int numberColumns = ((encodedGrid.size() - sizeof(char)*8) / GridEncoder::NUMBER_BITS_PER_NODE) / numberRows;

	// Create a basic grid with good dimensions
	Grid decodedGrid(numberRows, numberColumns);

	// Modify each node accordingly to the encoded grid
	for (size_t i = 0; i < decodedGrid.getNodeCount(); i++)
	{

		// decode the content
		std::pair<bool, bool> content(encodedGrid[sizeof(char)*8 + i*6], encodedGrid[sizeof(char)*8 + i*6 + 1]);
		//std::cout << content.second << std::endl;
		if (content.first == 0)
		{
			if (content.second == 0)
				decodedGrid.setData(i, Grid::Data::START);
			else
				decodedGrid.setData(i, Grid::Data::EXIT);
		}
		else
		{
			if (content.second == 0)
				decodedGrid.setData(i, Grid::Data::MUST_PASS);
			else
				decodedGrid.setData(i, Grid::Data::NOTHING);
		}

		// decode the links with neighbours
		int ind = 8 + i * 6 + 2;
		if (decodedGrid.hasNeighbor(i, Grid::Direction::NORTH))
			decodedGrid.setLinkWithNeighbor(i, Grid::Direction::NORTH, encodedGrid[sizeof(char)*8 + i*6 + 2]);
		else decodedGrid.setLinkWithNeighbor(i, Grid::Direction::NORTH, false);

		if (decodedGrid.hasNeighbor(i, Grid::Direction::EAST))
			decodedGrid.setLinkWithNeighbor(i, Grid::Direction::EAST, encodedGrid[sizeof(char)*8 + i*6 + 3]);
		else decodedGrid.setLinkWithNeighbor(i, Grid::Direction::EAST, false);

		if (decodedGrid.hasNeighbor(i, Grid::Direction::SOUTH))
			decodedGrid.setLinkWithNeighbor(i, Grid::Direction::SOUTH, encodedGrid[sizeof(char) * 8 + i * 6 + 4]);
		else decodedGrid.setLinkWithNeighbor(i, Grid::Direction::SOUTH, false);

		if (decodedGrid.hasNeighbor(i, Grid::Direction::WEST))
			decodedGrid.setLinkWithNeighbor(i, Grid::Direction::WEST, encodedGrid[sizeof(char)*8 + i*6 + 5]);
		else decodedGrid.setLinkWithNeighbor(i, Grid::Direction::WEST, false);

	}
	return decodedGrid;
}


