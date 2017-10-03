#pragma once

#include "Grid.hpp"

class FitnessEvaluator
{
public:
	FitnessEvaluator();
	~FitnessEvaluator();

	int evaluate(Grid& grid) const;
};

