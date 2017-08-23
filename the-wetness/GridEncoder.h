#pragma once

#include <vector>
#include "Grid.h"

/// <summary>
/// Class to encode a grid into a binary string (here a vector<bool>). 
/// It is encoded that way : each node is encoded with 6 bits. 
/// The two firsts represent the content (4 different contents) and the other the link with other neighbours.
/// </summary>
class GridEncoder
{
public:
	GridEncoder();
	~GridEncoder();

	static const size_t NUMBER_BITS_PER_NODE = 6;

	std::vector<bool> encode(const Grid& grid) const;
};

