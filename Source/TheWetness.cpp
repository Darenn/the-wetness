#include "TheWetness/Grid.hpp"
#include <iostream>
#include "TheWetness/GridEncoder.hpp"
#include <iterator>
#include "TheWetness/GA_Algorithms.hpp"
#include "TheWetness/GridDecoder.hpp"

using namespace std;

void display_vector(const vector<bool> &v)
{
	std::copy(v.begin(), v.end(),
		ostream_iterator<bool>(std::cout, " "));
}

GA_Algorithms::Population initializePopulation(int numChromosomes)
{
	auto grids = std::vector<Grid>(numChromosomes, Grid(5, 5));
	auto population = GA_Algorithms::Population();
	population.reserve(numChromosomes);
	auto ge = GridEncoder();

	for (auto i = 0; i < numChromosomes; ++i)
	{
		population.push_back(std::pair<GA_Algorithms::Chromosome, int>(ge.encode(grids[i]), 0));
	}

	return population;
}

void evaluatePopulation(GA_Algorithms::Population& population)
{
	for (auto pair : population)
	{
		pair.second = 10;
	}
}


int main()
{
	/*Grid grid(4, 4);
	GridEncoder ge{};

	vector<bool> encodedGrid = ge.encode(grid);
	cout << "Grid :" << std::endl << grid << std::endl;
	cout << "Encoded grid : " << std::endl;
	display_vector(encodedGrid);
	GridDecoder gd{};
	Grid decodedGrid = gd.decode(encodedGrid);
	cout << std::endl << "Decoded grid : " << std::endl << decodedGrid;*/

	GA_Algorithms ga_algo;

	auto population = initializePopulation(10);
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
		}

		// population.push_back()
		evaluatePopulation(population);
		// Sort population by fitness
		// Take the nth bests for the next generation		
	}

	auto best = population[0];

    return 0;
}



