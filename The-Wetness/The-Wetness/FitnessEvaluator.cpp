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
	grid.hasValidPath(start[0], exit[0]);
	return numMustPass;
}
