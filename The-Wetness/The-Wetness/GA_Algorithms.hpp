#pragma once
#include <vector>

class GA_Algorithms
{
public:
	
	typedef std::vector<std::pair<std::vector<bool>, int>> Population;
	typedef std::vector<bool> Chromosome;

	void mutate(Chromosome& chromosome, float mutationProbability = 0.15f) const;
	/// <summary>
	/// One-point crossover
	/// </summary>
	/// <param name="parentA"></param>
	/// <param name="parentB"></param>
	/// <returns></returns>
	Chromosome cross(const Chromosome& parentA, const Chromosome& parentB) const;
	const Chromosome& select(const Population& population) const;
};
