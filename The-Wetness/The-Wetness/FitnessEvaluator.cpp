#include "FitnessEvaluator.hpp"


FitnessEvaluator::FitnessEvaluator()
{
}


FitnessEvaluator::~FitnessEvaluator()
{
}

int FitnessEvaluator::evaluate(Grid& grid) const
{
	int numMustPass = grid.getDataCount(Grid::Data::MUST_PASS);
	std::vector<Grid::Coordinates> start = grid.getDatas(Grid::Data::START);
	std::vector<Grid::Coordinates> exit = grid.getDatas(Grid::Data::EXIT);
	if (start.size() == 0 || exit.size() == 0)
	{
		return -1000;
	}

	if (!grid.hasValidPath(start[0], exit[0])) {
		std::cout << "has not valid path :" << std::endl;
		std::cout << grid << std::endl;
		return -2000;
	}
	std::cout << "hasvalid path :" << std::endl;
	std::cout << grid << std::endl;
	return numMustPass;
}
