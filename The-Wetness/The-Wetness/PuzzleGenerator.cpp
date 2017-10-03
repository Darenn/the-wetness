#include "PuzzleGenerator.hpp"

Grid PuzzleGenerator::generateNextPuzzle()
{
	const unsigned GENERATION_SIZE = 20;

	GA_Algorithms ga_algo;

	auto population = initializePopulation(GENERATION_SIZE);
	evaluatePopulation(population);

	for (auto i = 0; i < 10; ++i)
	{
		auto offspring = GA_Algorithms::Population{};
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

			std::cout << _gridDecoder.decode(child) << std::endl;
			auto grid = _gridDecoder.decode(child);
		}

		population.insert(population.end(), offspring.begin(), offspring.end());
		evaluatePopulation(population);

		// Only keep the GENERATION_SIZE bests
		sort(population.begin(), population.end(), [](std::pair<std::vector<bool>, int> a, std::pair<std::vector<bool>, int> b) { return  a.second > b.second; });
		population.erase(population.begin() + GENERATION_SIZE, population.end());
	}

	auto best = population[0];
	std::cout << best.second << std::endl;

	return _gridDecoder.decode(best.first);
}

GA_Algorithms::Population PuzzleGenerator::initializePopulation(int numChromosomes)
{
	auto grids = std::vector<Grid>(numChromosomes, Grid(5, 5));
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
