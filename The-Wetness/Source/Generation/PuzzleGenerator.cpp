#include "Generation/PuzzleGenerator.hpp"
#include <ctime>
#include "Generation/Utility/Utils.h"

using namespace std;

Grid PuzzleGenerator::generateNextPuzzle()
{
	GA_Algorithms ga_algo;
	srand(std::time(nullptr));

	auto population = initializePopulation(GENERATION_SIZE);
	evaluatePopulation(population);

	for (auto i = 0; i < NUM_ITER; ++i)
	{
		GA_Algorithms::Population offspring{};
		for (auto j = 0; j < population.size(); j++)
		{
			auto parentA = ga_algo.select(population);
			auto parentB = ga_algo.select(population);

			GA_Algorithms::Chromosome child;

			if (std::rand() / static_cast<float>(RAND_MAX) < 0.2f)
			{
				child = ga_algo.cross(parentA, parentB);
			}
			else
			{
				child = GA_Algorithms::Chromosome(parentA);
			}

			ga_algo.mutate(child);
			offspring.push_back(std::pair<GA_Algorithms::Chromosome, int>(child, 0));
		}

		population.insert(population.end(), offspring.begin(), offspring.end());

		evaluatePopulation(population);

		// Only keep the GENERATION_SIZE bests
		sort(population.begin(), population.end(), [](std::pair<std::vector<bool>, int> a, std::pair<std::vector<bool>, int> b) { return a.second > b.second; });
		population.erase(population.begin() + GENERATION_SIZE, population.end());
	}

	auto best = population[0];
	Grid bestGrid = _gridDecoder.decode(best.first);
	std::vector<Grid::Coordinates> start = bestGrid.getDatas(Grid::Data::START);
	std::vector<Grid::Coordinates> exit = bestGrid.getDatas(Grid::Data::EXIT);
	std::vector<Grid::Coordinates> path = bestGrid.getValidPath(start[0], exit[0]);
	if (path.size() <= 0)
		return generateNextPuzzle();
	return bestGrid;
}

GA_Algorithms::Population PuzzleGenerator::initializePopulation(int numChromosomes)
{
	std::vector<Grid*> grids;
	for (size_t i = 0; i < numChromosomes; i++)
	{
		int size = Utils::RandomRange(2, 8);
		Grid* g = new Grid(Utils::RandomRange(2, 8), Utils::RandomRange(2, 8));
		grids.push_back(g);
	}

	GA_Algorithms::Population population;
	population.reserve(numChromosomes);

	for (auto i = 0; i < numChromosomes; ++i)
	{
		population.push_back(std::pair<GA_Algorithms::Chromosome, int>(_gridEncoder.encode(*grids[i]), 0));
	}

	return population;
}

void PuzzleGenerator::evaluatePopulation(GA_Algorithms::Population & population)
{
	for (auto& pair : population)
	{
		Grid decodedGrid = _gridDecoder.decode(pair.first);
		m_conformityEvaluator.fixGrid(decodedGrid);
		pair.first = _gridEncoder.encode(decodedGrid);
		pair.second = _fitnessEvaluator.evaluate(decodedGrid);
	}
}
