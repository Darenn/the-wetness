#pragma once

#include "Grid.hpp"
#include "GA_Algorithms.hpp"
#include <iostream>
#include "GridEncoder.hpp"
#include <iterator>
#include <algorithm>
#include "GridDecoder.hpp"
#include "FitnessEvaluator.hpp"
#include "ConformityEvaluator.hpp"

class PuzzleGenerator {
public:
	Grid generateNextPuzzle();
	const unsigned GENERATION_SIZE = 10;
	const unsigned NUM_ITER = 10;
	const unsigned GRID_WIDTH = 5;
	const unsigned GRID_HEIGHT = 5;

private:
	GA_Algorithms::Population initializePopulation(int numChromosomes);
	void evaluatePopulation(GA_Algorithms::Population& population);

	FitnessEvaluator _fitnessEvaluator;
	ConformityEvaluator m_conformityEvaluator;
	GridDecoder _gridDecoder;
	GridEncoder _gridEncoder;
};