#pragma once
#include "Grid.h"

class GridDecoder
{
public:
	GridDecoder();
	~GridDecoder();

	Grid decode(const std::vector<bool> encodedGrid) const;
};

