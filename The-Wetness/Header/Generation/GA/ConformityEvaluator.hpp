#pragma once

#include "Generation/Grid/Grid.hpp"

class ConformityEvaluator
{
public:
	ConformityEvaluator();
	~ConformityEvaluator();

	bool evaluate(Grid& grid) const;
	void fixGrid(Grid& grid) const;
};

