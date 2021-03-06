#pragma once

#include "Generation/Grid/Grid.hpp"
#include "ConformityEvaluator.hpp"

class FitnessEvaluator
{
public:
	FitnessEvaluator();
	~FitnessEvaluator();

	int evaluate(Grid& grid) const;

private:
	ConformityEvaluator m_conformityEvaluator;
};

