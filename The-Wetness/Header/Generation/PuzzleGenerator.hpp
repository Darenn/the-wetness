#pragma once

#include <iterator>
#include <iostream>
#include <algorithm>

#include "Grid/Grid.hpp"
#include "Grid/GridEncoder.hpp"
#include "Grid/GridDecoder.hpp"

#include "GA/GA_Algorithms.hpp"
#include "GA/FitnessEvaluator.hpp"
#include "GA/ConformityEvaluator.hpp"

class PuzzleGenerator {
public:
	Grid generateNextPuzzle();
	const unsigned GENERATION_SIZE = 20;
	const unsigned NUM_ITER        = 30;
	const unsigned GRID_WIDTH      = 3;
	const unsigned GRID_HEIGHT     = 3;

private:
	GA_Algorithms::Population initializePopulation(int numChromosomes);
	void evaluatePopulation(GA_Algorithms::Population& population);

	FitnessEvaluator _fitnessEvaluator;
	ConformityEvaluator m_conformityEvaluator;
	GridDecoder _gridDecoder;
	GridEncoder _gridEncoder;
};