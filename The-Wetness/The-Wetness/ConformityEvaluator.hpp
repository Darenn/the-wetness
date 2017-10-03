#pragma once

#include "Grid.hpp"

class ConformityEvaluator
{
public:
	ConformityEvaluator();
	~ConformityEvaluator();

	bool evaluate(Grid& grid);
};

