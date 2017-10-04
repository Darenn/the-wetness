#include "PuzzleGenerator.hpp"

Grid PuzzleGenerator::generateNextPuzzle()
{
	GA_Algorithms ga_algo;

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

			if (std::rand() / static_cast<float>(RAND_MAX) < 0.8f)
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
		sort(population.begin(), population.end(), [](std::pair<std::vector<bool>, int> a, std::pair<std::vector<bool>, int> b) { return  a.second > b.second; });
		population.erase(population.begin() + GENERATION_SIZE, population.end());
	}

	auto best = population[0];
	std::cout << best.second << std::endl;
	std::cout << _gridDecoder.decode(best.first) << std::endl;

	return _gridDecoder.decode(best.first);
}

GA_Algorithms::Population PuzzleGenerator::initializePopulation(int numChromosomes)
{
	auto grids = std::vector<Grid>(numChromosomes, Grid(GRID_WIDTH, GRID_HEIGHT));
	GA_Algorithms::Population population;
	population.reserve(numChromosomes);

	for (auto i = 0; i < numChromosomes; ++i)
	{
		population.push_back(std::pair<GA_Algorithms::Chromosome, int>(_gridEncoder.encode(grids[i]), 0));
	}

	return population;
}

void PuzzleGenerator::evaluatePopulation(GA_Algorithms::Population & population)
{
	for (auto& pair : population)
	{
		pair.second = _fitnessEvaluator.evaluate(_gridDecoder.decode(pair.first));
	}
}
