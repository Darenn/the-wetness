#pragma once
#include "Grid.hpp"

class GridDecoder
{
public:
	GridDecoder();
	~GridDecoder();

	Grid decode(const std::vector<bool> encodedGrid) const;
};

