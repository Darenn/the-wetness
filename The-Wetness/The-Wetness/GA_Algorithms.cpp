#include "GA_Algorithms.hpp"
#include <random>
#include <stdexcept>
#include <algorithm>

void GA_Algorithms::mutate(Chromosome& chromosome, float mutationProbability) const
{
	// don't mutate the number of rows
	for (size_t i = sizeof(char) * 8; i < chromosome.size(); i++)
	{
		if (std::rand() / static_cast<float>(RAND_MAX) < mutationProbability)
			chromosome[i] = !chromosome[i];
	}
}

GA_Algorithms::Chromosome GA_Algorithms::cross(const Chromosome& parentA, const Chromosome& parentB) const
{
	if (parentA.size() != parentB.size())
	{
		throw std::invalid_argument("Both parent must have the same size.");
	}
	auto child = std::vector<bool>(parentA);
	auto crossPoint = std::rand() / static_cast<float>(RAND_MAX) * parentB.size();
	for (auto i = crossPoint; i < parentB.size(); ++i)
	{
		child[i] = parentB[i];
	}
	return child;
}

const GA_Algorithms::Chromosome& GA_Algorithms::select(const std::vector<std::pair<std::vector<bool>, int>>& population) const
{
	#define COMPARISON [](std::pair<std::vector<bool>, int> a, std::pair<std::vector<bool>, int> b) { return  a.second < b.second; }
	auto bestFitness = *std::max_element(population.begin(), population.end(), COMPARISON);
	std::min_element(population.begin(), population.end(), COMPARISON);
	auto parentIndex = std::rand() / static_cast<float>(RAND_MAX) * population.size();
	return population[parentIndex].first;
}
